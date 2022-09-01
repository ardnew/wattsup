#ifndef Display_h
#define Display_h

#include "OLED.h"

class Display {
private:
  OLED *_oled;
public:
  Display(Board &board):
    _oled(new OLED(board)) {}
  virtual ~Display(void) {
    if (nullptr != _oled) { delete _oled; }
  }
  void update(duration_t now) {
    _oled->update(now);
  }
};

#endif // Display_h
