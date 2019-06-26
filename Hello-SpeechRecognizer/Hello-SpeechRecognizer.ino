// Board ver 1.2.0 / Library 1.7.0 OK 
// Wio LTE/M1 UART端子に発話認識モジュールをつないだ場合のサンプルプログラム

#include <WioCellLibforArduino.h>

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

void setup() {
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---");

  SerialUSB.println("### I/O Initialize.");
  
  Wio.Init();

  // GROVE端子へ電源供給を行う(D38以外向け）
  Wio.PowerSupplyGrove(true);
  
  delay(500);
  
  SerialUART.begin(9600);
  
  while (SerialUART.available()) 
  {
    SerialUART.read(); 
  }

  SerialUSB.println("### Setup completed.");
}

void loop() {
  if(SerialUART.available()) {
    char cmd;
    cmd = SerialUART.read();
    if((cmd > 0) && (cmd <= 22)) {
      SerialUSB.println(voiceBuffer[cmd - 1]);
    }
  }
}
