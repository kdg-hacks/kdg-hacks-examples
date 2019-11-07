/**
 ** Name: Hello-Buzzer.ino
 *
 * M5StackでGrove-Buzzerを使うサンプル
 * PORT Aにつないで用いる
 *
 * 参考: http://wiki.seeedstudio.com/Grove-Buzzer/
 */

void setup() {
  // put your setup code here, to run once:
    pinMode(22, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(22, HIGH);//音がなる
  delay(1000);
  digitalWrite(22, LOW);//音が消える
  delay(1000);
}
