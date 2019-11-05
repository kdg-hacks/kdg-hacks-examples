#include "DHT.h"
#include <Arduino.h>
#include <M5Stack.h>
//#include <Wire.h>

#define DHTPIN 22     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    M5.begin();
    dht.begin();
}

void loop() 
{
  float temp = dht.readTemperature();
  float hum =  dht.readHumidity();
  M5.Lcd.printf("Temp. = %f  Hum. = %f\n", temp,hum);
  delay(1500);
}
