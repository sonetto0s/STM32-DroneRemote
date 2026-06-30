#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include "main.h"
#include <stdint.h>
#include "remote.h"

#define FRAME_HEADER_1  0xAA
#define FRAME_HEADER_2  0x55

#define FRAME_TYPE_CHANNEL 0x01

#define FRAME_HEADER_SIZE 2
#define FRAME_LENGTH_SIZE 1
#define FRAME_TYPE_SIZE   1
#define FRAME_CRC_SIZE    2
uint16_t protocol_crc(uint8_t *data, uint16_t len);
void frame_init(Frame *frame);
void frame_setchannels(Frame *frame, const Channels *ch);
void frame_update_crc(Frame *frame);
#endif

