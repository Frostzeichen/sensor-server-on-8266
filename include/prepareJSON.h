#ifndef prepareJSON_h
#define prepareJSON_h
#include <Arduino.h>

String prepareJSON() {
  String jsonResponse;
  jsonResponse.reserve(1024);
  jsonResponse = F("HTTP/1.1 200 OK\r\n"
               "Content-Type: application/json\r\n"
               "Connection: close\r\n"
               "Refresh: 5\r\n"
               "\r\n"
               "{\"photoresistor\":");
  jsonResponse += analogRead(A0);
  jsonResponse += F("}"
                "\r\n");
  return jsonResponse;
}

#endif