#ifndef UART_h
#define UART_h

#include "board.inc.h"

class UART: public uart {
public:
  UART(void) {}
  virtual ~UART(void) {}
  size_t print(const char *p) {
    return uart::print(p);
  }
  size_t print(int d, int base) {
    return uart::print(d, base);
  }
  size_t println(void) {
    return uart::println();
  }
  size_t println(const char *p) {
    return uart::println(p);
  }
};

#endif // UART_h
