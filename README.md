# 📊 IoT Based Classroom Noise Monitoring System

An **IoT-based Classroom Noise Monitoring System** that detects excessive noise levels, tracks teacher presence using RFID, and captures visual evidence when noise exceeds a defined threshold in the teacher’s absence. The system provides **real-time monitoring** and a **dashboard-based event log** for management review.

---

## 🚀 Project Overview

This project combines **hardware + software** to create a smart classroom monitoring solution.
It ensures discipline by automatically detecting noise violations **only when a teacher is absent**, avoiding unnecessary alerts when the teacher is present.

### Core Logic

* Teacher presence is detected via **RFID authentication**
* Noise levels are continuously monitored
* If noise exceeds the set threshold **and teacher is absent**:

  * Buzzer alerts students
  * Webcam captures images/video
  * Event data is sent to the dashboard
* If teacher is present → system remains passive

---

## 🧩 System Architecture

**Hardware Layer**

* Noise detection & RFID authentication
* LCD feedback inside the classroom

**Software Layer**

* Web-based monitoring interface
* Dashboard for event history
* Serial/Web communication with ESP8266

---

## 🔧 Hardware Components Required

| Component               | Description                           |
| ----------------------- | ------------------------------------- |
| NodeMCU (ESP8266)       | Main microcontroller with WiFi        |
| RFID Reader (MFRC522)   | Teacher presence detection            |
| RFID Cards/Tags         | Assigned to teachers/classes          |
| LCD (16x2, I2C)         | Displays status & noise level         |
| Buzzer                  | Audible alert when threshold exceeded |
| Webcam (PC/Laptop)      | Captures photos/videos                |
| Microphone (Webcam Mic) | Noise/decibel detection               |
| Jumper Wires            | Connections                           |
| Breadboard              | Prototyping                           |

---

## 💻 Software & Tools Used

### Firmware / Embedded

* Arduino IDE
* ESP8266 Board Package
* Libraries:

  * `MFRC522`
  * `SPI`
  * `Wire`
  * `LiquidCrystal_I2C`

### Web Technologies

* HTML
* CSS
* JavaScript
* Web Serial API
* Web Media API (Camera & Mic)

### Platform

* Runs locally in modern browsers (Chrome/Edge recommended)

---

## 🌐 Web Application Structure

### 1️⃣ Monitoring Page

Used for **live operation & control**

Features:

* Connect ESP device via Serial Port
* Set noise threshold (dB)
* Set duration (seconds)
* Live webcam feed
* Live decibel display
* Teacher presence status (Present / Absent)
* Navigation to Dashboard

---

### 2️⃣ Dashboard Page

Used for **event history & review**

Displays:

* Timestamp & date
* Noise level exceeded (dB)
* Duration of violation
* Captured image/snapshot
* Classroom / teacher status
* Table-based event log

---

## 🔁 Workflow (End-to-End)

1. Teacher scans RFID card
2. System marks **Teacher Present / Absent**
3. Noise is continuously monitored
4. If threshold exceeded **and teacher is absent**:

   * Buzzer alerts
   * Webcam captures media
   * Event logged to dashboard
5. Management reviews events via dashboard

---

## 📂 Repository Structure

```
Classroom-Noise-Monitor/
│
├── Code/
│   ├── esp8266_rfid_noise_monitor.ino
│
├── Web/
│   ├── index.html        # Monitoring Page
│   ├── dashboard.html   # Dashboard Page
│   ├── style.css
│   ├── script.js
│
├── Diagrams/
│   ├── circuit_diagram.png
│   ├── system_architecture.png
│
├── Docs/
│   ├── project_report.pdf
│
├── README.md
```

---

## 🔐 RFID Customization

* Each RFID card has a **unique UID**
* Multiple cards can be assigned to:

  * Different teachers
  * Different classrooms
* New card UIDs can be added easily in code

---

## 📌 Key Highlights

* Fully automated
* Practical real-world use
* Modular & scalable
* Teacher-aware logic
* Real-time monitoring + logging
* Exhibition-ready project

---

## 🧠 Future Enhancements

* Cloud-based dashboard (AWS / Firebase)
* Mobile app support
* Multiple classroom handling
* Role-based access (Admin / Teacher)
* Analytics & reports
* ESP32 camera integration

---

## 📜 License

This project is intended for **educational and academic use**.
Feel free to modify and extend it with proper credit.

