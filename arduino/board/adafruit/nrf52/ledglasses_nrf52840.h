#ifndef ledglasses_nrf52840_h
#define ledglasses_nrf52840_h

// +---------------------------------------------------------------------------+
// |  Target peripherals                                                       |
// +---------------------------------------------------------------------------+

#include <Adafruit_TinyUSB.h>
#include <Wire.h>

// Peripherals

#define UART_IP          (Serial1)

#define PIN_LED           (PIN_LED1)

#define UART_USB          (Serial)

#define I2C_QT            (Wire)

// +---------------------------------------------------------------------------+
// |  Hardware abstraction layer (HAL)                                         |
// +---------------------------------------------------------------------------+

// Return type of Arduino core function millis()
typedef unsigned long duration_t;

class led {
protected:
  uint16_t _pin;
  bool     _on;
  uint16_t init(uint16_t const pin) {
    pinMode(pin, OUTPUT);
    return pin;
  }
  bool write(bool const on) {
    digitalWrite(_pin, on ? HIGH : LOW);
    return on;
  }
public:
  led(bool const on = false):
    _pin(init(PIN_LED)),
    _on(write(on)) {}
  virtual ~led(void) {}
  bool get(void) { return _on; }
  void set(bool const on) { _on = write(on); }
};

class uart: public Adafruit_USBD_CDC {
public:
  uart(void):
    Adafruit_USBD_CDC(UART_USB) {
    begin(115200);
  }
  virtual ~uart(void) {
    end();
  }
};

class i2c: public TwoWire {
public:
  i2c(void):
    TwoWire(I2C_QT) {
    begin();
  }
  virtual ~i2c(void) {
    end();
  }
  void initTransfer(uint8_t addr) {
    beginTransmission(addr);
  }
  uint8_t endTransfer(void) {
    return endTransmission();
  }
  uint8_t endTransfer(bool stop) {
    return endTransmission(stop);
  }
};

class board {
public:
  board(void) {}
  virtual ~board(void) {}
  void update(duration_t const now) { (void)now; }
};

#endif // ledglasses_nrf52840_h
