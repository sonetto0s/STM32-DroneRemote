#include "sbus.h"

uint8_t sbus_frame[SBUS_FRAME_LEN];
//uint16_t ch;
static uint16_t sbus_map(int16_t value)
{
    if (value < 1000)
        value = 1000;
    if(value>2000)
        value = 2000;

    return (value - 1000) * 1639 / 1000 + 172;
}


void sbus_encoder(uint16_t *channels,SBUS_FRAME * frame)
{
    uint8_t *buf = frame->sbus_frame_data;
    uint32_t bitbuf = 0;
    uint8_t bitcount = 0;
    uint16_t byteindex = 1;
    buf[0] = 0x0F;
    for (int i = 1; i < 25; i++)
        buf[i] = 0;
    for (int i = 0; i < SBUS_CHANNELS; i++)
    {
        uint16_t val = sbus_map(channels[i]);
        bitbuf |= (val << bitcount);
        bitcount += 11;
        while (bitcount >= 8)
        {
            buf[byteindex++] = (uint8_t)(bitbuf & 0xFF);
            bitbuf >>= 8;
            bitcount -= 8;
        }
    }

    buf[23] = 0x00;
    buf[24] = 0x00;
}


void sbus_send(SBUS_FRAME *Frame)
{
    HAL_UART_Transmit(&huart2,Frame->sbus_frame_data,SBUS_FRAME_LEN,10);
}