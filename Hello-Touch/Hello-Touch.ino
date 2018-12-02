// Wio LTE/M1 UART端子に Grove I2C touch sensor v1.2bを繋いだ場合のサンプルプログラム
//
// 実行前に I2C Touch Sensor Library のインストールと改修が必要です。
//
// 1. 以下よりライブラリをzip形式でダウンロード
//　https://github.com/Seeed-Studio/Grove_I2C_Touch_Sensor
//
// 2. Arduinoに上記ライブラリをインクルード(zip形式のまま)
//   -> "Arduino/libraries/Grove_I2C_Touch_Sensor-master"というパスでインクルードされます。
//
// 3. ライブラリを以下のように改修
//  3-1. Arduino/libraries/Grove_I2C_Touch_Sensor-master/i2c_touch_sensor.h の改修方法
//      以下の"."を"_"に変更
//　　　   #ifndef i2c_touch.sensor_h
//        #define i2c_touch.sensor_h
//
//  3-2. Arduino/libraries/Grove_I2C_Touch_Sensor-master/i2c_touch_sensor.cpp の改修方法
//   3-2-1. includeファイルを以下のみに変更
//       #include <WioCellLibforArduino.h>
//       #include "i2c_touch_sensor.h"
//       #include "mpr121.h"
//   3-2-2. コード置換
//       "Wire." を "WireI2C." に変更


#include <WioCellLibforArduino.h>
#include <i2c_touch_sensor.h>
#include <MPR121.h>

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
