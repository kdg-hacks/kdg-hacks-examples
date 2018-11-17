// Wio LTE/M1 I2C端子にGROVE 3-Axis Digiralを繋いだ場合のサンプルプログラム

#include <WioCellLibforArduino.h>

#define I2C_ADDRESS   (0x53)
#define REG_POWER_CTL (0x2d)
#define REG_DATAX0    (0x32)

WioCellular Wio;

void setup() {
  // デバッグ用シリアル初期化
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---");

  // Wi LTEoの初期化
  Wio.Init();

  // GROVE端子へ電源供給を行う(D38以外向け）
  Wio.PowerSupplyGrove(true);

  // 加速度センサーの電源ON
  AccelInitialize();
}

void loop() {
  float x;
  float y;
  float z;
  
  // 加速度センサーの値を読み取る
  AccelReadXYZ(&x, &y, &z);
  
  SerialUSB.print(x);
  SerialUSB.print(',');
  SerialUSB.print(y);
  SerialUSB.print(',');
  SerialUSB.println(z);

  delay(200);
}

// 加速度センサーの電源ON
void AccelInitialize() {
  WireI2C.begin();
  WireI2C.beginTransmission(I2C_ADDRESS);
  WireI2C.write(REG_POWER_CTL);
  WireI2C.write(0x08);
  WireI2C.endTransmission();
}

// 加速度センサーの値を読み取る
void AccelReadXYZ(float* x, float* y, float* z) {
  WireI2C.beginTransmission(I2C_ADDRESS);
  WireI2C.write(REG_DATAX0);
  WireI2C.endTransmission();

  if (WireI2C.requestFrom(I2C_ADDRESS, 6) != 6) {
    *x = 0;
    *y = 0;
    *z = 0;
    return;
  }

  int16_t val;
  ((uint8_t*)&val)[0] = WireI2C.read();
  ((uint8_t*)&val)[1] = WireI2C.read();
  *x = val * 2.0 / 512;
  ((uint8_t*)&val)[0] = WireI2C.read();
  ((uint8_t*)&val)[1] = WireI2C.read();
  *y = val * 2.0 / 512;
  ((uint8_t*)&val)[0] = WireI2C.read();
  ((uint8_t*)&val)[1] = WireI2C.read();
  *z = val * 2.0 / 512;
}
