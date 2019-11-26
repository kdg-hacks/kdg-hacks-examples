// M5STACKにIR REMOTE UNITを接続し、赤外線を学習（ソースコード化）する。
// リモコン信号を再現するサンプルアプリ

// 必要なライブラリ IRremoteESP8266 Version 2.7.1を利用
// https://github.com/crankyoldgit/IRremoteESP8266

#include <M5Stack.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRac.h>
#include <IRutils.h>

// IR REMOTE をPORT-Aに接続した場合
// #define IR_RECV_PIN  22
// #define IR_SEND_PIN  21

// IR REMOTE をPORT-Bに接続した場合
// #define IR_RECV_PIN  36
// #define IR_SEND_PIN  26

// IR REMOTE をPORT-Cに接続した場合
// #define IR_RECV_PIN  16
// #define IR_SEND_PIN  17

IRrecv irrecv(IR_RECV_PIN, 1024, 50, true);
decode_results results;
IRsend irsend(IR_SEND_PIN);

#define IR_MAX_SEND_DATA 300
uint16_t send_data[IR_MAX_SEND_DATA];
uint16_t send_len = 0;

unsigned long recvStartTime;
unsigned long recvDuration = 0;

void setup() {
  M5.begin();
  irsend.begin();
}

void loop() {
  M5.update();

  if ( M5.BtnA.wasReleased() ) {
    // 学習させたデータをそのまま送信する
    Serial.println("BtnA.released");
    if( send_len > 0 )
      irsend.sendRaw((uint16_t*)send_data, send_len, 38);
  }

  if ( M5.BtnB.wasReleased() ) {
    // ここでは、DMM.make 65型の電源ボタンを学習させて、Logに出力したソースコードをそのまま転記した例
    Serial.println("BtnB.released");
    uint16_t rawData[249] = {4526, 4392,  726, 1594,  628, 1588,  656, 1616,  628, 532,  602, 532,  602, 532,  602, 534,  602, 534,  600, 1644,  600, 1642,  602, 1640,  602, 534,  602, 534,  600, 532,  602, 532,  602, 534,  600, 532,  602, 1636,  608, 510,  624, 506,  628, 508,  626, 506,  626, 532,  602, 532,  602, 1640,  602, 532,  604, 1612,  630, 1640,  602, 1616,  626, 1640,  602, 1614,  628, 1590,  652, 5050,  750, 1302,  278, 4518,  2042, 6794,  3840, 3130,  1062, 1730,  1970, 4230,  940, 3098,  1530, 4506,  4630, 4314,  780, 1616,  628, 1616,  628, 1618,  624, 506,  628, 532,  602, 506,  628, 532,  602, 534,  600, 1618,  626, 1616,  626, 1616,  628, 532,  602, 506,  628, 532,  600, 508,  628, 532,  600, 532,  602, 1642,  602, 534,  600, 536,  598, 560,  576, 534,  600, 534,  600, 534,  600, 1642,  600, 534,  600, 1642,  600, 1640,  602, 1642,  600, 1642,  600, 1644,  598, 1644,  600, 9914,  530, 2340,  1490, 1762,  850, 7866,  492, 2832,  478, 6856,  1252, 438,  1608, 3906,  1186, 2726,  4900, 4378,  716, 1620,  600, 1642,  600, 1640,  602, 532,  600, 536,  598, 536,  600, 534,  600, 534,  600, 1640,  602, 1642,  602, 1642,  602, 534,  598, 534,  600, 534,  600, 532,  602, 532,  602, 510,  624, 1642,  600, 534,  600, 532,  602, 534,  602, 508,  626, 508,  626, 508,  626, 1616,  626, 532,  602, 1640,  602, 1618,  626, 1618,  626, 1618,  624, 1620,  624, 1642,  602, 10368,  1180, 6876,  572, 2734,  862, 1220,  570, 2122,  1030, 3504,  994, 1652,  2558};  // UNKNOWN A22929EF
    irsend.sendRaw((uint16_t*)rawData, sizeof(rawData), 38);
  }

  if ( M5.BtnC.wasReleased() ) {
    // リモコン信号を学習するモードに移行させる
    Serial.println("BtnC.released");
    ir_start(10000);
  }

  if (irrecv.decode(&results)) {
    irrecv.resume();

    if( results.rawlen <= IR_MAX_SEND_DATA ){
      ir_stop();

      uint16_t * result = resultToRawArray(&results);
      
      send_len = getCorrectedRawLength(&results);

      for( int i = 0 ; i < send_len ; i++ )
        send_data[i] = result[i];
      
      delete[] result;

      Serial.println("IR received");
    }else{
      Serial.println("IR size over");
    }

    Serial.print(resultToHumanReadableBasic(&results));
    
    String description = IRAcUtils::resultAcToString(&results);
    
    if (description.length())
      Serial.println("Mesg Desc.: " + description);

    Serial.println(resultToSourceCode(&results));

    delay(100);
  }

  if( recvDuration > 0 ){
    unsigned long elapsed = millis() - recvStartTime;
    if( elapsed >= recvDuration ){
      Serial.println("Expired");
      ir_stop();
    }
  }
}

// 学習開始
void ir_start(unsigned long duration){
  if( duration == 0 ){
    ir_stop();
  }else{
    if( recvDuration == 0 ){
      irrecv.enableIRIn();
    }

    send_len = 0;
    recvStartTime = millis();
    recvDuration = duration;

    Serial.println("IR scan start");
  }
}

// 学習終了
void ir_stop(void){
  if( recvDuration > 0 ){
    pinMode(IR_RECV_PIN, OUTPUT);
    recvDuration = 0;

    Serial.println("IR scan stopped");
  }
}
