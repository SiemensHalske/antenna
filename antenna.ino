#include "src/config.h"
#include "src/setup.h"
#include "src/sampleISR.h"
#include "src/crc16.h"

static void getTimestamp(uint8_t *ts)
{
  DateTime now = rtc.now();

  ts[0] = now.year() - 2000; // YY
  ts[1] = now.month();       // MM
  ts[2] = now.day();         // DD
  ts[3] = now.hour();        // HH
  ts[4] = now.minute();      // MM
  ts[5] = now.second();      // SS
}

void loop()
{
  if (sampleFlag)
  {
    digitalWrite(LED_BUILTIN, HIGH); // Optional: visualize block start

    uint16_t crc = 0xFFFF;

    uint8_t ts[6];
    getTimestamp(ts);

    // Compute CRC over header
    crc = crc16_update(crc, PREAMBLE_BYTE_1);
    crc = crc16_update(crc, PREAMBLE_BYTE_2);

    uint16_t blockSize = bufferSize * sizeof(sampleBuffer[0]);
    crc = crc16_update(crc, lowByte(blockSize));
    crc = crc16_update(crc, highByte(blockSize));

    for (uint8_t i = 0; i < sizeof(ts); ++i)
    {
      crc = crc16_update(crc, ts[i]);
    }

    for (uint16_t i = 0; i < bufferSize; i++)
    {
      crc = crc16_update(crc, lowByte(sampleBuffer[i]));
      crc = crc16_update(crc, highByte(sampleBuffer[i]));
    }

    // Send Preamble
    Serial.write(PREAMBLE_BYTE_1);
    Serial.write(PREAMBLE_BYTE_2);

    // Send block size
    Serial.write(lowByte(blockSize));
    Serial.write(highByte(blockSize));

    // Send timestamp
    for (uint8_t i = 0; i < sizeof(ts); ++i)
    {
      Serial.write(ts[i]);
    }

    // Send sample data
    for (uint16_t i = 0; i < bufferSize; i++)
    {
      Serial.write(lowByte(sampleBuffer[i]));
      Serial.write(highByte(sampleBuffer[i]));
    }

    // Send CRC
    Serial.write(lowByte(crc));
    Serial.write(highByte(crc));

    // Send Stopbyte
    Serial.write(STOP_BYTE);

    // Reset for next block
    sampleIndex = 0;
    sampleFlag = false;
    Timer1.attachInterrupt(sampleISR); // Restart sampling

    digitalWrite(LED_BUILTIN, LOW); // Optional: visualize block end
  }
}
