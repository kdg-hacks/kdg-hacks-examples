// Wio LTE/M1 D38 Ultrasonic Ranger V2.0
// I2CにN２エンジン
// を繋いだ場合のサンプルプログラム

#include <WioCellLibforArduino.h>
#include <ArduinoJson.h>
#include <WioCellularClient.h>
#include <PubSubClient.h>    // https://github.com/SeeedJP/pubsubclient
#include <stdio.h>
#include "Ultrasonic.h"

#define APN               "soracom.io"
#define USERNAME          "sora"
#define PASSWORD          "sora"

#define MQTT_SERVER_HOST  "beam.soracom.io"
#define MQTT_SERVER_PORT  (1883)

#define ID                "wioltem"
#define OUT_TOPIC         "topic/Test"
#define IN_TOPIC          "topic/Test/#"


#define INTERVAL          1500


// 接続した位置に合わせて、下記のコメントを付けたり、外したりしてください。 
#define US WIO_D38
// #define US WIO_D20

/**
 * N2TTS: 日本語音声合成Box制御用ラッパクラス
 */
class N2TTS
{
  static const uint8_t I2C_ADDRESS = 0x4f;

  /**
   * N2音声合成Boxへのコマンド定義
   */
  static const uint8_t CMD_SETVOLUME = 0x40;
  static const uint8_t CMD_GETVOLUME = 0x40;
  static const uint8_t CMD_SETSPEECHRATE = 0x41;
  static const uint8_t CMD_GETSPEECHRATE = 0x41;
  static const uint8_t CMD_SETPITCH = 0x42;
  static const uint8_t CMD_GETPITCH = 0x42;

  static const uint8_t CMD_SETTEXT = 0x67;
  static const uint8_t TEXTTYPE_PLAIN = 1;
  static const uint8_t CMD_START = 0x68;
  static const uint8_t CMD_GETLENGTH = 0x69;
  
private:
  // helper private method
  /**
   * N2音声合成Boxへのコマンド開始指示
   */
  const N2TTS * begin_cmd(uint8_t cmd) const
  {
    WireI2C.beginTransmission(N2TTS::I2C_ADDRESS);
    WireI2C.write(cmd);
    return this;    
  }
  /**
   * N2音声合成boxへのコマンド終了指示
   */
  const N2TTS * end_cmd() const {
    WireI2C.endTransmission();
    return this;
  }
public:
  /**
   * 音声合成Boxから設定されているパラメータを取得する
   * Parameter cmd: 取得するパラメータの識別用コマンド
   * Return: 取得したパラメータ、整数
   */
  int GetParam(uint8_t cmd) const
  {
    this->begin_cmd(cmd)->end_cmd();
    if (WireI2C.requestFrom(N2TTS::I2C_ADDRESS,4) != 4) {
      return -1;
    }
    int32_t val=0;
    ((uint8_t*)&val)[0] = WireI2C.read();
    ((uint8_t*)&val)[1] = WireI2C.read();
    ((uint8_t*)&val)[2] = WireI2C.read();
    ((uint8_t*)&val)[3] = WireI2C.read();

    return val;
  }
  /**
   * 音声合成Boxへ所定のパラメータを設定する
   * Parameter cmd: 設定するパラメータを示す識別用コマンド
   * Parameter val: 設定する値
   * Return: None
   */
  void SetParam(uint8_t cmd, int val)
  {
    this->begin_cmd(cmd);
    WireI2C.write(((uint8_t*)&val)[0]);
    WireI2C.write(((uint8_t*)&val)[1]);
    WireI2C.write(((uint8_t*)&val)[2]);
    WireI2C.write(((uint8_t*)&val)[3]);
    
    this->end_cmd();
  }
  // 以下パラメータ設定・取得用コマンドのラッパメソッド
  void setVolume(int vol) {
    this->SetParam(N2TTS::CMD_SETVOLUME,vol);
  }
  int getVolume() const {
    return this->GetParam(N2TTS::CMD_GETVOLUME);
  }
  void setSpeechRate(int srate) {
    this->SetParam(N2TTS::CMD_SETSPEECHRATE,srate);
  }
  int getSpeechRate() const {
    return this->GetParam(N2TTS::CMD_GETSPEECHRATE);
  }
  void setPitch(int pitch) {
    this->SetParam(N2TTS::CMD_SETPITCH, pitch);
  }
  int getPitch() const {
    return this->GetParam(N2TTS::CMD_GETPITCH);
  }
  /**
   * 指定されたテキストを音声合成Boxへ送信し、喋らせる
   * Parameter text: テキストデータ、Nullターミネートしている場合、lengthパラメータは不要
   * Parameter length: テキストデータの長さ
   * Return: サンプル数　（音声合成Boxは、32Kサンプル固定で音声再生を行なっている）
   */
  int Speak(const char *text, int length=-1)
  {
    int slen = length;
    if (slen<0) {
      slen = strlen(text);
    }
    this->begin_cmd(N2TTS::CMD_SETTEXT);
    WireI2C.write(N2TTS::TEXTTYPE_PLAIN);
    SerialUSB.print("speak text is: ");
    for (int i=0;i<slen && *text!='\0';i++) {
      SerialUSB.print(*text);
      WireI2C.write(*text);
      ++text;
    }
    if (*text!='\0') {
      WireI2C.write('\0');
    }
    SerialUSB.println("");
    this->end_cmd();
    delay(slen * 20);
    int len = this->GetParam(N2TTS::CMD_GETLENGTH);
    this->begin_cmd(N2TTS::CMD_START)->end_cmd();
    
    int play_time = int(len*1000/32000);
    delay(play_time);
    return len;
  }    
};

WioCellular Wio;
WioCellularClient WioClient(&Wio);
PubSubClient MqttClient;
N2TTS n2;
Ultrasonic UltrasonicRanger(US);

boolean setup_flag = false;

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

  SerialUSB.println("### TTS Initialize.");
  WireI2C.begin();

  // GROVE端子へ電源供給を行う(D38以外向け）
  Wio.PowerSupplyGrove(true);

  n2.setVolume(255);    // default volume

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
  
  long distance = UltrasonicRanger.MeasureInCentimeters();
  SerialUSB.print(distance);
  SerialUSB.println("[cm]");

  if((distance < 100) && (distance > 0))
  {
    char data[100];
    sprintf(data, "{\"cm\":%ld}", distance);
    SerialUSB.print("Publish:");
    SerialUSB.print(data);
    SerialUSB.println("");
    MqttClient.publish(OUT_TOPIC, data);
  }
  
  // 休憩（ただし、受信できるように、delay関数は使わないようにする）
  unsigned long next = millis();
  while (millis() < next + INTERVAL)
  {
    MqttClient.loop();
  }
}


// IN_TOPICを受信した時に呼ばれるコールバック関数
void callback(char* topic, byte* payload, unsigned int length) {
  StaticJsonBuffer<4000> jsonBuffer;
  char speak[128];
   
  // 受信したトピックを表示する
  SerialUSB.print("("); 
  SerialUSB.print(topic);
  SerialUSB.print(")Subscribe:");
  for (int i = 0; i < (int)length; i++) {
    SerialUSB.print((char)payload[i]);
  }
  SerialUSB.println("");

  JsonObject& root = jsonBuffer.parseObject(payload);
  if (!root.success()) {
   SerialUSB.println("parseObject() failed");
   return;
 }

 const char* cm = root["cm"];
 sprintf(speak,"%s センチメートル",cm);
 SerialUSB.println(speak);
 n2.setVolume(255);    // default volume
 n2.Speak(speak);
}
