# UART 通信说明

## 模块作用
负责 TX —— RX 之间的数据传输。


## 通信参数
- 波特率：115200
- 数据位：8
- 校验位：None
- 停止位：1
---

## 传输数据结构

```c

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

```

## TX 发送
-  HAL_UART_Transmit(&huart1, (uint8_t *)&tx, sizeof(Frame), 10);

## RX 接收
-  HAL_UART_Receive_IT(&huart1, rx_buf, sizeof(Frame));


## 通信效率提升
- 已添加初等CRC校验
- 已通过pragma使结构体对齐
- 已使用初等数据帧协议


