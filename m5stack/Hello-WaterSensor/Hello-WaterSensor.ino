/**
 ** Name: Hello-SHT31.ino
 *
 * M5StackでGrove - Water Sensorを使うサンプル
 * PORT Bにつないで用いる
 *
 * 参考: http://wiki.seeedstudio.com/Grove-Water_Sensor/
 */
#include <M5Stack.h>
#define WATER_SENSOR 36

void setup()
{
    // Initialize the M5Stack object
    M5.begin();
    pinMode(WATER_SENSOR, INPUT);
}
void loop()
{
    Serial.println(digitalRead(WATER_SENSOR));
    M5.Lcd.println(digitalRead(WATER_SENSOR));
    delay(1000);
}