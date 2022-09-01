#ifndef OLED_h
#define OLED_h

#include "display.inc.h"

class OLED: public oled {
public:
  OLED(Board &board): oled(board) {}
  virtual ~OLED(void) {}
  void update(duration_t now) {

  }
};

#endif // OLED_h
