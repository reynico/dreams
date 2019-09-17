#include "DHTesp.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* host = "Dreams exporter 3";
IPAddress ip_addr(192,168,1,8);
IPAddress gw(192,168,1,1);
IPAddress subnet(255,255,255,0);

DHTesp dht;
ESP8266WebServer server(9000);

void setup() {
  Serial.begin(115200);
  dht.setup(12, DHTesp::DHT22);
  setupWifi(host, ip_addr, gw, subnet);
}

void loop() {
    server.handleClient();
}
