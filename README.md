# STM32 Drone Remote
hello hello啊   :)

## 项目简介

    一个基于 stm32f103c8t6的简易飞控遥控器，实现摇杆数据采集、无线通信以及 SBUS 输出等等功能.

## 当前版本：V0.2

## 更新日志
```
    6.30 :构建TX/RX双端工程结构
           and完成 UART 双机通信验证
    6.29 : ADC + DMA 四路连续采样
           串口打印调试
    6.28 :  OK，这个项目它出生了
            初始化工程
```

## 已实现功能

```
###  遥控端（TX）

    ADC四通道采集并转化(roll,pitch,yaw,throttle)
    DMA连续采样
    滤波处理
    UART数据发送

###  接收端（RX）

    UART数据接收
    遥控通道恢复
    串口数据输出验证

```

## 编译环境
```
    STM32CubeMX
    Keil MDK V5
    STM32 HAL Library
```

## 硬件设备
```
    STM32F103C8T6 ×2
    XL1278 LoRa模块 ×2
    摇杆模块×2
    RadioMaster RP1 ELRS 接收机 x1
```
## 项目结构
```

├─project-tx
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
│      └─RTE
│          └─_project-tx
└─project_rx
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
        └─RTE
            └─_project_rx
```