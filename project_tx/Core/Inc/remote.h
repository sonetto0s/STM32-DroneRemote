#ifndef __REMOTE_H
#define __REMOTE_H

#include "main.h"

#pragma pack(push, 1)

typedef struct
{
    int16_t lx;
    int16_t ly;
    int16_t rx;
    int16_t ry;
    int16_t filter_buf[4];
} Remote;



typedef struct{

    int16_t roll;
    int16_t pitch;
    int16_t yaw;
    int16_t throttle;

}Channels;

typedef struct
{
	  uint8_t head1;
    uint8_t head2;
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
    int16_t throttle;
    uint8_t crc;

} Frame;

#pragma pack(pop)
extern Remote rem;
extern Channels ch;

void remote_init(void);
void remote_update(void);
int throttle_map(int raw);
int crcme(uint8_t *data, uint16_t len);

#endif
