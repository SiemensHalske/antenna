#ifndef CONFIG_H
#define CONFIG_H

#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"
#include <TimerOne.h>

const int CS_PIN = 10;                // MCP3008 CS
const int ADC_CHANNEL = 0;            // MCP3008 channel to read (0-7)
const int BUFFER_SIZE = 256;          // Number of samples per block
const int TARGET_SAMPLE_RATE = 75000; // 75 kSPS

uint16_t sampleBuffer[BUFFER_SIZE]; // Buffer to hold samples
volatile bool sampleFlag = false;   // Flag to indicate buffer is full
volatile uint16_t sampleIndex = 0;  // Current index in the sample buffer

RTC_DS3231 rtc;

#endif // CONFIG_H