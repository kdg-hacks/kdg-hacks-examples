// Wio LTE/M1 D38 or D20端子にGROVE BUTTON(P)を繋いだ場合のサンプルプログラム

#include <WioCellLibforArduino.h>

// 接続したボタンの位置に合わせて、下記のコメントを付けたり、外したりしてください。
#define BTN WIO_D38
// #define BTN WIO_D20

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

  // ポートをDIGITAL INPUTモードにする
  pinMode(BTN, INPUT);
}

void loop() {
  // ボタンの状態を読み取る
  int btn = digitalRead(BTN);
  
  // 読み取った値を表示する
  SerialUSB.println(btn);

  // 1秒間お休み
  delay(1000);
}
