#ifndef Board_h
#define Board_h

#if defined(ARDUINO_NRF52840_LED_GLASSES)
#include "adafruit/nrf52/ledglasses_nrf52840.h"
#endif

class LED {
private:
  uint16_t   _pin;
  bool       _on;
  duration_t _lit;
  uint16_t init(uint16_t const pin) {
    pinMode(pin, OUTPUT);
    return pin;
  }
  bool write(bool const on) {
    digitalWrite(_pin, LED_STATE(on));
    return on;
  }
public:
  LED(int const pin, bool const on):
    _pin(init(pin)), _on(write(on)), _lit(0) {}
  ~LED() {}
  bool get(void) { return _on; }
  void set(bool const on, duration_t const now) {
    if (_on != on) {
      _on = write(on);
      if (on) {
        _lit = now;
      }
    }
  }
  duration_t lit(duration_t const now) {
    return now - _lit;
  }
};

class Board {
private:
  UART *_uart;
  I2C  *_i2c;
  LED  *_led;

  void scan(void) {
    for (int addr = 1; addr < 128; ++addr) {
      _i2c->beginTransmission(addr);
      if (0 == _i2c->endTransmission()) {
        _uart->print("Found: 0x");
        _uart->print(addr, HEX);
        _uart->println();
      }
    }
    _uart->println();
  }

public:
  Board(void):
    _uart(new UART(UART_BUS)),
    _i2c(new I2C(I2C_BUS)),
    _led(new LED(PIN_LED, false)) {
  }

  ~Board(void) {
    if (nullptr != _i2c) {
      _i2c->end();
      delete _i2c;
    }
    if (nullptr != _uart) {
      _uart->end();
      delete _uart;
    }
    if (nullptr != _led) {
      delete _led;
    }
  }

  void update(duration_t now) {

    // Turn LED on for onDuty(ms) every period(ms).
    static duration_t const period = 1000UL; // 1.0 s
    static duration_t const onDuty =  100UL; // 0.1 s

    if (_led->get()) {
      if (_led->lit(now) >= onDuty) {
        _led->set(false, now);
      }
    } else {
      if (_led->lit(now) >= period) {
        _led->set(true, now);
        scan();
      }
    }
  }
};

#endif // Board_h
