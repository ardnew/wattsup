#ifndef ina260_i2c_h
#define ina260_i2c_h

#include <Adafruit_INA260.h>

#include "../../board/Board.h"

#define POWER_ADDRESS    (0x40)
#define POWER_ADC_PERIOD (INA260_TIME_2_116_ms) // 2.116ms
#define POWER_ADC_SAMPLE (INA260_COUNT_64)      //  x64 = 135.424ms

class power: protected Adafruit_INA260 {
private:
  Board *_board;
protected:
  bool _ready;
public:
  power(Board &board):
    Adafruit_INA260(),
    _board(&board) {
    if ((_ready = Adafruit_INA260::begin(POWER_ADDRESS, _board->i2c()))) {
      setCurrentConversionTime(POWER_ADC_PERIOD);
      setVoltageConversionTime(POWER_ADC_PERIOD);
      setAveragingCount(POWER_ADC_SAMPLE);
    }
    _board->uart()->printf("INA260: %s\r\n", _ready ? "OK" : "FAIL");
  }
  virtual ~power(void) {}
  float operator ()(void) { return _ready ? readPower() : 0.0F; }
  float voltage(void)     { return _ready ? readBusVoltage() : 0.0F; }
  float current(void)     { return _ready ? readCurrent() : 0.0F; }
};

#endif // ina260_i2c_h
