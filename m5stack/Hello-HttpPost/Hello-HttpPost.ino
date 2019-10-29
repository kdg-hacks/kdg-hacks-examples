/**
 * Name: Hello_HttpPost.ino
 *
 * M5StackでHTTP POSTリクエストを実行するサンプル
 */

#include <M5Stack.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial

const char* ssid     = "ssid";
const char* password = "password";
WiFiMulti wifiMulti;

void setup() {
    USE_SERIAL.begin(115200);
    USE_SERIAL.println();

    // init lcd, serial, but don't init sd card
    M5.begin(true, false, true);
    M5.Lcd.clear(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(1);
    M5.Lcd.println("HTTP POST EXAMPLE");

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    wifiMulti.addAP(ssid, password);
}

void loop() {
    M5.Lcd.clear(BLACK);
    M5.Lcd.setCursor(0, 0);

    // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {
        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        http.begin("http://example.com/"); //HTTP

        USE_SERIAL.print("[HTTP] POST...\n");
        // start connection and send HTTP header
        int httpCode = http.POST("{\"key\":\"value\"}");

        M5.Lcd.print("HTTP POST Status Code:");
        M5.Lcd.println(httpCode);
        M5.Lcd.println();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] POST... code: %d\n", httpCode);

            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(10000);
}