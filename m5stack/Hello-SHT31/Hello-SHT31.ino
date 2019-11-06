/**
 ** Name: Hello-SHT31.ino
 *
 * M5Stackで温湿度センサ(SHT31)を使うサンプル
 * I2Cなので、PORT Aにつないで用いる
 *
 * 参考: https://poche-magique.com/2018/05/09/m5stack_grovesht31/
 */

#include <Arduino.h>
#include <M5Stack.h>
#include <Wire.h>
#include "SHT31.h"

SHT31 sht31 = SHT31();

void setup() {
  // Initialize the M5Stack object
  M5.begin();

  Serial.println("begin...");
  sht31.begin();
}

void loop() {
  float temp = sht31.getTemperature();
  float hum = sht31.getHumidity();
  Serial.print("Temp = ");
  Serial.print(temp);
  Serial.println(" C");  // The unit for  Celsius because original arduino don't
                         // support speical symbols
  Serial.print("Hum = ");
  Serial.print(hum);
  Serial.println("%");
  Serial.println();

  M5.Lcd.printf("Temp. = %f  Hum. = %f\n", temp, hum);

  delay(1000);
}
