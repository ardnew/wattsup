#ifndef Display_h
#define Display_h

#include "OLED.h"

#include "../sensor/Sensor.h"

class Display {
private:
  Board *_board;
  OLED  *_oled;
public:
  static Board &reset(Board &board) {
    return oled::reset(board);
  }
public:
  Display(Board &board):
    _board(&board), _oled(new OLED(board)) {}
  virtual ~Display(void) {
    if (nullptr != _oled) { delete _oled; }
  }
  void update(duration_t now) {
    _oled->update(now);
  }
  OLED *oled(void) { return _oled; }
};

#endif // Display_h
