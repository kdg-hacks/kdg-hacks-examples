// Board ver 1.2.0 / Library 1.7.0 OK 
// Wio LTE/M1 I2C端子に Grove I2C touch sensor v1.2bを繋いだ場合のサンプルプログラム

#include <WioCellLibforArduino.h>
#include "i2c_touch_sensor.h"
#include "MPR121.h"

WioCellular Wio;
i2ctouchsensor touchsensor;

long previousMillis = 0;
long interval = 1000;

void setup() {
  // デバッグ用シリアル初期化
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---");

  SerialUSB.println("### I/O Initialize.");
  Wio.Init();

  // GROVE端子へ電源供給を行う(D38以外向け）
  Wio.PowerSupplyGrove(true);

  // needed by the GroveMultiTouch lib
  WireI2C.begin();

  // initialize the feelers
  touchsensor.initialize();
}

void loop() {
  long currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    touchsensor.getTouchState();
  }
  for (int i = 0; i < 12; i++) {
    if (touchsensor.touched & (1 << i)) {
      SerialUSB.print("pin ");
      SerialUSB.print(i);
      SerialUSB.println(" was  touched");
    }
  }
}
