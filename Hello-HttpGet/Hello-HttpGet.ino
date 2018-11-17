// Wio LTE/M1 が直接インターネットサービスに繋がるか？

#include <WioCellLibforArduino.h>

#define APN               "soracom.io"
#define USERNAME          "sora"
#define PASSWORD          "sora"

// #define WEBURL       "https://www.google.com/"
// #define WEBURL       "http://www.kddi.com/"
// #define WEBURL       "http://106.162.242.107"
#define WEBURL       "http://beam.soracom.io:8888/"


#define INTERVAL          (30000)

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
  delay(500);

  SerialUSB.println("### Turn on or reset.");
  if (!Wio.TurnOnOrReset()) {
    SerialUSB.println("### ERROR! ###");
    return;
  }

  SerialUSB.println("### Connecting to \"" APN "\".");
  Wio.SetSelectNetwork(WioCellular::SELECT_NETWORK_MODE_MANUAL_IMSI);
  if (!Wio.Activate(APN, USERNAME, PASSWORD)) {
    SerialUSB.println("### ERROR! ###");
    return;
  }

}

void loop() {
  char data[100];
  int status;

  SerialUSB.println("GET " WEBURL);
  status = Wio.HttpGet(WEBURL, data, 100);
  
  SerialUSB.print("RecvBytes:");
  SerialUSB.println(status);

err:
  SerialUSB.println("### Wait.");
  delay(INTERVAL);
}
