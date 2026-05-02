#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>

// ================= WIFI =================
const char* ssid = "dinaraaa";
const char* password = "88888888";

// ================= MQTT (HiveMQ Cloud) =================
const char* mqtt_server = "";
const int mqtt_port = 8883;
const char* mqtt_user = "";
const char* mqtt_pass = "";

// ================= PIN SLOT =================
#define SLOT1 32
#define SLOT2 33

// ================= HC-SR04 =================
#define TRIG 18
#define ECHO 19

// ================= SERVO =================
#define SERVO_PIN 12
Servo gateServo;

// ================= MQTT =================
WiFiClientSecure espClient;
PubSubClient client(espClient);

// ================= STATE =================
int prev_s1 = -1;
int prev_s2 = -1;
int prev_freeSlot = -1;
bool prevFullState = false;

// ================= TIMING =================
unsigned long lastGate = 0;
const int gateCooldown = 4000;

// ================= WIFI CONNECT =================
void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
}

// ================= MQTT CONNECT =================
void reconnect() {
  while (!client.connected()) {
    client.connect("ESP32_PARKING", mqtt_user, mqtt_pass);
  }
}

// ================= ULTRASONIC =================
long readDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);
  if (duration == 0) return -1;

  return duration * 0.034 / 2;
}

// ================= SETUP =================
void setup() {
  pinMode(SLOT1, INPUT);
  pinMode(SLOT2, INPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  gateServo.attach(SERVO_PIN);
  gateServo.write(0);

  Serial.begin(115200);

  setup_wifi();

  espClient.setInsecure();
  client.setServer(mqtt_server, mqtt_port);
}

// ================= LOOP =================
void loop() {

  if (!client.connected()) reconnect();
  client.loop();

  // ================= SLOT READ =================
  int s1 = (digitalRead(SLOT1) == LOW) ? 1 : 0;
  int s2 = (digitalRead(SLOT2) == LOW) ? 1 : 0;
  int freeSlot = 2 - (s1 + s2);

  // ================= MQTT PUBLISH =================
  char msg[10];

  sprintf(msg, "%d", s1);
  client.publish("parking/slot1", msg);

  sprintf(msg, "%d", s2);
  client.publish("parking/slot2", msg);

  sprintf(msg, "%d", freeSlot);
  client.publish("parking/free", msg);

  client.publish("parking/status", (freeSlot == 0) ? "FULL" : "AVAILABLE");

  // ================= SERIAL ONLY ON CHANGE =================
  if (s1 != prev_s1 || s2 != prev_s2 || freeSlot != prev_freeSlot) {

    Serial.println("===== UPDATE PARKING =====");
    Serial.print("Slot1: "); Serial.println(s1 ? "FULL" : "EMPTY");
    Serial.print("Slot2: "); Serial.println(s2 ? "FULL" : "EMPTY");
    Serial.print("Free : "); Serial.println(freeSlot);

    prev_s1 = s1;
    prev_s2 = s2;
    prev_freeSlot = freeSlot;
  }

  // ================= GATE CONTROL =================
  long dist = readDistance();

  if (dist > 0 && dist <= 3) {

    bool currentFullState = (freeSlot == 0);

    if (currentFullState && !prevFullState) {
      Serial.println("PARKING FULL!");
    }

    prevFullState = currentFullState;

    if (!currentFullState) {
      if (millis() - lastGate > gateCooldown) {

        Serial.println("GATE OPEN");
        gateServo.write(90);
        delay(2000);
        gateServo.write(0);
        Serial.println("GATE CLOSE");

        lastGate = millis();
      }
    }
  }

  delay(300);
}
