#include "Wire.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_BME280.h"
#include <WiFi.h>
#include <HTTPClient.h>
 

#define SEALEVELPRESSURE_HPA (1013.25)
 
Adafruit_BME280 bme; // I2C

const char* ssid = "ssid";
const char* password = "pass";

String serverName = "http://192.168.1.71/api/temperature/";

unsigned long delayTime;
 
void setup() {
    Serial.begin(9600);
    Serial.println(F("BME280 test"));
 
    bool status;
    
    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    status = bme.begin(0x76);  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }

    WiFi.begin(ssid, password);
  
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi...");
    } 
  
    Serial.println("Connected to the WiFi network");
    
    delayTime = 10000;
 
}
 
 
void loop() { 

  HTTPClient client;
  client.begin(serverName + bme.readTemperature());
  
  client.addHeader("Content-Type", "text/plain");
  int httpCode = client.PUT("Put response");
  Serial.println(bme.readTemperature());
  
  if(httpCode>0){
    
    Serial.println(httpCode);
    Serial.println("Ok");  
 
  }else{
 
    Serial.print("Error on sending PUT Request: ");
    Serial.println(httpCode);
  }
  
 
  client.end();
  delay(10000);
}
 

 
