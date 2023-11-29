#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiServer.h>
#include "env.h" // Custom environment header.
#include "prepareJSON.h"

String ssid = ENVSSID;
String password = ENVPASS;
WiFiServer server(80);
String header;

int ledPin = LED_BUILTIN;
int photoResistorPin = A0;

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi router");
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  server.begin();
  Serial.println();

  Serial.print("Connected! @ address: ");
  Serial.println(WiFi.localIP());

  pinMode(ledPin, OUTPUT);
  pinMode(photoResistorPin, INPUT);
}

void loop() {
  WiFiClient client = server.accept();
  if (client) {
    while (client.connected()) {
      digitalWrite(ledPin, HIGH);

      if (client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);

        if (line.length() == 1 && line[0] == '\n') {
          client.println(prepareJSON());
          break;
        }
      }

      digitalWrite(ledPin, LOW);
    }

    while (client.available()) client.read();
    client.stop();
    Serial.println("Client disconnected.");
  }
}