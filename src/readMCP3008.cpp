#include "readMCP3008.h"

uint16_t readMCP3008(uint8_t channel)
{
    digitalWrite(CS_PIN, LOW);

    SPI.transfer(0x01); // Start bit
    uint8_t highByte = SPI.transfer((0x08 | channel) << 4);
    uint8_t lowByte = SPI.transfer(0x00);

    digitalWrite(CS_PIN, HIGH);

    return ((highByte & 0x03) << 8) | lowByte;
}
