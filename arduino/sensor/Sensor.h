#ifndef Sensor_h
#define Sensor_h

#include "Power.h"

class Sensor {
private:
  Board *_board;
  Power *_power;
public:
  Sensor(Board &board):
    _board(&board),
    _power(new Power(board)) {}
  virtual ~Sensor(void) {
    if (nullptr != _power) { delete _power; }
  }
  void update(duration_t now) {
    _power->update(now);
  }
  Power *power(void) { return _power; }
};

#endif // Sensor_h
