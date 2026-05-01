# Smart Parking System (ESP32 + MQTT + Node.js + Web Dashboard)

Sistem Smart Parking berbasis IoT menggunakan ESP32, sensor IR, HC-SR04, servo gate, MQTT HiveMQ Cloud, dan dashboard realtime berbasis Node.js + Socket.IO.

---

## Fitur

* Monitoring 2 slot parkir (IR Sensor)
* Gate otomatis menggunakan HC-SR04 + Servo
* Komunikasi realtime menggunakan MQTT (HiveMQ Cloud)
* Dashboard web realtime (Socket.IO)
* Status parkir: AVAILABLE / FULL
* Update data realtime tanpa refresh

---

## Arsitektur Sistem

ESP32 → MQTT HiveMQ Cloud → Node.js Server → Socket.IO → Web Dashboard

---

## Hardware yang Digunakan

* ESP32 Dev Module
* 2x Sensor IR (slot parkir)
* HC-SR04 (sensor gate)
* Servo motor (gate)
* Kabel jumper
* Power supply 5V

---

## Software & Tools yang Harus Diinstall

### 1. Arduino IDE (ESP32)

Tambahkan board ESP32:
File → Preferences → Additional Board Manager URLs

[https://espressif.github.io/arduino-esp32/package_esp32_index.json](https://espressif.github.io/arduino-esp32/package_esp32_index.json)

Install board:
Tools → Board → ESP32 Dev Module

### Library Arduino:

* ESP32Servo
* PubSubClient
* WiFi (default ESP32)
* WiFiClientSecure

---

### 2. Node.js

Install Node.js (LTS):
[https://nodejs.org](https://nodejs.org)

Cek instalasi:
node -v
npm -v

---

## Install Dependency Server

Masuk folder project:
cd smart-parking

Init project:
npm init -y

Install dependency:
npm install express mqtt socket.io

---

## Struktur Project

smart-parking/
│
├── server.js
├── mqttClient.js
├── socket.js
├── dataStore.js
│
├── routes/
│   └── web.js
│
├── public/
    ├── index.html
    ├── style.css
    └── app.js


---

## Cara Menjalankan Sistem

### 1. Jalankan Server Node.js

node server.js
---

### 2. Upload Program ESP32

* Pilih board: ESP32 Dev Module
* Upload kode dari Arduino IDE

---

### 3. Buka Dashboard Web

(http://localhost:3000)

---

## MQTT Topic

parking/slot1
parking/slot2
parking/free
parking/status

---

## MQTT HiveMQ Cloud

Host    : 0e99766ab1e84d4b87733024352139b3.s1.eu.hivemq.cloud
Port    : 8883
User    : iotgama21
Password: Iotgama21

---

## 2026 IoT GAMA

Smart Parking IoT Project – ESP32 + MQTT + Node.js
