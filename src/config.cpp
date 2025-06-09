#include "config.h"

uint16_t sampleBuffer[BUFFER_SIZE];
volatile bool sampleFlag = false;
volatile uint16_t sampleIndex = 0;

RTC_DS3231 rtc;
