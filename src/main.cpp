#include <Arduino.h>
#include <WiFi.h>

#ifndef STASSID
#define STASSID "myssid"
#define STAPSK "mypsk1234"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;

void setup()
{
  delay(500);
  Serial.begin(115200);
  delay(500);

  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(17, INPUT_PULLDOWN);

  Serial.println("Starting...");
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.begin(ssid, password);

  uint32_t start = millis();
  while (!WiFi.isConnected())
  {
    digitalWrite(25, HIGH);
    delay(50);
    digitalWrite(25, LOW);
    delay(50);
    digitalWrite(26, HIGH);
    delay(50);
    digitalWrite(26, LOW);
    delay(900);
    if (millis() - start > 30000)
    {
      digitalWrite(3, HIGH);
      Serial.println("Connection Failed! Rebooting...");
      delay(5000);
      ESP.restart();
    }
  }
  Serial.println(WiFi.localIP().toString());
}

void loop()
{
  int ms = 250;
  if (digitalRead(17) == HIGH)
  {
    ms = 25;
  }

  digitalWrite(25, HIGH);
  delay(ms);
  digitalWrite(26, HIGH);
  delay(ms);
  digitalWrite(25, LOW);
  delay(ms);
  digitalWrite(26, LOW);
  delay(ms);
}