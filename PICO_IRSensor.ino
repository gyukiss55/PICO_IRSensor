

#include "IRSensor.h"
#include "ILI9225.h"

void setup() {
	Serial.begin(115200);
	delay (2000);
	setup_TFT ();
	setupIRSensor ();
}

void loop ()
{
	loopIRSensor ();
}

