#ifndef ssd1306_i2c_128x32_h
#define ssd1306_i2c_128x32_h

#include <Adafruit_SSD1306.h>

#include "../../board/Board.h"

#define OLED_WIDTH  (128)
#define OLED_HEIGHT (32)

class oled: protected Adafruit_SSD1306 {
public:
  oled(Board &board):
    Adafruit_SSD1306(OLED_WIDTH, OLED_HEIGHT, board.i2c()) {
    begin(SSD1306_SWITCHCAPVCC);
  }
  virtual ~oled(void) {}
};

#endif // ssd1306_i2c_128x32_h
