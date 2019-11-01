// Wio LTE/M1 SORACOM funnelを使ってみる
// AWS IoT Core向けのPOSTリクエストの例

#include <WioCellLibforArduino.h>

#define APN               "soracom.io"
#define USERNAME          "sora"
#define PASSWORD          "sora"

#define WEBURL            "http://funnel.soracom.io"
#define INTERVAL          (120000)

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
  if(setup_flag == false)
  {
    delay(5000);
    setup();
    return;
  }
  
  char data[100];
  int status;
  
  SerialUSB.println("### Post.");
  
  sprintf(data, "{\"value1\":\"uptime %lu\"}", millis() / 1000);
  
  SerialUSB.print("Post:");
  SerialUSB.print(data);
  SerialUSB.println("");
  
  if (Wio.HttpPost(WEBURL, data, &status)) {
    SerialUSB.print("Status:");
    SerialUSB.println(status);
  }

  SerialUSB.println("### Wait.");
  delay(INTERVAL);
}
