// 電話のパラメータを取得してみよう！

#include <WioCellLibforArduino.h>

#define INTERVAL  (5000)

WioCellular Wio;

void setup() {
  // デバッグ用シリアル初期化
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---");

  // Wi LTEoの初期化
  Wio.Init();

  // LTEモデムへ電源ON
  Wio.PowerSupplyCellular(true);
  delay(500);

  if (!Wio.TurnOnOrReset()) {
    SerialUSB.println("### ERROR! ###");
    return;
  }
  
  SerialUSB.println("Ready!!!");
}

void loop() {
  char imei[30];
  char imsi[30];
  char tel[30];

  // IMEIを取得してみよう
  if(Wio.GetIMEI(imei, sizeof(imei)) > 0){
    SerialUSB.print("imei=");
    SerialUSB.println(imei);
  }

  // IMSIを取得してみよう
  if(Wio.GetIMSI(imsi, sizeof(imsi)) > 0){
    SerialUSB.print("imsi=");
    SerialUSB.println(imsi);
  }

  // 電話番号を取得してみよう(Wio LTE-M1では取得出来ない！？）
  if(Wio.GetPhoneNumber(tel, sizeof(tel)) > 0){
    SerialUSB.print("tel=");
    SerialUSB.println(tel);
  }
  
  delay(INTERVAL);
}
