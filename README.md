# STM32 Drone Remote 

hello hello啊   :)

##  项目简介

this is一个基于 STM32F103C8T6 的简易无人机遥控系统，用来实现摇杆数据采集、无线通信以及 SBUS 输出等等功能.

##  当前版本：V0.2.1


##  更新日志

### V0.2.1
- 新增CRC校验,结合串口发送实现数据正确捕捉
- 新增定时器控制频率输出时序，移除主循环阻塞延时，优化时序逻辑
- 优化数据结构与系统工程设计，为后续协议升级做准备

### v0.2
- 构建 TX / RX 双工程结构
- 完成 UART 双机通信验证


### v0.1.2
- ADC + DMA 四通道连续采样
- 串口打印调试验证数据正确性

### v0.1
- 工程初始化完成 
- 搭建 STM32HAL基础工程


##  已实现功能

###  TX（遥控端）

- ADC 四通道采集
- DMA 连续搬运数据
- 基础滤波 + 死区 处理
- UART 数据发送

###  RX（接收端）

- UART 数据接收
- 数据解析恢复通道值
- 串口输出调试验证

##  开发环境

- STM32CubeMX
- Keil MDK V5.32
- Visual Stidio Code

##  硬件

- STM32F103C8T6 ×2
- XL1278 LoRa ×2）
- 双摇杆模块 ×2
- RP1 ELRS 接收机 ×1


## 工程结构

```
├─project_rx
│  ├─.vscode
│  ├─Core
│  │  ├─Inc
│  │  └─Src
│  ├─Drivers
│  │  ├─CMSIS
│  │  │  ├─Device
│  │  │  │  └─ST
│  │  │  │      └─STM32F1xx
│  │  │  │          ├─Include
│  │  │  │          └─Source
│  │  │  │              └─Templates
│  │  │  └─Include
│  │  └─STM32F1xx_HAL_Driver
│  │      ├─Inc
│  │      │  └─Legacy
│  │      └─Src
│  └─MDK-ARM
│      ├─DebugConfig
│      ├─project-tx
│      ├─project_rx
│      └─RTE
│          ├─_project-tx
│          └─_project_rx
└─project_tx
    ├─.vscode
    ├─Core
    │  ├─Inc
    │  └─Src
    ├─Docs
    ├─Drivers
    │  ├─CMSIS
    │  │  ├─Device
    │  │  │  └─ST
    │  │  │      └─STM32F1xx
    │  │  │          ├─Include
    │  │  │          └─Source
    │  │  │              └─Templates
    │  │  └─Include
    │  └─STM32F1xx_HAL_Driver
    │      ├─Inc
    │      │  └─Legacy
    │      └─Src
    └─MDK-ARM
        ├─DebugConfig
        ├─project_rx
        ├─project_tx
        └─RTE
            ├─_project_rx
            └─_project_tx
```
## 结合进度以及工作时间，本项目大概于7月中旬完成