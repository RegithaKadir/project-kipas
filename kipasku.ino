#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

// Konfigurasi pin dan tipe sensor
#define DHTPIN 2
#define DHTTYPE DHT11
#define relay1 14  // GPIO14 (D5)
#define relay2 12  // GPIO12 (D6)

DHT dht(DHTPIN, DHTTYPE);
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  digitalWrite(relay1, HIGH); // relay mati (LOW = ON)
  digitalWrite(relay2, HIGH);

  // Membuat WiFi Access Point
  WiFi.softAP("3 girls cantik", "12345678");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  // Routing
  server.on("/", handleRoot);
  server.on("/data", handleData); // Endpoint untuk data AJAX

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

  float t = dht.readTemperature();

  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.println(" °C");

  // Kontrol otomatis kipas
  if (t > 20.0 && t <= 29.0) {
    digitalWrite(relay1, LOW);  // kipas 1 ON
    digitalWrite(relay2, HIGH); // kipas 2 OFF
    Serial.println("Kipas kecepatan rendah menyala");
  } else if (t > 29.0) {
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, LOW);
    Serial.println("Kipas kecepatan tinggi menyala");
  } else {
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    Serial.println("Semua kipas mati");
  }

  delay(2000);
}

// Halaman utama (dengan AJAX)
void handleRoot() {
  String html = "<!DOCTYPE html>";
  html += "<html><head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>";
  html += "body { font-family: Arial; text-align: center; background-color: #f8f9fa; color: #333; }"; 
  html += "h1 { color: #007BFF; }";
  html += ".container { width: 80%; margin: auto; padding: 20px; background: white; box-shadow: 0 0 10px rgba(0,0,0,0.1); border-radius: 10px; }";
  html += ".status { font-size: 20px; font-weight: bold; padding: 10px; border-radius: 5px; }";
  html += ".on { color: green; }";
  html += ".off { color: red; }";
  html += "</style>";
  html += "<script>";
  html += "function updateData() {";
  html += "  fetch('/data').then(response => response.json()).then(data => {";
  html += "    document.getElementById('suhu').innerHTML = data.suhu + ' &deg;C';";
  html += "    document.getElementById('kipas1').innerHTML = data.kipas1 ? 'Menyala' : 'Mati';";
  html += "    document.getElementById('kipas1').className = 'status ' + (data.kipas1 ? 'on' : 'off');";
  html += "    document.getElementById('kipas2').innerHTML = data.kipas2 ? 'Menyala' : 'Mati';";
  html += "    document.getElementById('kipas2').className = 'status ' + (data.kipas2 ? 'on' : 'off');";
  html += "  });";
  html += "}";
  html += "setInterval(updateData, 3000);";
  html += "window.onload = updateData;";
  html += "</script>";
  html += "</head><body>";
  
  html += "<div class='container'>";
  html += "<h1>Monitoring Suhu dan Kipas</h1>";
  html += "<p><strong>Suhu:</strong> <span id='suhu'>Loading...</span></p>";
  html += "<p><strong>Status Kipas 1 (Rendah):</strong> <span id='kipas1' class='status'>Loading...</span></p>";
  html += "<p><strong>Status Kipas 2 (Tinggi):</strong> <span id='kipas2' class='status'>Loading...</span></p>";
  html += "</div></body></html>";

  server.send(200, "text/html", html);
}

// Endpoint JSON untuk AJAX
void handleData() {
  float t = dht.readTemperature();
  if (isnan(t)) t = 0.0;

  bool kipas1 = (digitalRead(relay1) == LOW);
  bool kipas2 = (digitalRead(relay2) == LOW);

  String json = "{";
  json += "\"suhu\":" + String(t, 1) + ",";
  json += "\"kipas1\":" + String(kipas1 ? "true" : "false") + ",";
  json += "\"kipas2\":" + String(kipas2 ? "true" : "false");
  json += "}";

  server.send(200, "application/json", json);
}
