// Board ver 1.2.0 / Library 1.7.0 OK 
// Wio LTE/M1 I2C端子にTemperature&Humidty Sensor(DHT31)を繋いだ場合のサンプルプログラム

#include <WioCellLibforArduino.h>
#include "SHT31.h"

WioCellular Wio;
SHT31 sht31 = SHT31();

void setup() {
  // デバッグ用シリアル初期化
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---");

  // Wi LTEoの初期化
  Wio.Init();

  // GROVE端子へ電源供給を行う(D38以外向け）
  Wio.PowerSupplyGrove(true);

  sht31.begin();
}

void loop() {
  float temp = sht31.getTemperature();
  float hum = sht31.getHumidity();
  SerialUSB.print("Temp = "); 
  SerialUSB.print(temp);
  SerialUSB.println(" C"); //The unit for  Celsius because original arduino don't support speical symbols
  SerialUSB.print("Hum = "); 
  SerialUSB.print(hum);
  SerialUSB.println("%"); 
  SerialUSB.println();
  delay(1000);
}
