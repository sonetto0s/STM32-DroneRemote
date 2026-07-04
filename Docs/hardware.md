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
TX -STM32      
|
LoRa      
|
RX -STM32      

当前使用 LoRa 模块进行协议验证，
```


## 飞控
- SBUS Interface
- UART
- 100000 波特率

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