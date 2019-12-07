/*
 * Copyright (c) 2019 Kohei "Max" MATSUSHITA
 * Released under the MIT license
 * https://opensource.org/licenses/mit-license.php
*/
#include <M5Stack.h>
#define CONSOLE Serial
#define MODEM Serial2 /* Serial2 is Modem of 3G Module */
#include <string.h>

#define TINY_GSM_MODEM_UBLOX
#include <TinyGsmClient.h>
TinyGsm modem(MODEM);
TinyGsmClient ctx(modem);

void modem_enabler(); //通信の確保
void render_rain_radar();
void print_top();
void print_bottom();
uint16_t getColor(uint8_t red, uint8_t green, uint8_t blue);

boolean send_flag = false;
boolean setup_flag = false;

void setup() {
  M5.begin();
  CONSOLE.begin(115200);
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextSize(2);
  
  print_top();
  print_bottom();
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(0, 16);
  M5.Lcd.println("## Congrats,");
  M5.Lcd.println("## Boot successfuly!");
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(218, 0);
  M5.Lcd.print(F("(prog..."));
  modem_enabler(); //通信の確保
}

void loop() {
  if (M5.BtnA.wasReleased()) { //ボタンを押したら
    send_light("[\"on\"]");
    print_top();
    print_bottom();
   // modem.gprsDisconnect();
  }else if (M5.BtnB.wasReleased()) { //ボタンを押したら
    send_light("[\"off\"]");
    print_top();
    print_bottom();
  }
  M5.update();
}

/* ------------------------------------------------------------*/

void modem_enabler() {
  M5.Lcd.setTextColor(WHITE);
  MODEM.begin(115200, SERIAL_8N1, 16, 17);

  M5.Lcd.fillRect(0, 224, 320, 16, BLACK); /* clean up */
  M5.Lcd.setCursor(0, 224);
  M5.Lcd.println(F("modem.restart()"));
  CONSOLE.println(F("modem.restart()"));
  modem.restart();
  
  M5.Lcd.fillRect(0, 224, 320, 16, BLACK); /* clean up */
  M5.Lcd.setCursor(0, 224);
  M5.Lcd.println(F("waitForNetwork()"));
  CONSOLE.println(F("waitForNetwork()"));
  while (!modem.waitForNetwork()) M5.Lcd.print(".");

  M5.Lcd.fillRect(0, 224, 320, 16, BLACK); /* clean up */
  M5.Lcd.setCursor(0, 224);
  M5.Lcd.println(F("gprsConnect(soracom.io)"));
  CONSOLE.println(F("gprsConnect(soracom.io)"));
  modem.gprsConnect("soracom.io", "sora", "sora");

  M5.Lcd.fillRect(0, 224, 320, 16, BLACK); /* clean up */
  M5.Lcd.setCursor(0, 224);
  M5.Lcd.println(F("isNetworkConnected()"));
  CONSOLE.println(F("isNetworkConnected()"));
  while (!modem.isNetworkConnected()) M5.Lcd.print(".");

  M5.Lcd.fillRect(0, 224, 320, 16, BLACK); /* clean up */
  M5.Lcd.setCursor(0, 224);
  M5.Lcd.print(F("MyIP:"));
  CONSOLE.print(F("MyIP: "));
  IPAddress ipaddr = modem.localIP();
  M5.Lcd.println(ipaddr);
  CONSOLE.println(ipaddr);
  M5.Lcd.fillRect(0, 224, 320, 16, BLACK); /* clean up */
  M5.Lcd.setCursor(0, 224);
  M5.Lcd.print(F("SETUP FINISH"));
  CONSOLE.print(F("SETUP FINISH"));
}

char _buf[32*1024] = {0}; /* store for JPG image data */

void send_light(char *command) {
  /* connect to host */
  const char *host = "beam.soracom.io";
  const int port = 8888;
  int timeout_s = 60;
  CONSOLE.print("Connecting:");
  CONSOLE.println(host);
  if (!ctx.connect(host, port, timeout_s)) {
    CONSOLE.println("fail");
    return;
  }

  /* send request */
  const char *path = "POST /smarthome/execute/commands HTTP/1.0";
  char payload[1024];
  sprintf(payload, command);
  CONSOLE.println(path);
  ctx.println(path);
  ctx.print("Host: ");
  ctx.println(host);
  char content_length_hdr[32];
  sprintf(content_length_hdr, "Content-Length: %lu", strlen(payload));
  ctx.println(content_length_hdr);
  ctx.println();
  ctx.println(payload);

  /* receive response */
  while (ctx.connected()) {
    String line = ctx.readStringUntil('\n');
    CONSOLE.println(line);
    if (line == "\r") {
      CONSOLE.println("headers received.");
      break;
    }
  }
  ctx.readBytes(_buf, sizeof(_buf)); /* body */
  ctx.stop();
}

void print_top() {
  M5.Lcd.fillRect(0, 0, 320, 16, getColor(51, 244, 204));
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print(F("IrRemocon"));
}

void print_bottom() {
  M5.Lcd.fillRect(0, 224, 320, 16, BLACK); /* clean up */
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(0, 224);
  M5.Lcd.print(F("Btn => Send Request"));
}

uint16_t getColor(uint8_t red, uint8_t green, uint8_t blue) {
  return ((red>>3)<<11) | ((green>>2)<<5) | (blue>>3);
}
