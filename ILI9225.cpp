// Include application, user and local libraries

#include <Arduino.h>
#include <SPI.h>
#include "TFT_22_ILI9225.h"
#include "ILI9225.h"


// Use hardware SPI (faster - on Uno: 13-SCK, 12-MISO, 11-MOSI)
TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED, TFT_BRIGHTNESS);
// Use software SPI (slower)
//TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_SDI, TFT_CLK, TFT_LED, TFT_BRIGHTNESS);

void setup_TFT ()
{
#if defined(ESP32)
	hspi.begin();
	tft.begin(hspi);
#elif defined(ARDUINO_ARCH_RP2040)
	SPI.setRX(TFT_SDO); // or setMISO()
	SPI.setCS(TFT_CS);
	SPI.setSCK(TFT_CLK);
	SPI.setTX(TFT_SDI); // or setMOSI()
	SPI.begin();

	//ARDUINO_ARCH_RP2040 ???
#else
	tft.begin();
#endif
	tft.fillRectangle(0, 0, tft.maxX() - 1, tft.maxY() - 1, COLOR_BLACK);
	int displayRow = 1;
	tft.setFont(Terminal6x8);
	tft.drawText(10, (displayRow++) * 10, "hello small font!");
	tft.setFont(Terminal12x16);
	tft.drawText(10, (displayRow++) * 10, "hello big font!", COLOR_RED); 
	tft.setBackgroundColor(COLOR_BLACK);
	tft.setFont(Terminal6x8);
	tft.setBacklight(HIGH);
	tft.setOrientation(1);
	delay(1000);
	tft.fillRectangle(0, 0, tft.maxX() - 1, tft.maxY() - 1, COLOR_BLACK);
	displayRow = 1;
	tft.drawText(10, (displayRow++) * 10, "BNO055 WEB server version test v1.0!");
}
