#ifndef adafruit_qtpy_esp32_pico_h
#define adafruit_qtpy_esp32_pico_h

// +---------------------------------------------------------------------------+
// |  Target peripherals                                                       |
// +---------------------------------------------------------------------------+

#include <Adafruit_NeoPixel.h>
#include <HardwareSerial.h>
#include <Wire.h>

// Select which I/O peripherals will be used

// NOTE:
//   IP := "Integrated Peripheral", which refers to any peripheral embedded
//   within the target MCU, as opposed to peripherals placed with an MCU on a
//   common control board. The term "native" means the same thing, and the two
//   may be interchangeable. IP is just shorter to write.

#define LED_DAT_PIN          (5U) // (PIN_NEOPIXEL)
#define LED_VCC_PIN          (8U) // (NEOPIXEL_POWER)
#define LED_RGB_DEFAULT      (0x0022FF)

#define UART_IP_BUS          (Serial1) // UART1
#define UART_USB_BUS         (Serial)  // CP2102/9 | CP2102N

#define I2C_IP_BUS           (Wire)
#define I2C_IP_SDA_PIN       (4U)  // (SDA)
#define I2C_IP_SCL_PIN       (33U) // (SCL)
#define I2C_QT_BUS           (Wire1)
#define I2C_QT_SDA_PIN       (22U) // (SDA1)
#define I2C_QT_SCL_PIN       (19U) // (SCL1)

#define OLED_RST_PIN         (32U) // (TX)

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
  bool write(bool const on, uint32_t color = LED_RGB_DEFAULT) {
    fill(on ? color : 0x000000);
    show();
    return on;
  }
public:
  led(bool const on = false):
    Adafruit_NeoPixel(1, LED_DAT_PIN, NEO_GRB + NEO_KHZ800),
    _pin(init(LED_DAT_PIN, LED_VCC_PIN)),
    _on(write(on)) {
    begin();
    setBrightness(20);
  }
  virtual ~led(void) {}
  bool get(void) { return _on; }
  void set(bool const on, uint32_t color = LED_RGB_DEFAULT) {
    _on = write(on, color);
  }
};

class uart: public HardwareSerial {
public:
  uart(void):
    HardwareSerial(UART_USB_BUS) {
    begin(115200);
  }
  virtual ~uart(void) {
    end();
  }
};

class i2c: public TwoWire {
public:
  i2c(void):
    TwoWire(I2C_IP_BUS) {
    // Typecast to resolve ambiguous overloaded constructors with default
    // parameters.
    begin((int)I2C_IP_SDA_PIN, (int)I2C_IP_SCL_PIN, (uint32_t)0);
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

#endif // adafruit_qtpy_esp32_pico_h
