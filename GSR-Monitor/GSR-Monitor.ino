/*
 * Grove GSR Sensor をシリアルで眺めるサンプル
 * センサーは、Analog(A4) に繋ぐ。可変抵抗をちょっと触るだけで値が変化するので注意が必要。
 * http://wiki.seeedstudio.com/Grove-GSR_Sensor/
 */

#include <WioCellLibforArduino.h>

#define GSR (WIO_A4)

WioCellular Wio;
int sensorValue = 0;
int gsr_average = 0;

void setup() {
  delay(200);

  SerialUSB.begin(9600);
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
  long sum = 0;
  for (int i = 0; i < 10; i++) {
    sensorValue = analogRead(GSR);
    sum += sensorValue;
    delay(5);
  }
  
  gsr_average = sum/10;
//  int hr = ((1024 + 2 * gsr_average) * 10000) / (512 - gsr_average);
//  SerialUSB.print("Serial Value = "); 
  SerialUSB.println(gsr_average);
//  SerialUSB.print("Human Resistance = "); 
//  SerialUSB.println(hr);
//  delay(500);
}
