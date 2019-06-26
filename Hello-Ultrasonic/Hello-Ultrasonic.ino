// Board ver 1.2.0 / Library 1.7.0 OK 
// Wio LTE/M1 D38 or D20端子にUltrasonic Ranger V2.0を繋いだ場合のサンプルプログラム

#include <WioCellLibforArduino.h>
#include "Ultrasonic.h"

// 接続した位置に合わせて、下記のコメントを付けたり、外したりしてください。
// #define US WIO_D38
// #define US WIO_D20

WioCellular Wio;
Ultrasonic UltrasonicRanger(US);

void setup() {
  // デバッグ用シリアル初期化
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---");

  // Wi LTEoの初期化
  Wio.Init();

  // GROVE端子へ電源供給を行う(D38以外向け）
  Wio.PowerSupplyGrove(true);
}

void loop() {
  long distance = UltrasonicRanger.MeasureInCentimeters();
  SerialUSB.print(distance);
  SerialUSB.println("[cm]");
  
  delay(200);
}
