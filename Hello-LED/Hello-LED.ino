#include <WioCellLibforArduino.h>

WioCellular Wio;

void setup() {
  // デバッグ用シリアル初期化
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---");

  // Wi LTEoの初期化
  Wio.Init();

  // フルカラーLEDに電源を投入する
  Wio.PowerSupplyLed(true);
  delay(500);

  // とりあえず消灯
  Wio.LedSetRGB(0, 0, 0);
}

void loop() {
  // 赤を光らせる
  Wio.LedSetRGB(255, 0, 0);
  SerialUSB.println("ON");
  
  // 1000ms秒待つ
  delay(1000);
  
  // 消灯する
  Wio.LedSetRGB(0, 0, 0);
  SerialUSB.println("OFF");

  // 1000ms秒待つ
  delay(1000);
}
