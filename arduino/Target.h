#ifndef Target_h
#define Target_h

#include "board/Board.h"
#include "sensor/Sensor.h"
// #include "display/Display.h"

class Target {
private:
  Board   *_board;
  Sensor  *_sensor;
  // Display *_display;
public:
  Target(void):
    _board(new Board),
    _sensor(new Sensor(*_board)) {}
    // _display(new Display(*_board)) {}
  virtual ~Target(void) {
    // if (nullptr != _display) { delete _display; }
    if (nullptr != _sensor)  { delete _sensor; }
    if (nullptr != _board)   { delete _board; }
  }
  void update(duration_t now) {
    _board->update(now);
    _sensor->update(now);
    // _display->update(now);

    // static float power = -999.0F;
    // float mW = _sensor->power()->milliwatts();
    // if (fabs(mW - power) > 0.005F) {
    //   float mV = _sensor->power()->millivolts();
    //   float mA = _sensor->power()->milliamps();
    //   _display->oled()->clear();
    //   _display->oled()->setCursor(0, 0);
    //   _display->oled()->printf("%+7.2f mW\n", mW);
    //   _display->oled()->printf("%+7.2f mV\n", mV);
    //   _display->oled()->printf("%+7.2f mA\n", mA);
    // }
  }
};

#endif // Target_h
