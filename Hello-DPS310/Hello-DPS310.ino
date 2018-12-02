#include <WioCellLibforArduino.h>
#include "Dps310.h"

#define RECEIVE_TIMEOUT (10000)

WioCellular Wio;

// Dps310 Opject
Dps310 Dps310PressureSensor = Dps310();

void setup()
{
  delay(200);
  // デバッグ用シリアル初期化
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---");

  // Wi LTEoの初期化
  SerialUSB.println("### I/O Initialize.");
  Wio.Init();

  SerialUSB.println("--- Power supply ON. ---");
  Wio.PowerSupplyCellular(true);
  delay(500);

  SerialUSB.println("--- Turn on or reset. ---");
  if (!Wio.TurnOnOrReset()) {
    SerialUSB.println("### ERROR! ###");
    return;
  }

  SerialUSB.println("--- Connecting to \"soracom.io\". ---");
#ifdef ARDUINO_WIO_LTE_M1NB1_BG96
  Wio.SetSelectNetwork(WioCellular::SELECT_NETWORK_MODE_MANUAL_IMSI);
#endif
  if (!Wio.Activate("soracom.io", "sora", "sora")) {
    SerialUSB.println("### ERROR! ###");
    return;
  }

  SerialUSB.println("### Grove supply ON.");
  Wio.PowerSupplyGrove(true);
  
  //Call begin to initialize Dps310PressureSensor
  //The parameter 0x76 is the bus address. The default address is 0x77 and does not need to be given.
  //Dps310PressureSensor.begin(Wire, 0x76);
  //Use the commented line below instead to use the default I2C address.
  Dps310PressureSensor.begin(WireI2C);

  SerialUSB.println("### Dps310PressureSensor begin.");

  //temperature measure rate (value from 0 to 7)
  //2^temp_mr temperature measurement results per second
  int16_t temp_mr = 2;
  //temperature oversampling rate (value from 0 to 7)
  //2^temp_osr internal temperature measurements per result
  //A higher value increases precision
  int16_t temp_osr = 2;
  //pressure measure rate (value from 0 to 7)
  //2^prs_mr pressure measurement results per second
  int16_t prs_mr = 2;
  //pressure oversampling rate (value from 0 to 7)
  //2^prs_osr internal pressure measurements per result
  //A higher value increases precision
  int16_t prs_osr = 2;
  //startMeasureBothCont enables background mode
  //temperature and pressure ar measured automatically
  //High precision and hgh measure rates at the same time are not available.
  //Consult Datasheet (or trial and error) for more information
  int16_t ret = Dps310PressureSensor.startMeasureBothCont(temp_mr, temp_osr, prs_mr, prs_osr);
  //Use one of the commented lines below instead to measure only temperature or pressure
  //int16_t ret = Dps310PressureSensor.startMeasureTempCont(temp_mr, temp_osr);
  //int16_t ret = Dps310PressureSensor.startMeasurePressureCont(prs_mr, prs_osr);


  if (ret != 0)
  {
    SerialUSB.print("Init FAILED! ret = ");
    SerialUSB.println(ret);
  }
  else
  {
    SerialUSB.println("Init complete!");
  }
}



void loop()
{
  uint8_t pressureCount = 20;
  float pressure[pressureCount];
  uint8_t temperatureCount = 20;
  float temperature[temperatureCount];
  char data[100];

  //This function writes the results of continuous measurements to the arrays given as parameters
  //The parameters temperatureCount and pressureCount should hold the sizes of the arrays temperature and pressure when the function is called
  //After the end of the function, temperatureCount and pressureCount hold the numbers of values written to the arrays
  //Note: The Dps310 cannot save more than 32 results. When its result buffer is full, it won't save any new measurement results
  int16_t ret = Dps310PressureSensor.getContResults(temperature, temperatureCount, pressure, pressureCount);

  if (ret != 0)
  {
    SerialUSB.println();
    SerialUSB.println();
    SerialUSB.print("FAIL! ret = ");
    SerialUSB.println(ret);
  }
  else
  {
    SerialUSB.println();
    SerialUSB.println();
    SerialUSB.print(temperatureCount);
    SerialUSB.println(" temperature values found: ");
    for (int16_t i = 0; i < temperatureCount; i++)
    {
      SerialUSB.print(temperature[i]);
      SerialUSB.println(" degrees of Celsius");
    }

    SerialUSB.println();
    SerialUSB.print(pressureCount);
    SerialUSB.println(" pressure values found: ");
    for (int16_t i = 0; i < pressureCount; i++)
    {
      SerialUSB.print(pressure[i]);
      SerialUSB.println(" Pascal");
    }
  }



  SerialUSB.println("--- Open socket. ---");

  // Open harvest connection
  int connectId;
  connectId = Wio.SocketOpen("harvest.soracom.io", 8514, WIO_UDP);
  if (connectId < 0) {
    SerialUSB.println("### ERROR! ###");
    goto err;
  }

  // Send data.
  SerialUSB.println("--- Send data. ---");
  SerialUSB.print("Send:");

  // create payload
  sprintf(data,"{\"temperature\": %f, \"pressure\": %f, \"graph_pressure\": %f}", temperature[0], pressure[0], pressure[0] - 102800);
  SerialUSB.println(data);
  if (!Wio.SocketSend(connectId, data)) {
    SerialUSB.println("### ERROR! ###");
    goto err_close;
  }

  // Receive data.
  SerialUSB.println("-- Receive data. ---");
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
  }
err:
  //Wait some time, so that the Dps310 can refill its buffer
  delay(10000);
}
