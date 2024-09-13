// IRSensor.cpp

#include <Arduino.h>
#include "IRSensor.h"

#define LED_DEF 25
#define IR_LED_DEF 14
#define IR_LEDDET_DEF 15
#define ExtInterruptTSvectorSize 20

uint32_t extInterruptTSvector[ExtInterruptTSvectorSize];
uint32_t extInterruptDTSvector[ExtInterruptTSvectorSize];
uint32_t extInterruptTSindex = 0;
uint32_t extInterruptTScount = 0;

void ReadIRDetect()
{
    extInterruptTSvector[extInterruptTSindex] = micros();
    extInterruptTScount++;
    if (extInterruptTScount > 1) {
        uint32_t prev = ExtInterruptTSvectorSize - 1;
        if (extInterruptTSindex > 0)
            prev = extInterruptTSindex - 1;
        extInterruptDTSvector[extInterruptTSindex] = extInterruptTSvector[extInterruptTSindex] - extInterruptTSvector[prev];
    }
    extInterruptTSindex++;
    if (extInterruptTSindex >= ExtInterruptTSvectorSize)
        extInterruptTSindex = 0;
}

void setupIRSensor() {
    Serial.begin(115200);

    pinMode(LED_DEF, OUTPUT);
    pinMode(IR_LED_DEF, OUTPUT);
    pinMode(IR_LEDDET_DEF, INPUT);
    attachInterrupt(IR_LEDDET_DEF, ReadIRDetect, RISING); // CHANGE  FALLING  RISING
}

void loopBlinkIRLED()
{
    static uint32_t tsLast = 0;
    static bool state = false;
    uint32_t tsNow = millis();
    if (tsNow - tsLast >= 100) {
        if (state) {
            digitalWrite(IR_LED_DEF, HIGH);
        }
        else {
            digitalWrite(IR_LED_DEF, LOW);
        }
        state = !state;
        tsLast = tsNow;
    }
}

uint32_t Prev(uint32_t i)
{
    uint32_t prev = ExtInterruptTSvectorSize - 1;
    if (i > 0) {
        prev = i - 1;

    }
    return prev;
}

void loopIRSensor() {

    loopBlinkIRLED();

    static uint32_t tsLast = 0;
    uint32_t tsNow = millis();
    if (tsNow - tsLast >= 2000) {
        tsLast = tsNow;
        uint32_t i1 = Prev(extInterruptTSindex);
        uint32_t tsNowMicro = micros();
        if (tsNowMicro > extInterruptTSvector[i1]  && tsNowMicro - extInterruptTSvector[i1] < 3000000)
        {
            Serial.print(extInterruptTSvector[i1]);
            Serial.print(":");
            for (int i = 0; i < 10; i++) {
                if (i >= (int)extInterruptTScount - 2)
                    break;
                if (i > 0)
                    Serial.print(",");
                Serial.print(extInterruptDTSvector[i1]);
                i1 = Prev (i1);            
            }
            Serial.println("");
        }
    }
    if (digitalRead(IR_LEDDET_DEF))
        digitalWrite(LED_DEF, HIGH);
    else
        digitalWrite(LED_DEF, LOW);

}
