#ifndef st7789_spi_135x240_h
#define st7789_spi_135x240_h

// #include "st7789_spi_135x240_setup.h"
// #include <TFT_eSPI.h>

#include "../../board/Board.h"

#define OLED_WIDTH     (135)
#define OLED_HEIGHT    (240)
#define OLED_RST_PULSE (2000U) // milliseconds

class oled { //: protected TFT_eSPI {
protected:
  bool _ready;
public:
  static Board &reset(Board &board) {
    board.uart()->print("OLED RST: TODO");
    board.uart()->println();
    return board; // Don't mind me, just passing through...
  }
public:
  //oled(Board &board):
  //  TFT_eSPI(OLED_WIDTH, OLED_HEIGHT) {
  //  init();
  //  _ready = true;
  //  if (_ready) {
  //    _cp437 = true;
  //    setTextSize(2);
  //    setTextColor(TFT_WHITE);
  //    setRotation(1);
  //    clearDisplay();
  //    setCursor(0, 0);
  //    display();
  //  }
  //  board.uart()->printf("ST7789: %s\r\n", _ready ? "OK" : "FAIL");
  //}
  oled(Board &board){}
  virtual ~oled(void) {}
  void clearDisplay(void) {
    //fillScreen(0);
  }
  void display(void) {}
};

#endif // st7789_spi_135x240_h
