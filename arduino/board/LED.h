#ifndef LED_h
#define LED_h

#include "board.inc.h"

class Board;

class LED: public led {
private:
  duration_t _lit;
public:
  LED(void):
    _lit(0) {}
  virtual ~LED(void) {}
  bool update(duration_t const now) {
    // Turn LED on for onDuty(ms) every period(ms).
    static duration_t const period = 1000UL; // 1.0 s
    static duration_t const onDuty =  100UL; // 0.1 s
    if (get()) {
      if (now - _lit >= onDuty) {
        set(false);
      }
    } else {
      if (now - _lit >= period) {
        set(true);
        _lit = now;
        return true; // Notify caller every time LED turns on
      }
    }
    return false;
  }
};

#endif // LED_h
