#ifndef ina260_i2c_h
#define ina260_i2c_h

#include <Adafruit_INA260.h>

#include "../../board/Board.h"

#define POWER_ADDRESS    (0x40)
#define POWER_ADC_PERIOD (INA260_TIME_2_116_ms) // 2.116ms
#define POWER_ADC_SAMPLE (INA260_COUNT_64)      //  x64 = 135.424ms

class power: protected Adafruit_INA260 {
protected:
  bool _ready;
public:
  power(Board &board):
    Adafruit_INA260(),
    _ready(begin(POWER_ADDRESS, board.i2c())) {
    if (_ready) {
      setCurrentConversionTime(POWER_ADC_PERIOD);
      setVoltageConversionTime(POWER_ADC_PERIOD);
      setAveragingCount(POWER_ADC_SAMPLE);
    }
    board.uart()->printf("INA260: %s\n", _ready ? "OK" : "FAIL");
  }
  virtual ~power(void) {}
  float operator ()(void) { return readPower(); }
  float voltage(void)     { return readBusVoltage(); }
  float current(void)     { return readCurrent(); }
};

#endif // ina260_i2c_h
