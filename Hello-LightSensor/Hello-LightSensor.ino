// Grove 光 センサー をシリアルで眺めるサンプル
// センサーは、Analog(A4) に繋ぐと動きます。
// 参考URL: http://wiki.seeedstudio.com/Grove-Light_Sensor/

#include <WioCellLibforArduino.h>

#define GSR (WIO_A4)

WioCellular Wio;

void setup() {
  delay(200);

  // デバッグ用シリアル初期化
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---------------------------------------------------");

  SerialUSB.println("### I/O Initialize.");
  Wio.Init();
  
  SerialUSB.println("### Power supply ON.");
  Wio.PowerSupplyGrove(true);

  delay(500);
  pinMode(GSR, INPUT_ANALOG);
  SerialUSB.println("### Setup completed.");
}

void loop() {
  // 1秒毎にGrove 光 センサーの値をシリアルに出力
  // Wio LTE M1/NB1(BG96)のADCが12bitのため、0(暗い)〜4095(明るい)までの値が取得可能
  int sensorValue = analogRead(GSR);
  SerialUSB.println(sensorValue);
  delay(1000);
}
