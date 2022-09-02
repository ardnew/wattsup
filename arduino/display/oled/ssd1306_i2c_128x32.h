#ifndef ssd1306_i2c_128x32_h
#define ssd1306_i2c_128x32_h

#include <Adafruit_SSD1306.h>

#include "../../board/Board.h"

#define OLED_ADDRESS (0x3C)
#define OLED_WIDTH   (128)
#define OLED_HEIGHT  (32)

class oled: protected Adafruit_SSD1306 {
protected:
  bool _ready;
public:
  oled(Board &board):
    Adafruit_SSD1306(OLED_WIDTH, OLED_HEIGHT, board.i2c()),
    _ready(begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS, false, false)) {
    if (_ready) {
      cp437(true);
      setTextSize(1);
      setTextColor(SSD1306_WHITE);
      clearDisplay();
    }
    board.uart()->printf("SSD1306: %s\n", _ready ? "OK" : "FAIL");
  }
  virtual ~oled(void) {}
};

#endif // ssd1306_i2c_128x32_h
