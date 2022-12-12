#ifndef OLED_h
#define OLED_h

#include "display.inc.h"

#define OLED_UPDATE_PERIOD_MS (250) // 4 Hz

class OLED: public oled {
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
  void clear(void) {
    clearDisplay();
  }
};

#endif // OLED_h
