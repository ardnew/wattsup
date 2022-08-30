// arduino.ino (automatically generated 2022-08-28 14:55:37 CDT)

#include "board/Board.h"

static Board *board;

void setup() {
  board = new Board;
}

void loop() {
  board->update(millis());
}
