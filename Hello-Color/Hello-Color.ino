// Board ver 1.2.0 / Library 1.7.0 OK 
#include <WioCellLibforArduino.h>
#include "GroveColorV2.h"

#define I2C_ADDRESS   (0x53)
#define REG_POWER_CTL (0x2d)
#define REG_DATAX0    (0x32)

// センサが色情報を集めるインターバルを、2.4ms/24ms/50ms/101ms/154ms/700msから選択できます。サイクルごとに収集可能な色情報カウントの最大値が異なります。必要に応じてコメントアウトしてください。
// #define SENSOR_INTEGRATION_TIME TCS34725_INTEGRATIONTIME_2_4MS         /**<  2.4ms - 1 cycle    - Max Count: 1024  */
// #define SENSOR_INTEGRATION_TIME TCS34725_INTEGRATIONTIME_24MS          /**<  24ms  - 10 cycles  - Max Count: 10240 */
// #define SENSOR_INTEGRATION_TIME TCS34725_INTEGRATIONTIME_50MS          /**<  50ms  - 20 cycles  - Max Count: 20480 */
// #define SENSOR_INTEGRATION_TIME TCS34725_INTEGRATIONTIME_101MS         /**<  101ms - 42 cycles  - Max Count: 43008 */
// #define SENSOR_INTEGRATION_TIME TCS34725_INTEGRATIONTIME_154MS         /**<  154ms - 64 cycles  - Max Count: 65535 */
#define SENSOR_INTEGRATION_TIME TCS34725_INTEGRATIONTIME_700MS            /**<  700ms - 256 cycles - Max Count: 65535 */

// センサの光に対する感度を、1倍/4倍/16倍/60倍から選択できます。
// #define SENSOR_GAIN TCS34725_GAIN_1X   /**<  No gain  */
// #define SENSOR_GAIN TCS34725_GAIN_4X   /**<  4x gain  */
// #define SENSOR_GAIN TCS34725_GAIN_16X  /**<  16x gain */
#define SENSOR_GAIN TCS34725_GAIN_60X     /**<  60x gain */

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

  // カラーセンサーの電源ON・初期化
  color.begin();

  // カラーセンサの感度を設定
  color.setGain(SENSOR_GAIN);

  // カラーセンサが色情報を集めるインターバルを設定
  color.setIntegrationTime(SENSOR_INTEGRATION_TIME);
}

void loop()
{
    // 取得した色情報(赤、緑、青、透明度)
    uint16_t red, green, blue, clear;

    while(1)
    {
        // 色情報を取得して出力
        color.getRawData(&red, &green, &blue, &clear);
        SerialUSB.print("The RGBA value are: RGBA( ");
        SerialUSB.print(red);
        SerialUSB.print(", ");
        SerialUSB.print(green);
        SerialUSB.print(", ");
        SerialUSB.print(blue);
        SerialUSB.print(", ");
        SerialUSB.print(clear);
        SerialUSB.println(" )");

        // 取得した色情報から、照度を出力
        SerialUSB.print("The lux is: Lux( ");
        SerialUSB.print(color.calculateLux(red, green, blue));
        SerialUSB.println(" )");

        // 取得した色情報から、色温度を出力
        SerialUSB.print("The color temperature is: Color Temperature( ");
        SerialUSB.print(color.calculateColorTemperature(red, green, blue));
        SerialUSB.println(" )");

        color.clearInterrupt();
    }
}
