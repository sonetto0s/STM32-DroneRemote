# Hardware

## 项目硬件连接说明

## MCU
- STM32F103C8T6 ×2
- 一块作为 TX,一块作为 RX


## 操作杆
- roll        PA0
- pitch       PA1
- yaw         PA2
- throttle    PA3

## UART
```
TX -STM32      PA9
|
USART1      
|
RX -STM32      PA10

当前使用 UART 进行协议验证，后续将替换为LoRa
```


## 飞控
- SBUS Interface
- UART
- 115200 波特率

## 电源供应
- USB 5V
- 后续可能修改优化供应

## 硬件传递实现

```
操作杆
|
STM32(TX)
|
LoRa
|
STM32(RX)
|
SBUS
|
飞控
```