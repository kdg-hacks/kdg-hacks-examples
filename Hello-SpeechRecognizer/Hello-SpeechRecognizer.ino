// Wio LTE/M1 UART端子に発話認識モジュールをつないだ場合のサンプルプログラム

#include <WioCellLibforArduino.h>

HardwareSerial* SpeechSerial;

WioCellular Wio;

const char *voiceBuffer[] = {
    "Turn on the light",
    "Turn off the light",
    "Play music",
    "Pause",
    "Next",
    "Previous",
    "Up",
    "Down",
    "Turn on the TV",
    "Turn off the TV",
    "Increase temperature",
    "Decrease temperature",
    "What's the time",
    "Open the door",
    "Close the door",
    "Left",
    "Right",
    "Stop",
    "Start",
    "Mode 1",
    "Mode 2",
    "Go",
};

void SerialBegin(HardwareSerial* serial) {
  SpeechSerial = serial;
  SpeechSerial->begin(9600);
}

void setup() {
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---");

  SerialUSB.println("### I/O Initialize.");
  SerialBegin(&SerialUART);
  Wio.Init();

  SerialUSB.println("### Power supply ON.");
  Wio.PowerSupplyGrove(true);
  delay(500);

  SerialUSB.println("### Setup completed.");
}

void loop() {
  if(SpeechSerial->available()) {
    char cmd;
    cmd = SpeechSerial->read();
    SerialUSB.println(voiceBuffer[cmd - 1]);
  }
}
