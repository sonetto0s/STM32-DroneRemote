#ifndef __REMOTE_H
#define __REMOTE_H

#include "main.h"
#include "string.h"

#pragma pack(push, 1)
typedef struct{
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
    int16_t throttle;
}Channels_t;


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


#endif
