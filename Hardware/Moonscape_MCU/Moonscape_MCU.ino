#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "neeltron2.4G";
const char* password = "*************";
const char *host = "Moonscape.neeltron.repl.co";
const int httpsPort = 443;
const char fingerprint[] PROGMEM = "25 DE 41 40 12 C6 E3 8C 9A FD 50 CC 35 CB 03 42 7B FC DD 86";
SoftwareSerial s(D6, D5);
void setup()
{
  s.begin(57600);
  Serial.begin(57600);
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  Serial.println("");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop()
{
  int data = s.read();
  if (data != -1) {
    Serial.println(data);
    WiFiClientSecure client;
    Serial.println(host);
    Serial.printf("Using fingerprint '%s'\n", fingerprint);
    client.setFingerprint(fingerprint);
    client.setTimeout(15000);
    delay(100);
    Serial.print("HTTPS Connecting");
    int r = 0;
    while ((!client.connect(host, httpsPort)) && (r < 30)) {
      delay(100);
      Serial.print(".");
      r++;
    }
    if (r == 30) {
      Serial.println("Connection failed");
    }
    else {
      Serial.println("Connected to web");
    }

    String getData, Link;

    Link = "/input?sleep=" + String(data);
    Serial.print("requesting URL: ");
    Serial.println(host + Link);
    client.print(String("GET ") + Link + " HTTP/1.1\r\n" +
                      "Host: " + host + "\r\n" +
                      "Connection: close\r\n\r\n");

    Serial.println("request sent");

    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("received");
        break;
      }
    }
    String line;
    while (client.available()) {
      line = client.readStringUntil('\n');
      Serial.println(line);
    }
    delay(1000);
  }
}