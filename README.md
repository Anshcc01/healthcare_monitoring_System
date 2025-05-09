# 🏥 IoT-Based Smart Healthcare Monitoring System

An end-to-end IoT solution to monitor vital health parameters—such as heart rate, SpO₂, room temperature, body temperature, and humidity—in real-time using ESP32, sensors, and a responsive web dashboard.

---

## 🚀 Features

- 📡 Real-time health data monitoring using WebSocket
- 🧠 Measures:
  - Heart Rate (BPM)
  - Blood Oxygen Level (SpO₂)
  - Room Temperature and Humidity
  - Body Temperature
- 📊 Responsive dashboard with live charts (HTML, CSS, JS)
- ⚠️ Abnormal value alerts (configurable)
- 🌐 ESP32-based Wi-Fi communication (no third-party cloud required)

---

## 🔧 Hardware Used

| Component      | Description                            |
|----------------|----------------------------------------|
| ESP32          | Microcontroller with built-in Wi-Fi    |
| MAX30100       | Pulse Oximeter (Heart Rate & SpO₂)     |
| DHT11          | Temperature & Humidity Sensor          |
| DS18B20        | High-accuracy Body Temperature Sensor  |
| Breadboard, Resistors, Wires | Standard IoT setup tools  |

---

## 🛠️ Software Stack

- **Firmware**: Arduino (C++) with:
  - `MAX30100_PulseOximeter.h`
  - `DallasTemperature.h`
  - `dht.h`
  - `WiFi.h`, `WebSocketsServer.h`
- **Frontend**: HTML + CSS + JavaScript
  - Chart.js for live graphs
  - WebSocket for real-time data updates


