#ifndef __REMOTE_H
#define __REMOTE_H

#include "main.h"

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

extern Remote rem;
extern Channels ch;

void remote_init(void);
void remote_update(void);
int throttle_map(int raw);

#endif
