/**
 * N2日本語音声合成Box制御サンプルコード(シンプル版）
 * Author: Crowd Machines Projecct / KDDI Research, Inc.
 * created by 2018/11/13
 */
#include <WioCellLibforArduino.h>

#define INTERVAL                100

/**
 * N2TTS: 日本語音声合成Box制御用ラッパクラス
 */
class N2TTS
{
  static const uint8_t I2C_ADDRESS = 0x4e;

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

void setup() {
  delay(200);
  
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---------------------------------------------------");

  SerialUSB.println("### I/O Initialize.");
  Wio.Init();
  
  SerialUSB.println("### Power supply ON.");
  Wio.PowerSupplyGrove(true);
  delay(500);

  SerialUSB.println("### TTS Initialize.");
  WireI2C.begin();

  SerialUSB.println("### Setup completed.");
  N2TTS n2;
  int v = n2.getVolume();
  SerialUSB.print("default volume is ");
  SerialUSB.println(v);
  v = n2.getSpeechRate();
  SerialUSB.print("default speech rate is ");
  SerialUSB.println(v);
  v = n2.getPitch();
  SerialUSB.print("default pitch rate is ");
  SerialUSB.println(v);
  
  n2.setVolume(256);    // default volume
  n2.Speak("こんにちは、起動しましたよ。");

  SerialUSB.println("### SetVolume begin.");
  n2.setVolume(128);    // 半分の音量にする
  SerialUSB.println("### SetVolume completed.");
  n2.Speak("さようならぁ。");
  v = n2.getVolume();
  SerialUSB.print("volume is ");
  SerialUSB.println(v);

  n2.setPitch(50);
  n2.Speak("またね〜");
}

void loop() {
  delay(INTERVAL);
}
