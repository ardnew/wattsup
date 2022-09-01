#ifndef Target_h
#define Target_h

#include "board/Board.h"
#include "sensor/Sensor.h"
#include "display/Display.h"

class Target {
private:
  Board   *_board;
  Sensor  *_sensor;
  Display *_display;
public:
  Target(void):
    _board(new Board),
    _sensor(new Sensor(*_board)),
    _display(new Display(*_board)) {}
  virtual ~Target(void) {
    if (nullptr != _display) { delete _display; }
    if (nullptr != _sensor)  { delete _sensor; }
    if (nullptr != _board)   { delete _board; }
  }
  void update(duration_t now) {
    _board->update(now);
    _sensor->update(now);
    _display->update(now);
  }
};

#endif // Target_h
