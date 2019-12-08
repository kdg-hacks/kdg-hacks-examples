// M5CAMERAで、特定のＷｅｂサーバに写真をアップロードするプログラム

// ボードはESP32 Wrover Moduleを選択してください。

/*
 * 受信側のPHPのサーバの例
<?php

    //一字ファイルができているか（アップロードされているか）チェック
    if(is_uploaded_file($_FILES['up_file']['tmp_name'])){

        //一字ファイルを保存ファイルにコピーできたか
        if(move_uploaded_file($_FILES['up_file']['tmp_name'],"./".$_FILES['up_file']['name'])){
            error_log(date("Y/m/d H:i:s") . "," . $_FILES['up_file']['name'] . "," . $_FILES['up_file']['size'] . "\n",3,"./up.log");
            echo "uploaded";

        }else{
            echo "error while saving.";
        }

    }else{

        //そもそもファイルが来ていない。
        echo "file not uploaded.";

    }
?> 
 */

#include "esp_camera.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>

#define CAMERA_MODEL_M5STACK_PSRAM
#include "camera_pins.h"

// 接続する無線LANの情報
// const char* ssid = "KDG-GUEST";
const char* ssid = "IoT24";
const char* password = "opentheGATE0905";

// グローバル変数の定義
uint8_t mac_addr[6] = {0};
char mac_addr_s[20]="0000000000000000";

WiFiClient client1;

#define WEB_HOST "192.168.0.106"
#define WEB_PORT 8000
#define WEB_PATH "up.php"

void setup() {
  Serial.begin(115200);
  Serial.println();

  // LEDの設定
  pinMode(M5LED1, OUTPUT);
  digitalWrite(M5LED1, HIGH);

  camera_config_t config;
  
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  
  config.frame_size = FRAMESIZE_VGA;
  config.jpeg_quality = 15;
  config.fb_count = 4;

  // カメラの初期化
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  // カメラのパラメータの設定
  sensor_t * s = esp_camera_sensor_get();
  s->set_framesize(s, FRAMESIZE_VGA);

  WiFi.begin(ssid, password);

  char buf[20];
  WiFi.macAddress(mac_addr);
  sprintf(mac_addr_s, "%02x%02x%02x%02x%02x%02x", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.printf("WiFi MAC ADDR=%s",mac_addr_s);
  Serial.println("");

  // WiFi接続
  int count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    count++;
    digitalWrite(M5LED1, LOW);
    delay(250);
    digitalWrite(M5LED1, HIGH);
    delay(250);
    Serial.print(".");

    if(count > 50)
    {
      Serial.println("");
      Serial.println("WIFi AP Not connect");
      count = 0;
      esp_restart();
      return;
    }
  }
  
  Serial.println("");
  Serial.println("WiFi connected");

  digitalWrite(M5LED1, LOW);

  capture();

  digitalWrite(M5LED1, HIGH);
}

void loop() {
}

// 静止画を一枚取得
void capture(){
    camera_fb_t * fb = NULL;
    esp_err_t res = ESP_OK;
    int64_t fr_start = esp_timer_get_time();

    fb = esp_camera_fb_get();
    
    if (!fb) {
        Serial.println("Camera capture failed");
        return;
    }

    Serial.println("Get Photo");

    size_t fb_len = 0;

    if(fb->format == PIXFORMAT_JPEG){
      post_image(fb->buf, fb->len);
    }
    else
    {
      Serial.println("NO PIX FORMAT JPG");
    }
    
    esp_camera_fb_return(fb);
    
    int64_t fr_end = esp_timer_get_time();
    Serial.printf("JPG: %u ms\n", (uint32_t)((fr_end - fr_start)/1000));
    return;
}

void post_image(uint8_t *buf, int len)
{
  Serial.printf("length=%d",len);
  Serial.println("");
  
  //boundary 作成
  char boundary[32]= "--";
  char contentType[100]= {0};
  
  randomSeed(micros());
  
  for (int i = 0; i < 3; i++) {
    ltoa(random(0x7FFFFFF), boundary + strlen(boundary), 16);
  }

  
  strcpy(contentType, "multipart/form-data; boundary=");
  strcat(contentType, boundary);

  String payloadHeaderFormat = ""
                     "--%s\r\n"
                     "Content-Disposition: form-data; name=\"up_file\"; filename=\"%s\"\r\n"
                     "Content-Type: application/octet-stream\r\n"
                     "Content-Transfer-Encoding: binary\r\n"
                     "\r\n"
                     ;
                     
  //body 部分上部 boundary と下部 boundary データを作成
  
  char payloadHeader[200] = {0};
  sprintf(payloadHeader,payloadHeaderFormat.c_str(),boundary,mac_addr_s);

  char payloadFooter[50] = {0};
  sprintf(payloadFooter, "\r\n--%s--\r\n", boundary);

  String bodyHeader = String(payloadHeader);
  String bodyFooter = String(payloadFooter);

  int contentLength = bodyHeader.length() + len + bodyFooter.length();
    
  if (client1.connect(WEB_HOST,WEB_PORT))
  {    
    client1.printf("POST %s HTTP/1.1\n",WEB_PATH);
    client1.print(F("Host: "));
    client1.println(WEB_HOST);
    
    client1.println(F("Connection: close"));
    
    client1.print(F("Content-Type: "));
    client1.println(contentType);

    client1.print(F("Content-Length: "));
    client1.println(contentLength);   
         
    client1.println();

    client1.print(bodyHeader.c_str());
    client1.flush();

    // Serial.println(bodyHeader.c_str());
    
    int sends = 0;
    int nRet = 0;

    while(sends < len)
    {
      int len2 = len - sends;

      if(len2 > 5120)
      {
        len2 = 5120;
      }
            
      nRet = client1.write(&buf[sends],len2);
      
      if(nRet == 0)
      {
        Serial.println("nRet = 0");
        delay(5000);
        esp_restart();
        return;
      }
      client1.flush();
      
      sends = sends + nRet;

      Serial.printf("nRet=%d/%d %d",nRet,len2,sends);
      Serial.println("");
    }

    client1.print(bodyFooter.c_str());
    client1.flush();

    // Serial.println(bodyFooter.c_str());

    String response = "";  

    int timeout = millis() + (30 * 1000);
    bool isTimeout = false;
    
    while (client1.available() == 0) {
        if ((int)(timeout - millis()) < 0) {
            Serial.println(">>> Client Timeout (30sec)!");
            isTimeout = true;
            break;
        }
        delay(100);
    }

   if(isTimeout == false){
        Serial.println(F("--- response "));
        String line = "";
        while(client1.available()){
            line = client1.readStringUntil('\r');
            Serial.print(line);
            response += line;
        }
        Serial.println(F(""));
        Serial.println(F("response --- "));
    }

    client1.stop();        
  }
  else
  {
    Serial.println("Error Connect");
  }
}
