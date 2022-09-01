#ifndef LED_h
#define LED_h

#include "board.inc.h"

class Board;

class LED {
private:
  uint16_t    _pin;
  bool        _on;
  duration_t  _lit;
  uint16_t init(uint16_t const pin) {
    pinMode(pin, OUTPUT);
    return pin;
  }
  bool write(bool const on) {
    digitalWrite(_pin, LED_STATE(on));
    return on;
  }
public:
  LED(int const pin): LED(pin, false) {}
  LED(int const pin, bool const on):
    _pin(init(pin)), _on(write(on)), _lit(0) {}
  virtual ~LED(void) {}
  bool get(void) { return _on; }
  void set(bool const on, duration_t const now = millis()) {
    if (_on != on) {
      _on = write(on);
      if (on) {
        _lit = now;
      }
    }
  }
  bool update(duration_t const now) {
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
        return true; // Notify caller every time LED turns on
      }
    }
    return false;
  }
};

#endif // LED_h
