#ifndef m5stick_c_plus_h
#define m5stick_c_plus_h

// +---------------------------------------------------------------------------+
// |  Target peripherals                                                       |
// +---------------------------------------------------------------------------+

#include <Wire.h>
#include <HardwareSerial.h>
#include <I2C_AXP192.h>
// #include <M5StickCPlus.h>

// Select which I/O peripherals will be used

// NOTE:
//   IP := "Integrated Peripheral", which refers to any peripheral embedded
//   within the target MCU, as opposed to peripherals placed with an MCU on a
//   common control board. The term "native" means the same thing, and the two
//   may be interchangeable. IP is just shorter to write.

#define LED_BUILTIN_PIN      (10U) // (Red LED)

//#define IR_TX_PIN            (9U)

#define BUTTON_A_PIN         (37U) // (HOME)
#define BUTTON_B_PIN         (39U) // (RESET)

//#define LEDC_SPKR_PIN        (2U)
//#define LEDC_SPKR_CHAN       (0U)

#define UART_USB_BUS         (Serial) // (FTDI FT232xx)
#define UART_USB_BAUD        (115200U) // Meaningless for USB CDC-ACM

#define I2C_EXT_BUS          (Wire)
#define I2C_POW_BUS          (I2C_EXT_BUS) // (INA260)

#define I2C_IP_BUS           (Wire1)
#define I2C_IMU_BUS          (I2C_IP_BUS) // (MPU6886)
#define I2C_PMU_BUS          (I2C_IP_BUS) // (AXP192)
#define I2C_PMU_ADDRESS      (0x34) // (I2C_AXP192_DEFAULT_ADDRESS)

//#define I2S_MIC_BUS          (I2S_NUM_0) // (SPM1423)
//#define I2S_MIC_CLK_PIN      (0U)
//#define I2S_MIC_DAT_PIN      (34U)

#define SPI_IP_BUS           (SPI)
#define SPI_OLED_BUS         (SPI_IP_BUS) // (ST7789v2)
#define SPI_OLED_SDO_PIN     (15U) // (MOSI)
#define SPI_OLED_SDI_PIN     (36U) // (MISO)
#define SPI_OLED_SCK_PIN     (13U) // (SCK)
#define SPI_OLED_CS_PIN      (5U)  // (SS)
#define SPI_OLED_DC_PIN      (23U)
#define SPI_OLED_RST_PIN     (18U)

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
    digitalWrite(_pin, on ? LOW : HIGH);
    return on;
  }
public:
  led(void): led(LED_BUILTIN_PIN) {}
  led(uint16_t const pin): led(pin, false) {}
  led(uint16_t const pin, bool const on):
    _pin(init(pin)),
    _on(write(on)) {
  }
  virtual ~led(void) {}
  bool get(void) { return _on; }
  void set(bool const on) { set(on, 0UL); }
  void set(bool const on, uint32_t color) {
    (void)color;
    _on = write(on);
  }
};

class uart: public HardwareSerial {
public:
  uart(void): uart(UART_USB_BUS) {}
  uart(HardwareSerial &bus): uart(bus, UART_USB_BAUD) {}
  uart(HardwareSerial &bus, uint32_t baud):
    HardwareSerial(bus) {
    begin(baud);
    flush();
  }
  virtual ~uart(void) { end(); }
};

class i2c: public TwoWire {
public:
  i2c(void): i2c(I2C_EXT_BUS) {}
  i2c(TwoWire &bus): TwoWire(bus) {}
  virtual ~i2c(void) { end(); }
};

class pmu: public I2C_AXP192 {
public:
  pmu(void): pmu(I2C_PMU_BUS) {}
  pmu(TwoWire &bus): pmu(bus, I2C_PMU_ADDRESS) {}
  pmu(TwoWire &bus, uint8_t const addr):
    I2C_AXP192(addr, bus) {
    begin(I2C_AXP192_InitDef{
      .EXTEN  = true, // bool (+5V OUT)
      .BACKUP = true, // bool (RTC)
      .DCDC1  = 3300, // int  (MCU  = 3.3V)
      .DCDC2  = 0,    // int
      .DCDC3  = 0,    // int
      .LDO2   = 3000, // int  (BKLT = 3.0V)
      .LDO3   = 3000, // int  (TFT  = 3.0V)
      .GPIO0  = 3301, // int  (RTC  = 3.3V)
      .GPIO1  = 0,    // int
      .GPIO2  = 0,    // int
      .GPIO3  = 0,    // int
      .GPIO4  = 0,    // int
    });
  }
  virtual ~pmu(void) { powerOff(); }
};

class board {
protected:
  i2c *_i2c; // Internal I2C bus (IMU, PMU)
  pmu *_pmu;
public:
  board(void):
    _i2c(new i2c(I2C_IP_BUS)),
    _pmu(new pmu(I2C_PMU_BUS)) {}
  virtual ~board(void) {
    if (nullptr != _i2c) { delete _i2c; }
    if (nullptr != _pmu) { delete _pmu; }
  }
  void update(duration_t const now) { (void)now; }
};

#endif // m5stick_c_plus_h
