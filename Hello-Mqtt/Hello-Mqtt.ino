// Wio LTE/M1 SORACOM beamを使ってみる
// MQTTでAWS IoTにアクセス

#include <WioCellLibforArduino.h>
#include <WioCellularClient.h>
#include <PubSubClient.h>		// https://github.com/SeeedJP/pubsubclient
#include <stdio.h>

#define APN               "soracom.io"
#define USERNAME          "sora"
#define PASSWORD          "sora"

#define MQTT_SERVER_HOST  "beam.soracom.io"
#define MQTT_SERVER_PORT  (1883)

#define ID                "wioltem"
#define OUT_TOPIC         "topic/Test"
#define IN_TOPIC          "topic/Test/#"

#define INTERVAL          (120000)

boolean setup_flag = false;

WioCellular Wio;
WioCellularClient WioClient(&Wio);
PubSubClient MqttClient;

void setup() {
  // デバッグ用シリアル初期化
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---------------------------------------------------");
  
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
    SerialUSB.println("### ERROR! ###");
    return;
  }

  // MQTTサーバにアクセスする
  SerialUSB.println("### Connecting to MQTT server \"" MQTT_SERVER_HOST "\"");
  MqttClient.setServer(MQTT_SERVER_HOST, MQTT_SERVER_PORT);
  MqttClient.setCallback(callback);
  MqttClient.setClient(WioClient);
 
  if (!MqttClient.connect(ID)) {
    SerialUSB.println("### ERROR! ###");
    return;
  }

  // 受信するトピックを要求する
  MqttClient.subscribe(IN_TOPIC);

  SerialUSB.println("### Setup completed.");
  
  setup_flag = true;
}

void loop() {
  if(setup_flag == false)
  {
    delay(5000);
    setup();
    return;
  }

  // 起動してからの時間をpublishする
  char data[100];
  sprintf(data, "{\"uptime\":%lu}", millis() / 1000);
  SerialUSB.print("Publish:");
  SerialUSB.print(data);
  SerialUSB.println("");
  MqttClient.publish(OUT_TOPIC, data);

  // 休憩（ただし、受信できるように、delay関数は使わないようにする）
  unsigned long next = millis();
  while (millis() < next + INTERVAL)
  {
    MqttClient.loop();
  }
}

// IN_TOPICを受信した時に呼ばれるコールバック関数
void callback(char* topic, byte* payload, unsigned int length) {
  // 受信したトピックを表示する
  SerialUSB.print("("); 
  SerialUSB.print(topic);
  SerialUSB.print(")Subscribe:");
  for (int i = 0; i < (int)length; i++) {
    SerialUSB.print((char)payload[i]);
  }
  SerialUSB.println("");
}
