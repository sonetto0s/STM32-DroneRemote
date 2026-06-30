#include "remote.h"


extern  volatile uint16_t adc_buf[4];

Channels ch;

int crcme(uint8_t *data,uint16_t len)
{
    uint8_t crc=0;
    for (int i = 0; i < len; i++)
    {
        crc ^= data[i];
    }
    return crc;
}

