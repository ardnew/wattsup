#ifndef ledglasses_nrf52840_h
#define ledglasses_nrf52840_h

#include <Adafruit_TinyUSB.h>
#include <Wire.h>

#define PIN_LED (PIN_LED1)

#define LED_ON          (LED_STATE_ON)
#define LED_OFF         !(LED_STATE_ON)
#define LED_STATE(bool) ((bool) ? (LED_ON) : (LED_OFF))

#define UART_BUS (Serial)
#define I2C_BUS  (Wire)

class UART: public Adafruit_USBD_CDC {
public:
  UART(Adafruit_USBD_CDC &bus): Adafruit_USBD_CDC(bus) {
    begin(115200);
  }
  virtual ~UART(void) {}
};

class I2C: public TwoWire {
public:
  I2C(TwoWire &bus): TwoWire(bus) {
    begin();
  }
  virtual ~I2C(void) {}
};

// Return type of Arduino core function millis()
typedef unsigned long duration_t;

#endif // ledglasses_nrf52840_h
