#include "sampleISR.h"
#include "readMCP3008.h"

void sampleISR()
{
    if (sampleIndex < BUFFER_SIZE)
    {
        sampleBuffer[sampleIndex++] = readMCP3008(ADC_CHANNEL);
    }
    else
    {
        sampleFlag = true;
        Timer1.detachInterrupt(); // Stop sampling until block is sent
    }
}