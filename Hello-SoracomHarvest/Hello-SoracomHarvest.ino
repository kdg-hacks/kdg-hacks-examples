// Wio cell lib for Arduino の soracom/soracom-harvest スケッチ例をSoracom Harvestへのデータ送受信に絞ったコードです
// 1秒ごとにカウントアップしたデータをSoracom Harvestに送信し、送受信内容をシリアルモニタにプリントします
// Soracom管理画面、 「Sim 管理」 -> Sim選択 ->「SORACOM Harvest 設定」より設定後
// Soracom管理画面、 「Sim 管理」 -> Sim選択 -> 「操作」-> 「データを確認」より送信データを確認することができます
#include <WioCellLibforArduino.h>

#define INTERVAL        (1000)
#define RECEIVE_TIMEOUT (10000)

WioCellular Wio;
int counter;

void setup() {
  delay(200);

  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---------------------------------------------------");
  
  SerialUSB.println("### Counter Initialize.");
  counter = 0;

  SerialUSB.println("### I/O Initialize.");
  Wio.Init();

  SerialUSB.println("### Power supply ON.");
  Wio.PowerSupplyCellular(true);
  delay(500);

  SerialUSB.println("### Turn on or reset.");
  if (!Wio.TurnOnOrReset()) {
    SerialUSB.println("### ERROR! ###");
    return;
  }

  SerialUSB.println("### Connecting to \"soracom.io\".");
#ifdef ARDUINO_WIO_LTE_M1NB1_BG96
  Wio.SetSelectNetwork(WioCellular::SELECT_NETWORK_MODE_MANUAL_IMSI);
#endif
  if (!Wio.Activate("soracom.io", "sora", "sora")) {
    SerialUSB.println("### ERROR! ###");
    return;
  }

  SerialUSB.println("### Setup completed.");
}

void loop() {
  char data[100];

  // create payload
  sprintf(data,"{\"count\": %d}", counter);

  SerialUSB.println("### Open.");

  // Open harvest connection
  int connectId;
  connectId = Wio.SocketOpen("harvest.soracom.io", 8514, WIO_UDP);
  if (connectId < 0) {
    SerialUSB.println("### ERROR! ###");
    goto err;
  }

  // Send data.
  SerialUSB.println("### Send.");
  SerialUSB.print("Send:");
  SerialUSB.println(data);
  if (!Wio.SocketSend(connectId, data)) {
    SerialUSB.println("### ERROR! ###");
    goto err_close;
  }

  // Receive data.
  SerialUSB.println("### Receive.");
  int length;
  length = Wio.SocketReceive(connectId, data, sizeof (data), RECEIVE_TIMEOUT);
  if (length < 0) {
    SerialUSB.println("### ERROR! ###");
    goto err_close;
  }

  if (length == 0) {
    SerialUSB.println("### RECEIVE TIMEOUT! ###");
    goto err_close;
  }

  SerialUSB.print("Receive:");
  SerialUSB.print(data);
  SerialUSB.println("");

err_close:
  SerialUSB.println("### Close.");
  if (!Wio.SocketClose(connectId)) {
    SerialUSB.println("### ERROR! ###");
    goto err;
  }

err:
  delay(INTERVAL);
  counter++;
}
