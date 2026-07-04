#ifndef __REMOTE_H
#define __REMOTE_H

#include "main.h"
#include "data_types.h"


typedef struct
{
    int16_t lx;
    int16_t ly;
    int16_t rx;
    int16_t ry;
    int16_t filter_buf[4];
} Remote;


#define ADC_MID_VALUE 2048
#define DEAD_NUM 50
#define CONTROLER_MAX 1000
#define THROTTLE_MAX_RAW 700
#define THROTTLE_OUTPUT_MAX 1000

#define FAILSAFE_TIMEOUT_MS 500

// typedef struct{

//     int16_t roll;
//     int16_t pitch;
//     int16_t yaw;
//     int16_t throttle;

// }Channels;

// typedef struct
// {
// 	uint8_t head1;
//     uint8_t head2;
//     uint8_t length;
// 	uint8_t type;
// 	Channels_t ch;
//     uint16_t crc;

// } Frame;


extern Remote rem;
extern Channels_t ch;

void remote_init(void);
void remote_update(uint16_t *raw_adc_buf);
int throttle_map(int raw);


#endif
