#ifndef LED_h
#define LED_h

#include "board.inc.h"

#define LED_PULSE_PERIOD  (1000UL) // 1.0 s
#define LED_PULSE_ONDUTY   (100UL) // 0.1 s

class LED: public led {
protected:
  duration_t const _period;
  duration_t const _onDuty;
  duration_t _lit;
public:
  LED(void): LED(LED_PULSE_PERIOD, LED_PULSE_ONDUTY) {}
  LED(duration_t const period, duration_t const onDuty):
    _period(period), _onDuty(onDuty), _lit(0) {}
  virtual ~LED(void) {}
  bool update(duration_t const now) {
    // Turn LED on for onDuty(ms) every period(ms).
    static byte pos = 0;
    pos += 4;
    if (get()) {
      if (now - _lit >= _onDuty) {
        set(false);
      }
    } else {
      if (now - _lit >= _period) {
        set(true,  wheel(pos));
        _lit = now;
        return true; // Notify caller every time LED turns on
      }
    }
    return false;
  }
public:
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
};

#endif // LED_h
