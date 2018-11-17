// Wio LTE/M1 UART端子にGPS v1.2を繋いだ場合のサンプルプログラム

#include <WioCellLibforArduino.h>

#define GPS_OVERFLOW_STRING "OVERFLOW"

HardwareSerial* GpsSerial;

WioCellular Wio;

void setup() {
  // デバッグ用シリアル初期化
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---");

  GpsBegin(&SerialUART);

  // Wi LTEoの初期化
  Wio.Init();

  // GROVE端子へ電源供給を行う(D38以外向け）
  Wio.PowerSupplyGrove(true);
}

void loop() {
  const char* data = GpsRead();
  if (data != NULL && strncmp(data, "$GPGGA,", 7) == 0) {
    SerialUSB.println(data);
  }
}

char GpsData[100];
int GpsDataLength;

void GpsBegin(HardwareSerial* serial) {
  GpsSerial = serial;
  GpsSerial->begin(9600);
  GpsDataLength = 0;
}

const char* GpsRead() {
  while (GpsSerial->available()) {
    char data = GpsSerial->read();
    if (data == '\r') continue;
    if (data == '\n') {
      GpsData[GpsDataLength] = '\0';
      GpsDataLength = 0;
      return GpsData;
    }
    
    if (GpsDataLength > (int)sizeof(GpsData) - 1) { // Overflow
      GpsDataLength = 0;
      return GPS_OVERFLOW_STRING;
    }
    GpsData[GpsDataLength++] = data;
  }

  return NULL;
}
