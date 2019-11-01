// Board ver 1.2.0 / Library 1.7.0 OK 
// Grove 光 センサー をシリアルで眺めるサンプル
// 参考URL: http://wiki.seeedstudio.com/Grove-Light_Sensor/

#include <WioCellLibforArduino.h>

// #define LIGHT (WIO_A4)
// #define LIGHT (WIO_A6)

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
  pinMode(LIGHT, INPUT_ANALOG);
  SerialUSB.println("### Setup completed.");
}

void loop() {
  // 1秒毎にGrove 光 センサーの値をシリアルに出力
  // Wio LTE M1/NB1(BG96)のADCが12bitのため、0(暗い)〜4095(明るい)までの値が取得可能
  int sensorValue = analogRead(LIGHT);
  SerialUSB.println(sensorValue);
  delay(1000);
}
