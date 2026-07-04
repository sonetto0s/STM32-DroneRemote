#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include "main.h"
#include <stdint.h>
#include "data_types.h"
#include <stdio.h>
#include <string.h>

#define FRAME_HEADER_1  0xAA
#define FRAME_HEADER_2  0x55

#define FRAME_TYPE_CHANNEL 0x01

// #define FRAME_HEADER_SIZE 2
// #define FRAME_LENGTH_SIZE 1
// #define FRAME_TYPE_SIZE   1
// #define FRAME_CRC_SIZE    2

#pragma pack(push, 1)
typedef struct
{
    uint8_t head1;
    uint8_t head2;
    uint8_t length;
    uint8_t type;
    Channels_t ch;
    uint16_t crc;

} Frame;
#pragma pack(pop)

uint16_t protocol_crc(uint8_t *data, uint16_t len);
void frame_init(Frame *frame);
void frame_setchannels(Frame *frame,const Channels_t *ch);
void frame_update_crc(Frame *frame);

#endif

