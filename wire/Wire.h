#include "Arduino.h"

#define PINNAME_TO_PIN(port, pin) ((port - 'A') * 16 + pin)
#define WIO_I2C_D24            PINNAME_TO_PIN('B', 8)
#define WIO_I2C_D25            PINNAME_TO_PIN('B', 9)
#define GROVE_I2C_CORE        (0)   // I2C1
#define GROVE_I2C_SCL_PIN    WIO_I2C_D25                // out
#define GROVE_I2C_SDA_PIN    WIO_I2C_D24                // in/out

extern TwoWire Wire;
