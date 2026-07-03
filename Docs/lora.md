# LoRa(XL1276)驱动模块说明


##  项目说明

本项目基于 STM32F103 系列单片机，集成(XL1278)LoRa无线通信模块,以搭建一个稳定无线通信驱动


##  硬件设备

- MCU：STM32F103C8T6
- LoRa模块：XL1278(SPI)
- 电压:3.3V



##  软件架构

###  软件层结构

- STM32 HAL库(CubeMX生成)
- LoRa驱动(RFsx1276.c)
- SPI通信（HAL_SPI）
- GPIO控制（HAL_GPIO）




### 已移植内容
- 原有标准库函数GPIO_WriteBit → HAL_GPIO_WritePin 
- 原有标准库函数GPIO_ReadInputDataBit → HAL_GPIO_ReadPin 
- 原有SysTick寄存器延时 → HAL_Delay 
- SPI标准库底层驱动 → HAL_SPI_TransmitReceive 



##  硬件控制信号说明

###  NSS

作用: 检测LoRa模块选中状态

- 低电平   开始通信     HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_RESET);
- 高电平   结束通信     HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_SET);   


### RESET 

作用:检测是否复位
- 低电平  复位状态
- 高电平  正常运行

### DIO引脚

作用: 传递通知LoRa模块状态
- DIO0    发送/接收完成
- DIO1-DIO5    扩展功能