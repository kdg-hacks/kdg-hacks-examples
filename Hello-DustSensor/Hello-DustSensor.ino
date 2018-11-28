// Wio LTE/M1 D38 or D20端子にGROVE Dust Sensorを繋いだ場合のサンプルプログラム
// このセンサーは、本来5Vで動作するセンサーなので、3.3VのWio LTE/M1では、不安定な動作の可能性が！

#include <WioCellLibforArduino.h>
#include <math.h>

// 接続したセンサーの位置に合わせて、下記のコメントを付けたり、外したりしてください。
// #define DUST WIO_D38
// #define DUST WIO_D20

WioCellular Wio;

unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

void setup() {
  // デバッグ用シリアル初期化
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---");

  // Wi LTEoの初期化
  Wio.Init();

  // GROVE端子へ電源供給を行う(D38以外向け）
  Wio.PowerSupplyGrove(true);

  // デジタル入力モードに設定
  pinMode(DUST,INPUT);
  
  // 現在の値を格納する
  starttime = millis();
}

void loop() 
{
  // 立ち下がりのパルスを計測する
  duration = pulseIn(DUST, LOW);
  lowpulseoccupancy = lowpulseoccupancy + duration;

  if ((millis()-starttime) > sampletime_ms) // ３０秒毎に集計する
  {
    ratio = lowpulseoccupancy/(sampletime_ms*10.0);
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // スペックシートの曲線から算出している

    // 測定結果を表示する
    SerialUSB.print(lowpulseoccupancy);
    SerialUSB.print(",");
    SerialUSB.print(ratio);
    SerialUSB.print(",");
    SerialUSB.println(concentration);

    // 変数を初期化
    lowpulseoccupancy = 0;
    starttime = millis();
  }
}
