#include <SPI.h>
#include <MFRC522.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define SS_PIN D4
#define RST_PIN D2

MFRC522 rfid(SS_PIN, RST_PIN);

String ssid = "TP-LINK_ED0514", password = "123universo";
long timeUntilNextRequest;

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
  Serial.print("WiFi connected!");
  Serial.println("");
}

void httpRequest() {
  if(WiFi.status() == WL_CONNECTED && millis() >= timeUntilNextRequest ) {
    HTTPClient http;
    http.begin("http://192.168.3.123:3000/");
    int httpCode = http.GET();
  
    if(httpCode > 0) {
      String payload = http.getString();
      DynamicJsonDocument doc(1024);
      DeserializationError err = deserializeJson(doc, payload);
      
      if(err) {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(err.c_str());
      }

      String data = doc["data"];
      
      Serial.println(data);
    }
  
    http.end();
  }
  timeUntilNextRequest = millis() + 10000;
}

void loop() {
  // put your main code here, to run repeatedly:
  readID();
}

void readID(){
  if(!rfid.PICC_IsNewCardPresent()) return;
  if(!rfid.PICC_ReadCardSerial()) return;
  Serial.println("");

  Serial.print("UID: ");
  String content = "";
  byte letra;
  
  for(byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
    content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(rfid.uid.uidByte[i], HEX));
  }

  rfid.PICC_HaltA();
}
