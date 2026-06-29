//#include "remote.h"

//Channels ch;
//Remote rem;
//void remote_init(void)
//{
//        rem.lx = rem.ly = 0;
//        rem.rx = rem.ry = 0;
//        for (int i = 0; i < 4; i++)
//        {
//            rem.filter_buf[i] = 0;
//        }
//}

//int  improvenum(uint16_t raw)
//{
//   
//    int deadnum = (int)raw - 2048;
//    if (deadnum > -50 &&deadnum < 50)
//    {
//        deadnum = 0;
//    }
//    return (deadnum * 700) / 2048;
//}

//void remote_update(void)
//{
//    int raw_value[4] = {improvenum(adc_buf[0]), improvenum(adc_buf[1]), improvenum(adc_buf[2]), improvenum(adc_buf[3])};

//    for (int i = 0; i < 4; i++)
//    {
//        rem.filter_buf[i] = (rem.filter_buf[i] * 3 + raw_value[i]) / 4;
//    }
//    rem.lx = rem.filter_buf[0];
//    rem.ly = rem.filter_buf[1];
//    rem.rx = rem.filter_buf[2];
//    rem.ry = rem.filter_buf[3];

//    ch.roll = rem.lx;
//    ch.pitch = rem.ly;
//    ch.yaw = rem.rx;
//    ch.throttle = throttle_map(rem.ry);

//}


//int throttle_map(int raw)
//{
//    if (raw < 0)
//           raw = 0;
//    if (raw > 700)
//        raw = 700;
//        return (raw * 1000) / 700;
//}




