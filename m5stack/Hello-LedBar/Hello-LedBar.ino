/**
 ** Name: Hello-LedBar.ino
 *
 * M5StackのLED Barを操作するサンプル
 *
 */

#include <Adafruit_NeoPixel.h>
#define PIN            15
#define NUMPIXELS      10
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 10;

void setup() {
  pixels.begin();
}

void loop() {
  int color_r = random(255) ;
  int color_g = random(255) ;
  int color_b = random(255) ;
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(color_r, color_g, color_b));
    pixels.show();
    delay(delayval);
  }
  delay(100);
}
