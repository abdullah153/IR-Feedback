#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
int  MyData;
const int redPin = 13; 
const int greenPin = 15;
IRrecv irrecv(14);
decode_results results;
void setup() {
  MyData = 0;
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin("Wifi Username", "Wifi Password");
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
    Serial.println("");
    Serial.print("connected to ");
    Serial.print("IP Adress: ");
    Serial.println(WiFi.localIP());
    irrecv.enableIRIn();
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {
    digitalWrite(greenPin,HIGH);
    WiFiClient client;
    HTTPClient http;
    if (irrecv.decode(&results)) {      
       Serial.println("You Receive This:");
       MyData = (results.value);
       digitalWrite(redPin,HIGH);
       delay(250);
       digitalWrite(redPin,LOW); 
       Serial.println(MyData);      

    if (MyData == IR readind number ){ 
      delay(250);
      Serial.print("[HTTP] begin...\n");
      http.begin(client, "API");    // API of the device you want to control
      http.setAuthorization("username","password"); // for your hub
    Serial.print("[HTTP] GET...\n");
    int httpCode = http.GET();    
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
    http.end();
    }
    // Repeat this code for all devices or buttoms you want to control it
     else {
      Serial.printf("Failed\n");
      http.end();
    }
  delay(250);
  Serial.println("Ready for next Signal\n");
  irrecv.resume();
  }
  
  if (WiFi.status() != WL_CONNECTED) {
    digitalWrite(greenPin,LOW);
  } 
  } 
}
