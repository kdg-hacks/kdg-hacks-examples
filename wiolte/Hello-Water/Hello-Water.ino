// Board ver 1.2.0 / Library 1.7.0 OK 
// GROVE 水センサを繋いだ場合のサンプルプログラム

#include <WioCellLibforArduino.h>

// #define WATER_SENSOR (WIO_D38)
// #define WATER_SENSOR (WIO_D20)

#define INTERVAL (1000)

WioCellular Wio;

void setup() {
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---");

  Wio.Init();

  // GROVE端子へ電源供給を行う(D38以外向け）
  Wio.PowerSupplyGrove(true);

  pinMode(WATER_SENSOR, INPUT);
}

void loop() {
  SerialUSB.println(isExposedToWater());
  delay(INTERVAL);
}

boolean isExposedToWater() {
  if(digitalRead(WATER_SENSOR) == LOW)
    return true;
  else return false;
}
