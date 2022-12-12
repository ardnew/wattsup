#ifndef sh1107_i2c_128x64_h
#define sh1107_i2c_128x64_h

#include <Adafruit_SH110X.h>

#include "../../board/Board.h"

#define OLED_ADDRESS   (0x3C)
#define OLED_WIDTH     (64)
#define OLED_HEIGHT    (128)
#define OLED_RST_PULSE (2000U) // milliseconds

class oled: protected Adafruit_SH1107 {
protected:
  bool _ready;
public:
  // Reset the OLED device manually in case we are not wired up to a Feather
  // (or any other board with an active-high RST broken out).
  // Note that the RST pad on the OLED should be connected to GPIO pin on the
  // target (OLED_RST_PIN), and optionally pulled high to VCC, both via 10K
  // resistor(s).
  static Board &reset(Board &board) {
    pinMode(OLED_RST_PIN, OUTPUT);
    board.uart()->print("OLED RST: ");
    for (bool set = Board::pulse(OLED_RST_PIN, HIGH, OLED_RST_PULSE);
      set;
      set = Board::pulse(OLED_RST_PIN)) {
      board.uart()->print(".");
    }
    board.uart()->println();
    return board; // Don't mind me, just passing through...
  }
public:
  oled(Board &board):
    Adafruit_SH1107(OLED_WIDTH, OLED_HEIGHT, board.i2c()),
    _ready(begin(OLED_ADDRESS, true)) {
    if (_ready) {
      cp437(true);
      setTextSize(2);
      setTextColor(SH110X_WHITE);
      setRotation(1);
      clearDisplay();
      setCursor(0, 0);
      display();
    }
    board.uart()->printf("SH1107: %s\r\n", _ready ? "OK" : "FAIL");
  }
  virtual ~oled(void) {}
};

#endif // sh1107_i2c_128x64_h
