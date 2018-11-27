// Wio LTE/M1 赤外線リモコン(エアコン操作)サンプル
// Wio LTE/M1 -> SORACOM Beam -> au HOMEサーバ -> 赤外線リモコンへの赤外線信号送信リクエストの例

#include <WioCellLibforArduino.h>

#define APN               "soracom.io"
#define USERNAME          "sora"
#define PASSWORD          "sora"

#define WEBURL            "http://beam.soracom.io:8888/smarthome/execute/commands"
#define INTERVAL          (120000)

boolean send_flag = false;
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
    SerialUSB.println("### SetSelectNetwork MANUAL_IMSI ###");
    Wio.SetSelectNetwork(WioCellular::SELECT_NETWORK_MODE_MANUAL_IMSI);
  #endif

  #ifdef ARDUINO_WIO_3G
    SerialUSB.println("### SetSelectNetwork AUTOMATIC ###");
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
  // 1回のみ赤外線信号送信リクエストを実施
  if(send_flag)
  {
    return;
  }

  // 初期化未実施の場合初期化を実施
  if(setup_flag == false)
  {
    delay(5000);
    setup();
    return;
  }
  
  char data[100];
  int status;
  
  SerialUSB.println("### IR Remocn Aircon-Power-Signal Post.");

  // エアコンの暖房ON -> 冷房ON -> OFF操作リクエスト
  sprintf(data, "[\"heat_on\", \"cool_on\", \"aircon_off\"]");
  
  SerialUSB.print("Post:");
  SerialUSB.print(data);
  SerialUSB.println("");
  
  if (Wio.HttpPost(WEBURL, data, &status)) {
    SerialUSB.print("Status:");
    SerialUSB.println(status);
    send_flag = true;
  }

  SerialUSB.println("### Wait.");
  delay(INTERVAL);
}
