#ifndef st7789_spi_135x240_h
#define st7789_spi_135x240_h

// #include "st7789_spi_135x240_setup.h"

#include <TFT_eSPI.h>

#include "../../board/Board.h"

#define OLED_WIDTH     (135)
#define OLED_HEIGHT    (240)
#define OLED_RST_PULSE (2000U) // milliseconds

class oled: public TFT_eSPI {
protected:
  bool _ready;
public:
  static Board &reset(Board &board) {
    board.uart()->print("OLED RST: TODO");
    board.uart()->println();
    return board; // Don't mind me, just passing through...
  }
public:
  oled(Board &board): TFT_eSPI() {
    begin();
    _ready = true;
    setTextColor(TFT_WHITE, TFT_BLACK);
    clearDisplay();
    board.uart()->printf("ST7789: %s\r\n", _ready ? "OK" : "FAIL");
  }
  virtual ~oled(void) {}
  void clearDisplay(void) {
    fillScreen(TFT_BLACK);
  }
  void display(void) { yield(); }
};

#endif // st7789_spi_135x240_h
