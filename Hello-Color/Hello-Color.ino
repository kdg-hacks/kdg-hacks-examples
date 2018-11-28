#include <WioCellLibforArduino.h>
#include "GroveColorV2.h"

#define I2C_ADDRESS   (0x53)
#define REG_POWER_CTL (0x2d)
#define REG_DATAX0    (0x32)

WioCellular Wio;
GroveColorV2 color;

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
  WireI2C.begin();
  color.begin();
  color.setGain(TCS34725_GAIN_16X);
  color.setIntegrationTime(TCS34725_INTEGRATIONTIME_24MS);
}

void loop()
{
    uint16_t red, green, blue, alpha;

    while(1)
    {
        color.getRawData(&red, &green, &blue, &alpha);
        SerialUSB.print("The RGBA value are: RGBA( ");
        SerialUSB.print(red);
        SerialUSB.print(", ");
        SerialUSB.print(green);
        SerialUSB.print(", ");
        SerialUSB.print(blue);
        SerialUSB.print(", ");
        SerialUSB.print(alpha);
        SerialUSB.println(" )");
        color.clearInterrupt();
    }
}
