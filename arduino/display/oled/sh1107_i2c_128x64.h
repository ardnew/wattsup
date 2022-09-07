#ifndef sh1107_i2c_128x64_h
#define sh1107_i2c_128x64_h

#include <Adafruit_SH110X.h>

#include "../../board/Board.h"

#define OLED_ADDRESS (0x3C)
#define OLED_WIDTH   (128)
#define OLED_HEIGHT  (32)

class oled: protected Adafruit_SH1107 {
protected:
  bool _ready;
public:
  oled(Board &board):
    Adafruit_SH1107(OLED_WIDTH, OLED_HEIGHT, board.i2c()),
    _ready(begin(OLED_ADDRESS, true)) {
    if (_ready) {
      cp437(true);
      setTextSize(1);
      setTextColor(SH110X_WHITE);
      setRotation(1);
      clearDisplay();
      setCursor(0, 0);
      print("This is a test");
      display();
    }
    board.uart()->printf("SH1107: %s\n", _ready ? "OK" : "FAIL");
  }
  virtual ~oled(void) {}
};

#endif // sh1107_i2c_128x64_h
