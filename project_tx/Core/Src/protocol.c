#include "protocol.h"

uint16_t protocol_crc(uint8_t *data,uint16_t len)
{
    uint16_t crc = 0xFFFF;
    for (int i = 0; i < len; i++)
    {
        crc ^= data[i];
        for (int j = 0; j < 8; j++)
        {
            if(crc & 0x0001)
            {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc;
}

void frame_init(Frame *frame)
{
    frame->head1 = FRAME_HEADER_1;
    frame->head2 = FRAME_HEADER_2;
    frame->length = sizeof(Channels_t);
    frame->type = FRAME_TYPE_CHANNEL;
    memset(&(frame->ch), 0, sizeof(Channels_t));
    frame->crc = 0;
}

void frame_setchannels(Frame *frame,const Channels_t *ch)
{
    memcpy(&(frame->ch), ch, sizeof(Channels_t));
}

void frame_update_crc(Frame *frame)
{
    frame->crc = protocol_crc((uint8_t *)frame, sizeof(Frame) - 2);
}

