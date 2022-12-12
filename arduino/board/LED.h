#ifndef LED_h
#define LED_h

#include "board.inc.h"

class LED: public led {
private:
  duration_t _lit;
  static inline constexpr uint32_t rgb(uint32_t r, uint32_t g, uint32_t b) {
    return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
  }
  static inline uint32_t wheel(byte pos) {
    pos = 255 - (pos);
    if (pos < 85) {
      return rgb(255 - pos * 3, 0, pos * 3);
    } else if (pos < 170) {
      pos -= 85;
      return rgb(0, pos * 3, 255 - pos * 3);
    }
    pos -= 170;
    return rgb(pos * 3, 255 - pos * 3, 0);
  }
public:
  LED(void):
    _lit(0) {}
  virtual ~LED(void) {}
  bool update(duration_t const now) {
    // Turn LED on for onDuty(ms) every period(ms).
    static duration_t const period = 1000UL; // 1.0 s
    static duration_t const onDuty =  100UL; // 0.1 s
    static byte pos = 0;
    pos += 4;
    if (get()) {
      if (now - _lit >= onDuty) {
        set(false);
      }
    } else {
      if (now - _lit >= period) {
        set(true,  wheel(pos));
        _lit = now;
        return true; // Notify caller every time LED turns on
      }
    }
    return false;
  }
};

#endif // LED_h
