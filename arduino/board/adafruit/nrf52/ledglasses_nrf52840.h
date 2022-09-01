#ifndef ledglasses_nrf52840_h
#define ledglasses_nrf52840_h

#include <Adafruit_TinyUSB.h>
#include <Wire.h>

#define PIN_LED (PIN_LED1)

#define LED_ON          (LED_STATE_ON)
#define LED_OFF         !(LED_STATE_ON)
#define LED_STATE(bool) ((bool) ? (LED_ON) : (LED_OFF))

class uart: public Adafruit_USBD_CDC {
public:
  uart(void): Adafruit_USBD_CDC(Serial) {
    begin(115200);
  }
  virtual ~uart(void) {
    end();
  }
};

class i2c: public TwoWire {
public:
  i2c(void): TwoWire(Wire) {
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

// Return type of Arduino core function millis()
typedef unsigned long duration_t;

#endif // ledglasses_nrf52840_h
