// Board ver 1.2.0 / Library 1.7.0 OK 
// NeoPixel RGB TYPE LED 1m/60LED

#include <WioCellLibforArduino.h>

// 接続するポート
// #define PIN (WIO_D38)
// #define PIN (WIO_D20)

#define MAX_LED 60        // テープLEDの数

extern "C" void DelayLoop(int32_t iterations);

WioCellular Wio;

int count = 0;
  
void setup() {
  // デバッグ用シリアル初期化
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---");

  // Wi LTEoの初期化
  Wio.Init();

  pinMode(PIN, OUTPUT);
  
  // GROVE端子へ電源供給を行う(D38以外向け）
  Wio.PowerSupplyGrove(true);
  delay(100);
  LED_RESET();
  delay(2000);
}

void loop() {
  for(int i = 0 ; i < MAX_LED ; i++)
  {
    if((i % 2) == 0)
    {
      SetSingleLED(0x00,0x10,0x00);
    }
    else
    {
      SetSingleLED(0x00,0x00,0x10);
    }
  }

  delay(150);

  for(int i = 0 ; i < MAX_LED ; i++)
  {
    if((i % 2) == 0)
    {
      SetSingleLED(0x00,0x00,0x10);
    }
    else
    {
      SetSingleLED(0x00,0x10,0x00);
    }
  }

  delay(150);

  count++;

  if(count > 20)
  {
    LED_RESET();
    delay(2000);
    count = 0;
  }
}

void SetBit(bool on)
{
  if (!on) {
    LED_GPIO_HIGH();
    DelayLoop(30);
    LED_GPIO_LOW();
    DelayLoop(65);
  }
  else {
    LED_GPIO_HIGH();
    DelayLoop(60);
    LED_GPIO_LOW();
    DelayLoop(50);
  }
}

void LED_GPIO_LOW(){
  digitalWrite(PIN,LOW);
}

void LED_GPIO_HIGH(){
  digitalWrite(PIN,HIGH);
}

void SetByte(uint8_t val)
{
  for (int i = 0; i < 8; i++) {
    SetBit(val & (1 << (7 - i)));
  }
}

// LEDを消灯させる
void LED_RESET()
{
  for(int i = 0 ; i < MAX_LED ; i++)
  {
    SetByte(0x0);
    SetByte(0x0);
    SetByte(0x0);
  }
}

// 色をセットする。
void SetSingleLED(uint8_t r, uint8_t g, uint8_t b)
{
  SetByte(g);
  SetByte(r);
  SetByte(b);
}
