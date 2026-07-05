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

void frame_getchannels(Frame *frame,Channels_t *ch)
{
    memcpy(ch,&(frame->ch),sizeof(Channels_t));
}

void frame_update_crc (Frame *frame)
{
    frame->crc = protocol_crc((uint8_t *)frame, sizeof(Frame) - 2);
}

uint8_t frame_check(const Frame *frame)
{
    if (frame->head1 != FRAME_HEADER_1)
        return FRAME_HEAD_ERR;
    if (frame->head2 != FRAME_HEADER_2)
        return FRAME_HEAD_ERR;
    if (frame->length != sizeof(Channels_t))
        return FRAME_LEN_ERR;
    if (frame->type != FRAME_TYPE_CHANNEL)
        return FRAME_TYPE_ERR;
    uint16_t crc = protocol_crc((uint8_t *)frame, sizeof(Frame) - 2);
    if (crc != frame->crc)
    {
        return FRAME_CRC_ERR;
    }
    return FRAME_OK;
}


int frame_parser(uint8_t * buf,uint16_t len,Frame *fr)
{
    if (len < sizeof(Frame))
        return 0;
    for (int i = 0; i <= len - sizeof(Frame); i++)
    {
            if (buf[i] == FRAME_HEADER_1 && buf[i + 1] == FRAME_HEADER_2)
            {
                memcpy(fr, &buf[i], sizeof(Frame));
                return 1;
              
            }
    }
    return 0;
}

