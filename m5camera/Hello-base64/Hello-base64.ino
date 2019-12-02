// M5CAMERA 文字列(Base64)で、写真を取得するプログラム
// ボードをESP32 Wrover Moduleを選択してください。

#define CAMERA_MODEL_M5STACK_PSRAM

#include "camera_pins.h"
#include "esp_camera.h"
#include "base64.hpp"

unsigned char encoded[64000];

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
  
  // config.frame_size = FRAMESIZE_UXGA;
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
  // s->set_framesize(s, FRAMESIZE_UXGA);
  s->set_framesize(s, FRAMESIZE_VGA);

}

void loop() {
  digitalWrite(M5LED1, LOW);

  capture();

  digitalWrite(M5LED1, HIGH);

  delay(1000);
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
    
    size_t fb_len = 0;

    if(fb->format == PIXFORMAT_JPEG){
      Serial.print(fb->len);
      Serial.println("");

      // ここで、BASE64化を行っています。
      memset(encoded,0,sizeof(encoded));
      Serial.print("data:image/jpeg;base64,");
      encode_base64(fb->buf, fb->len, encoded);
      Serial.println((char *)encoded);
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
