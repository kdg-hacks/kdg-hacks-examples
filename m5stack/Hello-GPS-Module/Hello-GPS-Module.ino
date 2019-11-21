// M5STACK(GRAY) + GPS MODULEを組み合わせた
// サンプルアプリ(M5STACK Fireでは動作しないので注意）

// GPSの信号を解析するライブラリ（TinyGPS++）をインストール必要
// https://github.com/mikalhart/TinyGPSPlus

// M5STACKの液晶には、緯度経度等の情報は出力されないので、デバックコンソールを確認のこと。

#include <M5Stack.h>
#include <TinyGPS++.h>
 
TinyGPSPlus gps;

#define GPS Serial1

void setup() {
  M5.begin();
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.println(F("M5Stack GRAY + GPS MODULE")); 
  GPS.begin(9600, SERIAL_8N1, 16, 17);
}

void loop() {
  if(GPS.available()){
    if(gps.encode(GPS.read())) {
      displayInfo();
    }
  }
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }
 
  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }
 
  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }
 
  Serial.println();
}
