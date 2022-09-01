#ifndef Power_h
#define Power_h

#include "sensor.inc.h"

class Power: protected power {
public:
  Power(Board &board): power(board) {}
  virtual ~Power(void) {}
  void update(duration_t now) {

  }
};

#endif // Power_h
