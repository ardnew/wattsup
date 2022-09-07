#ifndef Board_h
#define Board_h

#include "LED.h"
#include "UART.h"
#include "I2C.h"

class Board {
private:
  UART *_uart;
  I2C  *_i2c;
  LED  *_led;
  void scan(duration_t const now) {
    for (int addr = 1; addr < 128; ++addr) {
      _i2c->initTransfer(addr);
      if (0 == _i2c->endTransfer()) {
        _uart->print("Found: 0x");
        _uart->print(addr, HEX);
        _uart->println();
      }
    }
    _uart->println();
  }
public:
  Board(void):
    _uart(new UART()),
    _i2c(new I2C()),
    _led(new LED()) {
  }
  virtual ~Board(void) {
    if (nullptr != _led)  { delete _led; }
    if (nullptr != _i2c)  { delete _i2c; }
    if (nullptr != _uart) { delete _uart; }
  }
  UART *uart(void) { return _uart; }
  I2C  *i2c(void)  { return _i2c; }
  LED  *led(void)  { return _led; }
  void update(duration_t const now) {
    if (_led->update(now)) {
      //scan(now);
    }
  }
};

#endif // Board_h
