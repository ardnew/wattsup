#ifndef Board_h
#define Board_h

#if defined(ARDUINO_NRF52840_LED_GLASSES)
#include "adafruit/nrf52/ledglasses_nrf52840.h"
#endif

class Board;

class LED {
private:
  Board      *_board;
  uint16_t    _pin;
  bool        _on;
  duration_t  _lit;
  void (Board::*_onLit)(duration_t const);
  uint16_t init(uint16_t const pin) {
    pinMode(pin, OUTPUT);
    return pin;
  }
  bool write(bool const on) {
    digitalWrite(_pin, LED_STATE(on));
    return on;
  }
public:
  LED(Board * const board, int const pin, bool const on,
      void (Board::*onLit)(duration_t const) = nullptr):
    _board(board), _pin(init(pin)), _on(write(on)), _lit(0), _onLit(onLit) {}
  ~LED() {}
  bool get(void) { return _on; }
  void set(bool const on, duration_t const now = millis()) {
    if (_on != on) {
      _on = write(on);
      if (on) {
        _lit = now;
      }
    }
  }
  void update(duration_t const now) {
    // Turn LED on for onDuty(ms) every period(ms).
    static duration_t const period = 1000UL; // 1.0 s
    static duration_t const onDuty =  100UL; // 0.1 s
    if (get()) {
      if (now - _lit >= onDuty) {
        set(false, now);
      }
    } else {
      if (now - _lit >= period) {
        set(true, now);
        // Invoke the callback every time the LED turns on.
        if (nullptr != _board && nullptr != _onLit) {
          (_board->*_onLit)(now);
        }
      }
    }
  }
};

class Board {
private:
  UART *_uart;
  I2C  *_i2c;
  LED  *_led;

  void scan(duration_t const now) {
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
    _led(new LED(this, PIN_LED, false, &Board::scan)) {
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
  void update(duration_t const now) {
    _led->update(now);
  }

};

#endif // Board_h
