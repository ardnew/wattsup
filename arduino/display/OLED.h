#ifndef OLED_h
#define OLED_h

#include "display.inc.h"

#define OLED_UPDATE_PERIOD_MS (250) // 4 Hz

class OLED: protected oled {
private:
  Board      *_board;
  duration_t  _period;
public:
  OLED(Board &board):
    OLED(board, OLED_UPDATE_PERIOD_MS) {}
  OLED(Board &board, duration_t const period):
    oled(board),
    _board(&board),
    _period(period) {}
  virtual ~OLED(void) {}
  void update(duration_t now) {
    static duration_t last = 0UL;
    if (now - last >= _period) {
      if (_ready) {
        display();
        last = now;
      } else {
        _board->uart()->println("OLED not ready!");
      }
    }
  }
  // Exported protected methods
  void clear(void) {
    oled::clearDisplay();
  }
  void setCursor(int16_t const x, int16_t const y) {
  //  oled::setCursor(x, y);
  }
  size_t printf(const char * format, ...) {
  //  static size_t const bufsz = 256;
  //  char buf[bufsz];
  //  va_list ap;
  //  va_start(ap, format);
  //  int len = vsnprintf(buf, bufsz, format, ap);
  //  oled::print(buf); // vsnprintf always null-terminates
  //  va_end(ap);
  //  return len;
  }
  //size_t print(const char *p)   { return oled::print(p); }
  //size_t print(int d, int base) { return oled::print(d, base); }
  //size_t println(void)          { return oled::println(); }
  //size_t println(const char *p) { return oled::println(p); }
};

#endif // OLED_h
