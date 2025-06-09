#include "config.h"

unsigned int bufferSize = DEFAULT_BUFFER_SIZE;
unsigned int targetSampleRate = DEFAULT_SAMPLE_RATE;
uint16_t* sampleBuffer = nullptr;
volatile bool sampleFlag = false;
volatile uint16_t sampleIndex = 0;

RTC_DS3231 rtc;
