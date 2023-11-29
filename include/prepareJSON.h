#ifndef prepareJSON_h
#define prepareJSON_h
#include <Arduino.h>

String prepareJSON() {
  String jsonResponse;
  jsonResponse.reserve(1024);
  jsonResponse = F("HTTP/1.1 200 OK\r\n"  // This code is designed for 1:1 sensor:controller only. TODO: add support for multiple sensors.
               "Content-Type: application/json\r\n"
               "Connection: close\r\n"
               "Refresh: 5\r\n"
               "\r\n"
               "{"
               "\"sensorModel\": \"photoresistor\", \"reading\": "); // sensor data
  jsonResponse += analogRead(A0);
  jsonResponse += F(","
               "\"type\": \"light\", \"format\": \"analog\", " // sensor data
               "\"controllerModel\": \"NodeMCU v0.9\"" // controller data
               "}"
               "\r\n");
  return jsonResponse;
}

#endif