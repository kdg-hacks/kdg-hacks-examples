// Wio LTE/M1 SORACOMのmetaデータを受け取る

#include <WioCellLibforArduino.h>
#include <ArduinoJson.h>

#define APN               "soracom.io"
#define USERNAME          "sora"
#define PASSWORD          "sora"

#define WEBURL            "http://metadata.soracom.io/v1/subscriber"  // SORACOM メタデータサービスのURL
// #define WEBURL            "http://metadata.soracom.io/v1/userdata"  // SORACOM メタデータサービスのURL（ユーザーデータを取得する場合）

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
  
  char data[3000];  // レスポンスを格納できるだけの容量が必要！
  int status;

  SerialUSB.println("GET " WEBURL);
  memset(data,0,sizeof(data));
  status = Wio.HttpGet(WEBURL, data, sizeof(data));
  
  SerialUSB.print("RecvBytes:");
  SerialUSB.println(status);

  if(status > 0)
  {
    SerialUSB.println(data);
    json_parse(data);
  }

  SerialUSB.println("### Wait.");
  delay(INTERVAL);
}

void json_parse(char *json){
 StaticJsonBuffer<4000> jsonBuffer;

 JsonObject& root = jsonBuffer.parseObject(json);
 if (!root.success()) {
   SerialUSB.println("parseObject() failed");
   return;
 }
 const char* ipAddress = root["ipAddress"];
 SerialUSB.println(ipAddress);
}
