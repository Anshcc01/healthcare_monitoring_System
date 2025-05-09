
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <dht.h>
#include <WiFi.h>
#include <WebSocketsServer.h>

#define DHT11_PIN 18  // GPIO18
#define DS18B20 5     // GPIO5
#define REPORTING_PERIOD_MS 1000

float temperature, humidity, BPM, SpO2, bodytemperature;

const char* ssid = "AnshGalaxy-a21s";
const char* password = "11223344";

dht DHT;
PulseOximeter pox;
OneWire oneWire(DS18B20);
DallasTemperature sensors(&oneWire);

// WebSocket server on port 81
WebSocketsServer webSocket = WebSocketsServer(81);
uint32_t tsLastReport = 0;

void onBeatDetected() {
  Serial.println("Beat!");
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  // Optional: handle client connect/disconnect
}

void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(19, OUTPUT);  // GPIO19 for any digital output

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  if (!pox.begin()) {
    Serial.println("Pulse oximeter FAILED");
    while (1);
  }
  Serial.println("Pulse oximeter ready");
  pox.setOnBeatDetectedCallback(onBeatDetected);
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

  sensors.begin();

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  pox.update();
  webSocket.loop();

  sensors.requestTemperatures();
  DHT.read11(DHT11_PIN);

  temperature = DHT.temperature;
  humidity = DHT.humidity;
  BPM = pox.getHeartRate();
  SpO2 = pox.getSpO2();
  bodytemperature = sensors.getTempCByIndex(0);

  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    String json = "{";
    json += "\"roomTemp\":" + String(temperature) + ",";
    json += "\"roomHumidity\":" + String(humidity) + ",";
    json += "\"heartRate\":" + String(BPM) + ",";
    json += "\"bloodOxygen\":" + String(SpO2) + ",";
    json += "\"bodyTemp\":" + String(bodytemperature);
    json += "}";

    Serial.println("Sending: " + json);
    webSocket.broadcastTXT(json);

    tsLastReport = millis();
  }
}
