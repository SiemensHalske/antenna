#include "setup.h"

void setup()
{
    Serial.begin(1000000); // 1 Mbaud for fast data transfer
    SPI.begin();
    Wire.begin();

    pinMode(CS_PIN, OUTPUT);
    digitalWrite(CS_PIN, HIGH);

    SPI.setClockDivider(SPI_CLOCK_DIV2); // Fastest SPI
    SPI.setDataMode(SPI_MODE0);
    SPI.setBitOrder(MSBFIRST);

    // Init RTC
    if (!rtc.begin())
    {
        Serial.println("RTC not found!");
        while (1)
            ;
    }

    if (rtc.lostPower())
    {
        Serial.println("RTC lost power, setting time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    // Init Timer1 for sampling
    Timer1.initialize(1000000UL / TARGET_SAMPLE_RATE);
    Timer1.attachInterrupt(sampleISR);

    pinMode(LED_BUILTIN, OUTPUT);

    Serial.println("Starting MCP3008 HDSR Sampling with DS3231...");
}
