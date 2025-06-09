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

const uint8_t PREAMBLE_BYTE_1 = 0xAA; // Frame preamble first byte
const uint8_t PREAMBLE_BYTE_2 = 0x55; // Frame preamble second byte
const uint8_t STOP_BYTE = 0xFE;       // Frame stop byte

extern uint16_t sampleBuffer[BUFFER_SIZE]; // Buffer to hold samples
extern volatile bool sampleFlag;           // Flag to indicate buffer is full
extern volatile uint16_t sampleIndex;      // Current index in the sample buffer

extern RTC_DS3231 rtc;

#endif // CONFIG_H
