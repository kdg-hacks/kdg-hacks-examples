// Board ver 1.2.0 / Library 1.7.0 OK 
// GROVE PIRモーションセンサを繋いだ場合のサンプルプログラム

#include <WioCellLibforArduino.h>

// #define PIR_MOTION_SENSOR (WIO_D38)
// #define PIR_MOTION_SENSOR (WIO_D20)

#define INTERVAL (5000)

WioCellular Wio;

void setup() {
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---");

  Wio.Init();

  // GROVE端子へ電源供給を行う(D38以外向け）
  Wio.PowerSupplyGrove(true);

  pinMode(PIR_MOTION_SENSOR, INPUT);
}

void loop() {
  SerialUSB.println(isPeopleDetected());
  delay(INTERVAL);
}

boolean isPeopleDetected() {
  int sensorValue = digitalRead(PIR_MOTION_SENSOR);
  SerialUSB.println(sensorValue);
  if(sensorValue == HIGH) { //if the sensor value is HIGH?
    return true;//yes,return ture
  } else {
    return false;//no,return false
  }
}
