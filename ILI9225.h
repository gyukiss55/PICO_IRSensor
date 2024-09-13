/* ILI9225 */ 
#include <Arduino.h>
#include "SPI.h"
#include "TFT_22_ILI9225.h"

#ifdef ARDUINO_ARCH_STM32F1
#define TFT_RST PA1
#define TFT_RS  PA2
#define TFT_CS  PA0 // SS
#define TFT_SDI PA7 // MOSI
#define TFT_CLK PA5 // SCK
#define TFT_LED 0 // 0 if wired to +5V directly
#elif defined(ESP8266)
#define TFT_RST 4   // D2
#define TFT_RS  5   // D1
#define TFT_CLK 14  // D5 SCK
//#define TFT_SDO 12  // D6 MISO
#define TFT_SDI 13  // D7 MOSI
#define TFT_CS  15  // D8 SS
#define TFT_LED 2   // D4     set 0 if wired to +5V directly -> D3=0 is not possible !!
#elif defined(ESP32)
#define TFT_RST 26  // IO 26
#define TFT_RS  25  // IO 25
#define TFT_CLK 14  // HSPI-SCK
//#define TFT_SDO 12  // HSPI-MISO
#define TFT_SDI 13  // HSPI-MOSI
#define TFT_CS  15  // HSPI-SS0
#define TFT_LED 0   // 0 if wired to +5V directly
#elif defined(ARDUINO_ARCH_RP2040)
#define TFT_RST 7  // GP 7
#define TFT_RS  6  // GP 6
#define TFT_CLK 18  // GP 2 (SPI0 - CLK)
#define TFT_SDO 16  // GP4 (SPI0 - MISO)
#define TFT_SDI 19  // GP3 (SPI0 - MOSI)
#define TFT_CS  17  // GP4 (SPI0 - CS)
#define TFT_LED 0   // 0 if wired to +5V directly
//ARDUINO_ARCH_RP2040 !!! ???
#else
mialofasz!
#define TFT_RST 8
#define TFT_RS  9
#define TFT_CS  10  // SS
#define TFT_SDI 11  // MOSI
#define TFT_CLK 13  // SCK
#define TFT_LED 3   // 0 if wired to +5V directly
#endif

#define TFT_BRIGHTNESS 200 // Initial brightness of TFT backlight (optional)


extern TFT_22_ILI9225 tft;

void setup_TFT ();
