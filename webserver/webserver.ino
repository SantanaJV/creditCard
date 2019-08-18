#include <SPI.h>
#include <MFRC522.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

#define SS_PIN D4
#define RST_PIN D2

ESP8266WebServer server(80);
MFRC522 rfid(SS_PIN, RST_PIN);
DynamicJsonDocument data(1024);

String currentRfid = "";
String rfidPayload = "";
String ssid = "TP-LINK_ED0514", password = "123universo";
long timeUntilNextRequest;
bool loggedIn = false;

void handleRoot();
void handleLogin();
void handleMain();
void handleNotFound();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  SPI.begin();
  rfid.PCD_Init();
  
  Serial.print("Connecting on ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(250);
  }
  Serial.println("");
  Serial.print("WiFi connected! IP:");
  Serial.println(WiFi.LocalIP());

  if(MDNS.begin("esp8266")) {
    Serial.println("mDNS started!");
  } else {
    Serial.println("Error setting up mDNS");
  }

  server.on("/", HTTP_GET, handleRoot);
  server.on("/", HTTP_POST, handleLogin);
  server.on("/main", HTTP_GET, handleMain);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("WebServer started!");
}

void loop() {
  // put your main code here, to run repeatedly:
  readID();
  server.handleClient();
}

void readID(){
  if(!rfid.PICC_IsNewCardPresent()) return;
  if(!rfid.PICC_ReadCardSerial()) return;
  Serial.println("");

  Serial.print("UID: ");
  String content = "";
  byte letra;
  
  for(byte i = 0; i < rfid.uid.size; i++) {
    content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(rfid.uid.uidByte[i], HEX));
  }

  Serial.println(content);
  currentRfid = content;
  requestRfidData();

  rfid.PICC_HaltA();
}

void requestRfidData() {
  if(WiFi.status() != WL_CONNECTED) return;

  HTTPClient http;

  String URL = "http://192.168.3.123:3000/";
  URL.concat(currentRfid);

  Serial.print("Requesting data from ");
  Serial.println(URL);

  http.begin(URL);
  int httpCode = http.GET();
  
  if(httpCode > 0) {
    rfidPayload = http.getString();

    DeserializationError err = deserializeJson(data, rfidPayload);
      
    if(err) {
      Serial.print(F("deserializeJson() failed with code "));
      Serial.println(err.c_str());
    }
      
    Serial.println(data);
  }
  
  http.end();  
}