/**
 * Name: Hello_HttpGet.ino
 * 
 * M5StackでHTTP GETリクエストを実行するサンプル
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
    // init lcd, serial, but don't init sd card
    M5.begin(true, false, true);
    M5.Lcd.clear(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(1);
    M5.Lcd.println("HTTP GET EXAMPLE");

    USE_SERIAL.begin(115200);
    USE_SERIAL.println();

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
        http.begin("http://example.com/index.html"); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        M5.Lcd.print("HTTP GET Status Code:");
        M5.Lcd.println(httpCode);
        M5.Lcd.println();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);

                M5.Lcd.println("payload:");
                M5.Lcd.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
   
    delay(10000);
}
