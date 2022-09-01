#ifndef ina260_i2c_h
#define ina260_i2c_h

#include <Adafruit_INA260.h>

#include "../../board/Board.h"

#define POWER_ADDRESS (0x40)

class power: protected Adafruit_INA260 {
public:
  power(Board &board) {
    begin(POWER_ADDRESS, board.i2c());
  }
  virtual ~power(void) {}
};

#endif // ina260_i2c_h
