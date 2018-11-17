// Wio LTE/M1 D38端子にGROVE BUTTON(P)を繋いだ場合のサンプルプログラム

#include <WioCellLibforArduino.h>

WioCellular Wio;

void setup() {
  // デバッグ用シリアル初期化
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---");

  // Wi LTEoの初期化
  Wio.Init();

  // D38のポートをDIGITAL INPUTモードにする
  pinMode(WIO_D38, INPUT);
}

void loop() {
  // ボタンの状態を読み取る
  int btn = digitalRead(WIO_D38);
  
  // 読み取った値を表示する
  SerialUSB.println(btn);

  // 1秒間お休み
  delay(1000);
}
