#ifndef adafruit_qtpy_esp32_pico_h
#define adafruit_qtpy_esp32_pico_h

// +---------------------------------------------------------------------------+
// |  Target peripherals                                                       |
// +---------------------------------------------------------------------------+

#include <Adafruit_NeoPixel.h>
#include <HardwareSerial.h>
#include <Wire.h>

// Peripherals

#define PIN_LED          (PIN_NEOPIXEL)
#define PIN_VLED         (NEOPIXEL_POWER)

#define UART_IP          (Serial1)
#define UART_USB         (Serial)

#define I2C_IP           (Wire)
#define PIN_I2C_IP_SDA   (SDA)
#define PIN_I2C_IP_SCL   (SCL)
#define I2C_QT           (Wire1)
#define PIN_I2C_QT_SDA   (SDA1)
#define PIN_I2C_QT_SCL   (SCL1)

// +---------------------------------------------------------------------------+
// |  Hardware abstraction layer (HAL)                                         |
// +---------------------------------------------------------------------------+

// Return type of Arduino core function millis()
typedef unsigned long duration_t;

class led: public Adafruit_NeoPixel {
protected:
  uint16_t _pin;
  bool     _on;
  uint16_t init(uint16_t const pin, uint16_t const vpin) {
    pinMode(pin, OUTPUT);
    pinMode(vpin, OUTPUT);
    digitalWrite(vpin, HIGH);
    return pin;
  }
  bool write(bool const on) {
    fill(on ? 0x0022FF : 0x000000);
    show();
    return on;
  }
public:
  led(bool const on = false):
    Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800),
    _pin(init(PIN_LED, PIN_VLED)),
    _on(write(on)) {
    begin();
    setBrightness(20);
  }
  virtual ~led(void) {}
  bool get(void) { return _on; }
  void set(bool const on) { _on = write(on); }
};

class uart: public HardwareSerial {
public:
  uart(void):
    HardwareSerial(UART_USB) {
    begin(115200);
  }
  virtual ~uart(void) {
    end();
  }
};

class i2c: public TwoWire {
public:
  i2c(void):
    TwoWire(I2C_IP) {
    // Typecast to resolve ambiguous overloaded constructors with default
    // parameters.
    begin((int)PIN_I2C_IP_SDA, (int)PIN_I2C_IP_SCL, (uint32_t)0);
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

#endif // adafruit_qtpy_esp32_pico_h
