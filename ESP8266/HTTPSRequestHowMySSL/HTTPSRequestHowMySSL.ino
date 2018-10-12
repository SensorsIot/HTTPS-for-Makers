/*
    HTTP over TLS (HTTPS) example sketch

    This example demonstrates how to use
    WiFiClientSecure class to access HTTPS API.
    We fetch and display the status of
    esp8266/Arduino project continuous integration
    build.

    Limitations:
      only RSA certificates
      no support of Perfect Forward Secrecy (PFS)
      TLSv1.2 is supported since version 2.4.0-rc1

    Created by Ivan Grokhotkov, 2015.
    This example is in public domain.
*/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <credentials.h>

const char*  ssid = mySSID;
const char* password = myPASSWORD;

//const char* host = "howsmyssl.com";
//const char* fingerprint = "B2 6F 23 D1 90 D5 41 5E CD 20 61 7A 74 31 DA B2 9C E4 48 97"; //howsmyssl

//const char* host = "google.com";
//const char* fingerprint = "76 FB 50 5F 7C 81 7D 89 6B 42 14 24 43 DE 86 E7 3C D9 85 5F"; //google

//const char* host = "thingspeak.com";
//const char* fingerprint = "F9 C2 65 6C F9 EF 7F 66 8B F7 35 FE 15 EA 82 9F 5F 55 54 3E"; //Thingspeak

const char* host = "howsmyssl.com";
const char* fingerprint = "b2 6f 23 d1 90 d5 41 5e cd 20 61 7a 74 31 da b2 9c e4 48 97"; //howsmyssl

const int httpsPort = 443;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (client.verify(fingerprint, host)) {
    Serial.println("fingerprint matches");
  } else {
    Serial.println("fingerprint doesn't match");
  }

  Serial.println("\nStarting connection to server...");
  if (!client.connect(host, 443))
    Serial.println("Connection failed!");
  else {
    Serial.println("Connected to server!");
    // Make a HTTP request:
    client.print("GET https://www.");
    client.print(host);
    client.println("/a/check HTTP/1.0");
    client.print("Host: ");
    client.println(host);

    Serial.print("GET https://");
    Serial.print(host);
    Serial.println("/a/check HTTP/1.0");
    Serial.println("Host: ");
    Serial.println(host);
    client.println("Connection: close");
    client.println();

    Serial.println("request sent");
  }
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
}

void loop() {
}
