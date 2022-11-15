#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#define IR_LED 4
IRsend irsend(IR_LED);
const char* ssid = "<wifiname>";
const char* password = "<wifipassword>";
uint16_t powerOn[349] = { 700, 17770, 3098, 8856, 620, 376, 620, 1376, 616, 382, 612, 384, 612, 404, 592, 404, 592, 404, 594, 400, 602, 394, 608, 1384, 612, 382, 616, 380, 616, 1376, 616, 378, 616, 380, 616, 1376, 614, 1380, 612, 1382, 610, 1402, 588, 1404, 588, 408, 596, 400, 602, 394, 606, 390, 608, 386, 612, 384, 612, 384, 612, 384, 612, 382, 612, 384, 612, 384, 612, 384, 610, 386, 608, 390, 606, 390, 606, 410, 584, 412, 584, 412, 586, 408, 594, 402, 598, 398, 600, 394, 606, 388, 608, 388, 610, 386, 610, 386, 610, 386, 610, 386, 610, 386, 610, 388, 608, 388, 606, 392, 604, 1408, 584, 1410, 582, 1410, 588, 1404, 608, 2870, 3104, 8874, 598, 1392, 602, 394, 602, 394, 600, 394, 600, 396, 600, 396, 600, 398, 598, 400, 596, 400, 594, 1418, 572, 424, 572, 422, 572, 1420, 584, 410, 588, 1404, 594, 1398, 598, 1392, 598, 1392, 598, 1394, 598, 1396, 596, 402, 594, 422, 574, 422, 572, 424, 570, 426, 572, 424, 576, 420, 584, 412, 588, 408, 590, 404, 594, 400, 598, 398, 598, 398, 598, 398, 598, 398, 598, 398, 598, 400, 596, 400, 596, 402, 594, 422, 574, 422, 572, 424, 572, 424, 572, 424, 576, 418, 584, 412, 588, 408, 592, 402, 596, 400, 598, 398, 598, 398, 598, 396, 598, 398, 596, 400, 598, 398, 598, 400, 596, 2902, 3074, 8904, 576, 1418, 574, 422, 574, 422, 580, 416, 582, 412, 590, 406, 596, 400, 596, 398, 600, 394, 602, 1390, 602, 394, 602, 394, 602, 394, 602, 394, 602, 1394, 598, 1414, 578, 418, 576, 1416, 578, 1414, 590, 1402, 596, 1396, 604, 1388, 606, 1386, 606, 1386, 606, 1386, 606, 390, 606, 392, 602, 394, 602, 1410, 580, 1412, 580, 1412, 592, 404, 598, 398, 602, 392, 606, 390, 608, 388, 608, 388, 608, 1384, 608, 388, 608, 386, 608, 1386, 606, 1388, 604, 412, 584, 1410, 582, 1410, 592, 402, 596, 398, 600, 396, 606, 390, 608, 388, 608, 386, 610, 386, 610, 1382, 608, 1382, 610, 1384, 608, 1388, 616 };
uint16_t powerOff[351] = { 684, 17792, 3092, 8864, 616, 380, 614, 1382, 610, 386, 610, 388, 610, 406, 590, 406, 588, 408, 590, 404, 600, 396, 604, 1388, 612, 384, 612, 382, 616, 1376, 616, 1376, 616, 378, 616, 1378, 614, 1378, 614, 1380, 612, 1400, 592, 1400, 596, 398, 606, 390, 610, 384, 614, 380, 616, 380, 618, 376, 620, 376, 620, 376, 618, 376, 620, 376, 620, 376, 620, 378, 618, 380, 616, 382, 614, 380, 614, 402, 594, 402, 594, 402, 604, 392, 610, 386, 612, 382, 618, 378, 620, 376, 622, 374, 620, 376, 620, 374, 624, 372, 622, 374, 622, 374, 622, 376, 620, 376, 618, 378, 618, 380, 616, 398, 598, 1396, 602, 1390, 622, 2854, 3122, 8856, 618, 1374, 620, 376, 620, 376, 620, 376, 618, 378, 618, 378, 616, 380, 616, 380, 612, 384, 614, 1382, 610, 406, 590, 406, 590, 1402, 596, 400, 602, 1388, 610, 1382, 616, 1376, 614, 1378, 614, 1378, 616, 1378, 614, 382, 612, 384, 610, 386, 610, 406, 590, 406, 590, 406, 590, 404, 600, 396, 606, 390, 608, 386, 612, 384, 614, 382, 614, 380, 616, 380, 618, 378, 616, 378, 616, 380, 616, 380, 616, 380, 612, 384, 612, 384, 610, 406, 588, 408, 590, 406, 590, 406, 598, 398, 602, 394, 606, 388, 612, 384, 614, 382, 616, 378, 616, 380, 616, 380, 616, 380, 614, 382, 614, 382, 614, 2886, 3090, 8870, 610, 1384, 606, 410, 586, 408, 588, 406, 594, 402, 600, 396, 606, 390, 610, 386, 614, 382, 614, 1376, 614, 382, 614, 382, 614, 382, 614, 1378, 614, 1380, 612, 1382, 610, 406, 588, 1406, 592, 1400, 602, 1390, 608, 1384, 616, 1376, 618, 1374, 618, 1374, 616, 1376, 618, 380, 612, 384, 614, 384, 612, 1402, 592, 1400, 596, 1396, 602, 392, 610, 386, 612, 384, 616, 380, 616, 378, 618, 378, 616, 1374, 618, 378, 618, 378, 618, 1378, 614, 1380, 612, 384, 12, 12, 584, 1402, 590, 1402, 600, 394, 608, 388, 610, 386, 612, 384, 616, 378, 618, 378, 618, 378, 618, 378, 616, 380, 618, 1376, 616, 1378, 618 };

ESP8266WebServer server(80);
const int led = 13;
void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "Hello from esp8266!");
  digitalWrite(led, 0);
}
void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Foundnn";
  message += "URI: ";
  message += server.uri();
  message += "nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "nArguments: ";
  message += server.args();
  message += "n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}
void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  irsend.begin();
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else   // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // ESP8266

  server.on("/", handleRoot);

  server.on("/on", []() {
    if (server.arg("password") == "<password>") {  // If password are correct
      delay(200);
      irsend.sendRaw(powerOn, 349, 38);
      delay(200);
      irsend.sendRaw(powerOn, 349, 38);
      Serial.println("Enviou");
      server.send(200, "ligou");
    } else {  //  password don't match
      server.send(401, "text/plain", "401: Unauthorized");
    }
  });

  server.on("/off", []() {
       if (server.arg("password") == "<password>") {  // If password are correct
        delay(200);
        irsend.sendRaw(powerOff, 351, 38);
        delay(200);
        irsend.sendRaw(powerOff, 351, 38);
        Serial.println("Enviou");
        server.send(200);
      } else {  //  password don't match
        server.send(401, "text/plain", "401: Unauthorized");
      }
  });

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
