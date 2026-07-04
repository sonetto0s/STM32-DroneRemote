#  协议说明

##  通信流程

```
操作杆
|
ADC_DMA
|
Channels
|
Frame
|
LoRa
|
Frame Parser
|
Channels
|
SBUS

```


##  框架格式
- header1      1 byte   0xAA
- header2      1 byte   0x55
- length       1 byte   payload长度
- type         1 byte   数据类型
- payload      n byte   数据内容
- CRC16        2 byte   数据校验


