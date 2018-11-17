// Wio LTE/M1 D38 or D20端子にGROVE Buzzer v1.2を繋いだ場合のサンプルプログラム

#include <WioCellLibforArduino.h>

// 接続したブザーの位置に合わせて、下記のコメントを付けたり、外したりしてください。
// #define BUZZER WIO_D38
// #define BUZZER WIO_D20

WioCellular Wio;

void setup() {
  // デバッグ用シリアル初期化
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---");

  // Wio LTEの初期化
  Wio.Init();

  // GROVE端子へ電源供給を行う(D38以外向け）
  Wio.PowerSupplyGrove(true);
  
  // ポートをDIGITAL OUTPUTモードにする
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  // ブザーON
  digitalWrite(BUZZER, HIGH);
  SerialUSB.println("ON");
  delay(100);

  // ブザーOFF
  digitalWrite(BUZZER, LOW);
  SerialUSB.println("OFF");
  delay(1000);
}
