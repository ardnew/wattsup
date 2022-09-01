#ifndef I2C_h
#define I2C_h

#include "board.inc.h"

class I2C: public i2c {
public:
  I2C(void) {}
  virtual ~I2C(void) {}
  void initTransfer(uint8_t addr) {
    i2c::initTransfer(addr);
  }
  uint8_t endTransfer(void) {
    return i2c::endTransfer();
  }
  uint8_t endTransfer(bool stop) {
    return i2c::endTransfer(stop);
  }
};

#endif // I2C_h
