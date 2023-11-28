#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiServer.h>
#include "env.h" // Custom environment header.

String ssid = ENVSSID;
String password = ENVPASS;
WiFiServer server(80);
String header;

int ledPin = LED_BUILTIN;
int photoResistorPin = A0;

String prepareJSON() {
  String htmlPage;
  htmlPage.reserve(1024);
  htmlPage = F("HTTP/1.1 200 OK\r\n"
               "Content-Type: application/json\r\n"
               "Connection: close\r\n"
               "Refresh: 5\r\n"
               "\r\n"
               "{\"photoresistor\":");
  htmlPage += analogRead(A0);
  htmlPage += F("}"
                "\r\n");
  return htmlPage;
}

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