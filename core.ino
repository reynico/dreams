const char* ssid = "your-ssid";
const char* password = "your-psk";
int co2Sensor = A0;

void setupWifi(const char* host, IPAddress ip, IPAddress gw, IPAddress subnet) {
  WiFi.begin(ssid, password);
  WiFi.hostname(host);
  WiFi.config(ip, gw, subnet);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  while (WiFi.status() != WL_CONNECTED)
    delay(1000);
  Serial.println("Connection established!");
  server.on("/metrics", handle_OnConnect);
  server.begin();
}

void handle_OnConnect() {
  TempAndHumidity dht22 = dht.getTempAndHumidity();
  int adcCo2 = analogRead(co2Sensor);
  float voltage = adcCo2*(3.3/1023);

  if (voltage == 0) {
    Serial.println("A problem has occurred with the sensor");
  } else if (voltage < 0.4) {
    Serial.println("Pre-heating the sensor...");
  } else {
    float voltageDiference=voltage-0.4;
    float concentration=(voltageDiference*5000.0)/1.6;
    String content = "co2_concentration " + String(concentration) + "\n";
    content += "temperature_c " + String(dht22.temperature) + "\n";
    content += "humidity " + String(dht22.humidity) + "\n";
    server.send(200, "text/html", content);
  }
}
