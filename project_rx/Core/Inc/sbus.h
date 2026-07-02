#ifndef __SBUS_H
#define __SBUS_H

#include "main.h"
#include "remote.h"
#include "usart.h"
#define SBUS_FRAME_LEN 25
#define SBUS_CHANNELS 16
typedef struct
{

    uint8_t sbus_frame_data[SBUS_FRAME_LEN];

} SBUS_FRAME;


static uint16_t sbus_map(int16_t value);
void sbus_encoder(uint16_t *ch, SBUS_FRAME *frame);
void sbus_send(SBUS_FRAME *Frame);
extern UART_HandleTypeDef huart1;
#endif

