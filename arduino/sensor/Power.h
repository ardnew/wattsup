#ifndef Power_h
#define Power_h

#include "sensor.inc.h"

#define POWER_UPDATE_PERIOD_MS (500) // 2 Hz

class Power: protected power {
private:
  Board      *_board;
  duration_t  _period;
  float       _power;
  float       _voltage;
  float       _current;
public:
  Power(Board &board):
    Power(board, POWER_UPDATE_PERIOD_MS) {}
  Power(Board &board, duration_t const period):
    power(board),
    _board(&board),
    _period(period),
    _power(0),
    _voltage(0),
    _current(0) {}
  virtual ~Power(void) {}
  void update(duration_t now) {
    static duration_t last = 0UL;
    if (last == 0UL || now - last >= _period) {
      if (_ready) {
        // _power   = (*this)();
        // _voltage = voltage();
        // _current = current();
        last     = now;
        _board->uart()->printf("%8.2f mW   %8.2f mV   %8.2f mA\r\n", _power, _voltage, _current);
      } else {
        //_board->uart()->println("Power not ready!");
        // begin();
      }
    }
  }
  float milliwatts(void) { return _power; }
  float millivolts(void) { return _voltage; }
  float milliamps(void)  { return _current; }
};

#endif // Power_h
