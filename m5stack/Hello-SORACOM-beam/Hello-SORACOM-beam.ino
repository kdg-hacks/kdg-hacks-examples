/**
 * M5Stack(Gray)で、SORACOM beamを使って
 * IFTTT向けのPOSTリクエストを行うサンプルです。
 * (`Hello-SoracomHarvest.ino` と本ソースはほぼ同様です。)
 *
 * 下記コマンドをbeam経由で行います。
 * curl -X POST -H "Content-Type: application/json" -d '{"value1":"uptime:
 * xx"}'
 * https://maker.ifttt.com/trigger/m5gray_uptime/with/key/{YOUR_MAKER_KEY}
 *
 * * --- 事前準備 --- *
 * 下記記事などを参考にIFTTTの設定を入れます。
 * [IFTTTで簡単IoT！M5StackとLINEを連携する方法](http://kyokucho1989.chillout.jp/2019/11/09/ifttt%E3%81%A7%E7%B0%A1%E5%8D%98iot%EF%BC%81m5stack%E3%81%A8line%E3%82%92%E9%80%A3%E6%90%BA%E3%81%99%E3%82%8B%E6%96%B9%E6%B3%95/)
 *
 * LINEに投稿する場合のactionの例は、同ディレクトリの「IFTTT_LINEの例.png」参照
 */

#include <M5Stack.h>

#define TINY_GSM_MODEM_UBLOX
#include <TinyGsmClient.h>

TinyGsm modem(Serial2); /* Serial2 is Modem of 3G Module */
TinyGsmClient ctx(modem);

#define WEBURL "http://beam.soracom.io:8888/"
#define INTERVAL (10000)  // 10 seconds

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
  M5.Lcd.println(F("Uptime post to SORACOM BEAM"));

  /* HTTP GET example */
  if (!ctx.connect("uni.soracom.io", 80)) {
    Serial.println(F("Connect failed."));
    return;
  }
  Serial.println(F("connected."));

  /* build payload */
  char payload[1024];
  sprintf(payload, "{\"value1\":\"uptime %lu\"}", millis() / 1000);

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

  Serial.println("### Wait.");
  delay(INTERVAL);
}
