#include "src/config.h"
#include "src/setup.h"
#include "src/sampleISR.h"

void sendTimestamp()
{
  DateTime now = rtc.now();

  Serial.write(now.year() - 2000); // YY
  Serial.write(now.month());       // MM
  Serial.write(now.day());         // DD
  Serial.write(now.hour());        // HH
  Serial.write(now.minute());      // MM
  Serial.write(now.second());      // SS
}

void loop()
{
  if (sampleFlag)
  {
    digitalWrite(LED_BUILTIN, HIGH); // Optional: visualize block start

    // Send Preamble
    Serial.write(0xAA);
    Serial.write(0x55);

    // Send block size (bufferSize * 2 bytes)
    uint16_t blockSize = bufferSize * 2;
    Serial.write(lowByte(blockSize));
    Serial.write(highByte(blockSize));

    // Send timestamp
    sendTimestamp();

    // Send sample data
    for (uint16_t i = 0; i < bufferSize; i++)
    {
      Serial.write(lowByte(sampleBuffer[i]));
      Serial.write(highByte(sampleBuffer[i]));
    }

    // Send Stopbyte
    Serial.write(0xFE);

    // Reset for next block
    sampleIndex = 0;
    sampleFlag = false;
    Timer1.attachInterrupt(sampleISR); // Restart sampling

    digitalWrite(LED_BUILTIN, LOW); // Optional: visualize block end
  }
}
