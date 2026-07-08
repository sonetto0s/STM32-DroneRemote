# STM32 Drone Remote 

hello hello啊   👋

##  项目简介

this is一个基于 STM32F103C8T6 的简易无人机遥控系统，用来实现摇杆数据采集、无线通信以及 SBUS 输出等等功能.

##  当前版本：V0.7.1


##  更新日志

### V0.7.1
- 测试LoRa模块通讯

### V0.7
- 引入LoRa模块并移植入rx端,基本取代UART通讯
- 测试SPI通信完毕
- 逐步开始PCB设计

### V0.6.1
- 进一步优化目录结构,修改删减不合理实现代码

### V0.6
- 调整硬件层与协议层结构,调整代码实现逻辑
- 增加FailSafe保护,规划工程能力实现
- 增加状态机实现,优化程序

### V0.5 
- 初步移植LoRa驱动至tx端，逐步取代有线连接
- 测试SPI 通信机制

### V0.4
- 新增SBUS协议,引入多串口收发调整RX端功能
- 通过USART2将解析数据发送
- 优化项目结构,暂推迟lora实现

### V0.3.2 
- 新增数据帧解析函数，通过扫描算法保证整帧高效准确传递
- 新增debug 调试打印错误函数
- 剔除无用代码，优化项目结构

### V0.3.1
- 调整目录结构

### V0.3
- 优化CRC校验，改为标准CRC-16校验
- 完成Frame数据结构设计

### V0.2.1
- 新增初等CRC校验,结合串口发送实现数据正确捕捉
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

- ADC 四通道采集(摇杆输入)
- DMA 连续搬运数据
- 基础滤波 + 死区 处理
- 自定义协议帧封装
- UART 数据发送

###  RX（接收端）

- UART DMA数据接收
- 基于字节流的帧解析
- CRC校验帧与结构校验
- 数据解析提取并恢复通道值
- GPIO输出调试验证
- 通过SBUS协议与USART2将收到数据进行装包发送

##  开发环境

- STM32CubeMX
- Keil MDK V5.32
- Visual Stidio Code

##  硬件

- STM32F103C8T6 ×2
- XL1278 LoRa ×2）
- 双摇杆模块 ×2
- RP1 ELRS 接收机 ×1

## Docs 目录

- Docs/adc_dma.md
- Docs/data_flow.md
- Docs/debug_log.md
- Docs/hardware.md
- Docs/protocol.md
- Docs/uart_com.md
- Docs/sbus.md
- Docs/lora.md

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

## 工程进度
```
 ADC + DMA           OK
  |  
 Channel             OK
  |  
 Frame Protocol      OK
  |              
 SBUS                OK
  |   
 LoRa                   
  |             <- THIS IS CURRENT STAGE  
 飞控
  |   
 fly~
```
## 结合进度以及工作时间，本项目大概于7月中旬完成,不会追求过快完成,主要是要学习这种工程思维and项目设计啥的，毕竟是我第一个正式的项目(stm32),哈          


## 欢迎交流，也欢迎提出建议啊,我不打游戏，平时就经常坐电脑桌前敲代码，你发消息给我我肯定能及时回复你的       :)

