// Board ver 1.2.0 / Library 1.7.0 OK 
// Wio LTE/M1 UART端子にGPS v1.2を繋いだ場合のサンプルプログラム

#include <WioCellLibforArduino.h>
#include "TinyGPS++.h"

TinyGPSPlus gps;

WioCellular Wio;

void setup() {
  // デバッグ用シリアル初期化
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---");

  // Wi LTEoの初期化
  Wio.Init();

  // GROVE端子へ電源供給を行う(D38以外向け）
  Wio.PowerSupplyGrove(true);

  SerialUART.begin(9600);
}

void loop() {
  if (SerialUART.available()) {
    int inByte = SerialUART.read();
    if(gps.encode(inByte)) {
      displayInfo();
    }
  }
}

void displayInfo()
{
  SerialUSB.print(F("Location: "));
  
  if (gps.location.isValid()) {
    SerialUSB.print(gps.location.lat(), 6);
    SerialUSB.print(F(","));
    SerialUSB.print(gps.location.lng(), 6);
  } else {
    SerialUSB.print(F("INVALID"));
  }

  SerialUSB.print(F("  Date/Time: "));
  
  if (gps.date.isValid()) {
    SerialUSB.print(gps.date.month());
    SerialUSB.print(F("/"));
    SerialUSB.print(gps.date.day());
    SerialUSB.print(F("/"));
    SerialUSB.print(gps.date.year());
  } else {
    SerialUSB.print(F("INVALID"));
  }

  SerialUSB.print(F(" "));
  
  if (gps.time.isValid()) {
    if (gps.time.hour() < 10) {
      SerialUSB.print(F("0"));
    }
    
    SerialUSB.print(gps.time.hour());
    SerialUSB.print(F(":"));
    
    if (gps.time.minute() < 10) {
      SerialUSB.print(F("0"));
    }
    
    SerialUSB.print(gps.time.minute());
    SerialUSB.print(F(":"));
    
    if (gps.time.second() < 10) {
      SerialUSB.print(F("0"));
    }

    SerialUSB.print(gps.time.second());
    SerialUSB.print(F("."));
    
    if (gps.time.centisecond() < 10) {
      SerialUSB.print(F("0"));
    }
    
    SerialUSB.print(gps.time.centisecond());
  } else {
    SerialUSB.print(F("INVALID"));
  }

  SerialUSB.println();
}
