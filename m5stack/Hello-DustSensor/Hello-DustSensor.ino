/** 
 *  Name: Hello-DustSensor.ino
 *  
 *  Wio LTE/M1 D38 or D20端子にGROVE Dust Sensorを繋いだ場合のサンプルプログラム
 *  このセンサーは、本来5Vで動作するセンサーなので、3.3VのWio
 *  LTE/M1では、不安定な動作の可能性が！
 *  
 *  PORT Bにつないで用いる。
 *  
 *  ref: https://windabaft.co.jp/blog_ceo/?p=463
 */

#include <Arduino.h>
#include <M5Stack.h>
#include <math.h>

#define DUST 36

unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000; // データシートの計測方法が30秒のため
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

void setup() {
  // M5Stackの初期化
  M5.begin();
  M5.Power.begin();

  Serial.begin(115200);

  // Disable the speaker noise(https://github.com/mauricecyril/Grove-Dust-Sensor-with-m5stack/blob/master/GroveDustSensor_m5stack.ino)
  dacWrite(25, 0);

  // デジタル入力モードに設定
  pinMode(DUST, INPUT);

  // 現在の値を格納する
  starttime = millis();

  M5.Lcd.println("START!!!");
}

void loop() {
  // 立ち下がりのパルスを計測する
  duration = pulseIn(DUST, LOW);
  
  lowpulseoccupancy = lowpulseoccupancy + duration;

  if ((millis() - starttime) > sampletime_ms)  // ３０秒毎に集計する
  {
    ratio = lowpulseoccupancy / (sampletime_ms * 10.0);
    concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio +
                    0.62;  // スペックシートの曲線から算出している

    // 測定結果を表示する
    Serial.print(lowpulseoccupancy);
    Serial.print(",");
    Serial.print(ratio);
    Serial.print(",");
    Serial.println(concentration);

    M5.Lcd.print("low pulse:");
    M5.Lcd.print(lowpulseoccupancy);
    M5.Lcd.print(", ratio:");
    M5.Lcd.print(ratio);
    M5.Lcd.print(", DSM501A:");
    M5.Lcd.println(concentration);

    // 変数を初期化
    lowpulseoccupancy = 0;
    starttime = millis();
  }
}
