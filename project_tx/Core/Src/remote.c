#include "remote.h"
#include "adc.h"

// extern  volatile uint16_t adc_buf[4];

extern uint32_t last_time;
Channels_t ch;
Remote rem;
void remote_init(void)
{
        rem.lx = rem.ly = 0;
        rem.rx = rem.ry = 0;
        for (int i = 0; i < 4; i++)
        {
            rem.filter_buf[i] = 0;
        }
}

int  improvenum(uint16_t raw)
{
   
    int deadnum = (int)raw - ADC_MID_VALUE;
    if (deadnum > -DEAD_NUM &&deadnum < DEAD_NUM)
    {
        deadnum = 0;
    }
    return (deadnum * CONTROLER_MAX) / ADC_MID_VALUE;
}

void remote_update(uint16_t *raw_adc_buf)
{
    int raw_value[4] = {improvenum(raw_adc_buf[0]), improvenum(raw_adc_buf[1]), improvenum(raw_adc_buf[2]), improvenum(raw_adc_buf[3])};

    for (int i = 0; i < 4; i++)
    {
        rem.filter_buf[i] = (rem.filter_buf[i] * 3 + raw_value[i]) / 4;
    }
    rem.lx = rem.filter_buf[0];
    rem.ly = rem.filter_buf[1];
    rem.rx = rem.filter_buf[2];
    rem.ry = rem.filter_buf[3];

    ch.roll = rem.lx;
    ch.pitch = rem.ly;
    ch.yaw = rem.rx;
    ch.throttle = throttle_map(rem.ry);
  
}


int throttle_map(int raw)
{
    if (raw < 0)
           raw = 0;
    if (raw > THROTTLE_MAX_RAW)
        raw = THROTTLE_MAX_RAW;
        return (raw * THROTTLE_OUTPUT_MAX) / THROTTLE_MAX_RAW;
}







