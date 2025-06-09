#include "setup.h"
#include "sampleISR.h"

static void setSamplingParameters(unsigned int rate, unsigned int size)
{
    targetSampleRate = rate;
    bufferSize = size;

    if (sampleBuffer)
    {
        delete[] sampleBuffer;
    }

    sampleBuffer = new uint16_t[bufferSize];
    sampleIndex = 0;

    Timer1.initialize(1000000UL / targetSampleRate);
    Timer1.attachInterrupt(sampleISR);
}

void configureSampling()
{
    unsigned int rate = DEFAULT_SAMPLE_RATE;
    unsigned int size = DEFAULT_BUFFER_SIZE;

    Serial.println("Send 'rate size' within 3s to override defaults...");
    unsigned long start = millis();
    while (millis() - start < 3000)
    {
        if (Serial.available())
        {
            rate = Serial.parseInt();
            size = Serial.parseInt();
            break;
        }
    }

    if (rate == 0)
        rate = DEFAULT_SAMPLE_RATE;
    if (size == 0)
        size = DEFAULT_BUFFER_SIZE;

    setSamplingParameters(rate, size);
}

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

    // Configure sampling parameters and Timer1
    configureSampling();

    pinMode(LED_BUILTIN, OUTPUT);

    Serial.println("Starting MCP3008 HDSR Sampling with DS3231...");
}
