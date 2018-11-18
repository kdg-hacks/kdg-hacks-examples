// Wio LTE/M1 が直接インターネットサービスに繋がるか？

#include <WioCellLibforArduino.h>

#define APN               "soracom.io"
#define USERNAME          "sora"
#define PASSWORD          "sora"

#define WEBURL       "http://httpbin.org/ip"  // JSONでアクセス元IPアドレスを返すHP

// HTTPSだと失敗するので、SORACOMサービス使わないとダメだね。
// #define WEBURL       "https://httpbin.org/ip"
// #define WEBURL       "http://beam.soracom.io:8888/"

#define INTERVAL          (60000)

boolean setup_flag = false;

WioCellular Wio;

void setup() {
  // デバッグ用シリアル初期化
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---");

  SerialUSB.println("### I/O Initialize.");
  Wio.Init();
  
  SerialUSB.println("### Power supply ON.");
  Wio.PowerSupplyCellular(true);
  delay(1000);

  SerialUSB.println("### Turn on or reset.");
  if (!Wio.TurnOnOrReset()) {
    SerialUSB.println("### ERROR! ###");
    return;
  }
  
  #ifdef ARDUINO_WIO_LTE_M1NB1_BG96
    SerialUSB.println("### SetSelectNetwork ###");
    Wio.SetSelectNetwork(WioCellular::SELECT_NETWORK_MODE_MANUAL_IMSI);
  #endif

  #ifdef ARDUINO_WIO_3G
    SerialUSB.println("### SetSelectNetwork ###");
    Wio.SetSelectNetwork(WioCellular::SELECT_NETWORK_MODE_AUTOMATIC);
  #endif

  SerialUSB.println("### Connecting to \"" APN "\".");
  
  if (!Wio.Activate(APN, USERNAME, PASSWORD)) {
    SerialUSB.println("### APN SET ERROR! ###");
    return;
  }

  setup_flag = true;
}

void loop() {
  if(setup_flag == false)
  {
    delay(5000);
    // setup();
    return;
  }
  
  char data[3000];  // レスポンスを格納できるだけの容量が必要！
  int status;

  SerialUSB.println("GET " WEBURL);
  status = Wio.HttpGet(WEBURL, data, sizeof(data));
  
  SerialUSB.print("RecvBytes:");
  SerialUSB.println(status);

  if(status > 0)
  {
    data[status] = 0x0;
    SerialUSB.println(data);
  }

  SerialUSB.println("### Wait.");
  delay(INTERVAL);
}
