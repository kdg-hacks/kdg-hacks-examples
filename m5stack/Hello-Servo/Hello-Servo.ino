/**
 ** Name: Hello-Servo.ino
 *
 * サーボモータを操作するサンプル
 *
 * TODO：補足を追加する必要あり。
 * PortBに直接接続すると、OutputをサポートしないG36に接続してしまう。
 *
 *
 * 参考：https://botalab.tech/m5stack_drive_rcservo/
 */

#include <M5Stack.h>
#include "utility/M5Servo.h"

M5Servo myServo;

// the setup routine runs once when M5Stack starts up
void setup(){

  // Initialize the M5Stack object
  M5.begin();

  // LCD display
  M5.Lcd.print("Servo test");

  myServo.attach(5);
}

// the loop routine runs over and over again forever
void loop() {

  for (int i = -90; i <= 90; i+=5){
    myServo.write(i);
    uint8_t v = map(i,-90,90,0,100);
    delay(15);
  }

  for (int i = 90; i >= -90; i-=5){
    myServo.write(i);
    uint8_t v = map(i,-90,90,0,100);
    delay(15);
  }

  delay(300);
}