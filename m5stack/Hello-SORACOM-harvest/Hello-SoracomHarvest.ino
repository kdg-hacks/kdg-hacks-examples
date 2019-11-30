/**
 * 1秒ごとにカウントアップしたデータをSoracom
 * Harvestに送信し、送受信内容をシリアルモニタにプリントします
 *
 * Soracom管理画面、「Sim 管理」 -> Sim選択 ->「SORACOM Harvest 設定」より設定後
 * Soracom管理画面、「Sim 管理」 -> Sim選択 -> 「操作」->
 * 「データを確認」より送信データを確認することができます
 *
 * [参考URL] https://dev.soracom.io/jp/start/m5stack/
 * 上記の記事のサンプルコードのuploadするデータのpayload部分のみ変更してます。
 *
 * [注]
 * M5Stack用3G拡張ボードを外して書き込み(Upload)しないとエラーが出る可能性があります。
 */

#include <M5Stack.h>

#define TINY_GSM_MODEM_UBLOX
#include <TinyGsmClient.h>

TinyGsm modem(Serial2); /* Serial2 is Modem of 3G Module */
TinyGsmClient ctx(modem);

int counter = 0;

void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.println(F("M5Stack + 3G Module"));

  M5.Lcd.print(F("modem.restart()"));
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  modem.restart();
  M5.Lcd.println(F("done"));

  M5.Lcd.print(F("getModemInfo:"));
  String modemInfo = modem.getModemInfo();
  M5.Lcd.println(modemInfo);

  M5.Lcd.print(F("waitForNetwork()"));
  while (!modem.waitForNetwork()) M5.Lcd.print(".");
  M5.Lcd.println(F("Ok"));

  M5.Lcd.print(F("gprsConnect(soracom.io)"));
  modem.gprsConnect("soracom.io", "sora", "sora");
  M5.Lcd.println(F("done"));

  M5.Lcd.print(F("isNetworkConnected()"));
  while (!modem.isNetworkConnected()) M5.Lcd.print(".");
  M5.Lcd.println(F("Ok"));

  M5.Lcd.print(F("My IP addr: "));
  IPAddress ipaddr = modem.localIP();
  M5.Lcd.print(ipaddr);
  delay(2000);
}

void loop() {
  M5.update();

  M5.Lcd.clear(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println(F("Uptime post to SORACOM Harvest"));

  /* HTTP GET example */
  if (!ctx.connect("uni.soracom.io", 80)) {
    Serial.println(F("Connect failed."));
    return;
  }
  Serial.println(F("connected."));

  /* build payload */
  char payload[1024];
  // sprintf(payload, "{\"uptime\":%lu}", millis() / 1000);
  sprintf(payload, "{\"counter\":%lu}", counter);
  counter++;

  /* send request */
  ctx.println("POST / HTTP/1.1");
  ctx.println("Host: uni.soracom.io");
  ctx.println("Content-Type: application/json");
  char content_length_hdr[32];
  sprintf(content_length_hdr, "Content-Length: %lu", strlen(payload));
  ctx.println(content_length_hdr);
  ctx.println();
  ctx.println(payload);
  Serial.println("sent data below;");
  Serial.println(payload);

  /* receive response */
  while (ctx.connected()) {
    String line = ctx.readStringUntil('\n');
    Serial.println(line);
    if (line == "\r") {
      Serial.println("headers received.");
      break;
    }
  }
  char buf[1 * 1024] = {0};
  ctx.readBytes(buf, sizeof(buf)); /* body */
  ctx.stop();
  M5.Lcd.println(buf);

  Serial.println("received data below;");
  Serial.println(buf);

  delay(1000 * 1);  // 1秒スリープ
}