// GROVE 水センサを繋いだ場合のサンプルプログラム

#include <WioCellLibforArduino.h>

#define WATER_SENSOR (WIO_D20)
#define INTERVAL (1000)

WioCellular Wio;

void setup() {
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---");

  Wio.Init();

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