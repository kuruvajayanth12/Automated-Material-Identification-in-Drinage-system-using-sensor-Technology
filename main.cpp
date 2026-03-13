#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define METAL_SENSOR_PIN 4   // GPIO 4

// 🔹 WiFi credentials
const char* ssid = "Jayanth";
const char* password = "64089087";

// 🔹 Telegram details
String botToken = "8065025613:AAGgNs_jVfVG78ahmlcPwzFNNVSikxHIBCw";
String chatID  = "6743483783";

bool messageSent = false;   // prevents repeat messages

// 🔹 Function to send Telegram message
void sendTelegramMessage(String message) {
  HTTPClient http;
  String url = "https://api.telegram.org/bot" + botToken +
               "/sendMessage?chat_id=" + chatID +
               "&text=" + message;

  http.begin(url);
  http.GET();
  http.end();

  Serial.println("Telegram message sent");
}

void setup() {
  Serial.begin(115200);
  pinMode(METAL_SENSOR_PIN, INPUT);

  Serial.println("Metal Detection Test Started");

  // 🔹 Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
}

void loop() {
  int sensorValue = digitalRead(METAL_SENSOR_PIN);

  if (sensorValue == HIGH) {
    Serial.println("⚠️ object detected");

    if (!messageSent) {
      sendTelegramMessage("⚠️ object detected!");
      messageSent = true;
    }
  } 
  else {
    Serial.println("⚙️ No metal");
    messageSent = false;   // reset when metal removed
  }

  delay(500);
}
