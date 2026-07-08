/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "remote.h"
#include <string.h>
#include "protocol.h"
#include "sbus.h"
#include "RFsx1276.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
Channels_t ch;
Frame rx;
uint8_t dma_rx_buf[32];
SBUS_FRAME sbus;
uint8_t rx_ready = 0;
uint32_t last_time = 0;
typedef enum{
    STATE_INIT = 0,
    STATE_NORMAL,
    STATE_FAILSAFE
}SystemState;
SystemState current_state = STATE_INIT;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void apply_failsafe(void);
void debug_frame(FrameStatus st);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void uart_send_string(const char *str)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str), HAL_MAX_DELAY); 
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  RF_Sx1276_Init();
  HAL_TIM_Base_Start_IT(&htim2);
//   HAL_UARTEx_ReceiveToIdle_DMA(&huart1, dma_rx_buf, sizeof(dma_rx_buf));
  SX1276StartRx();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      uint32_t result=SX1276Process();
      if (result == RF_RX_DONE)
    {
      uint16_t size;
      SX1276GetRxPacket(dma_rx_buf, &size);
      if (frame_parser(dma_rx_buf, size, &rx))
      {
          FrameStatus fs = frame_check(&rx);
          if(fs==FRAME_OK)
        {
          frame_getchannels(&rx, &ch);
          last_time = HAL_GetTick();
          current_state = STATE_NORMAL;
        }
        else
        {
            debug_frame(fs);
        }
      }
    }
      if (HAL_GetTick() - last_time > 500)
      {
          current_state = STATE_FAILSAFE;
          apply_failsafe();
      }
      else if (current_state == STATE_FAILSAFE)
      {
          current_state = STATE_NORMAL;
      }
      // if(rx_ready)
      // {

      // }
      /* USER CODE END WHILE */

      /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */


 void debug_frame(FrameStatus st)
 {
     switch (st)
    {
    case FRAME_HEAD_ERR:
            uart_send_string("HEAD ERROR!\r\n");
            break;

    case FRAME_LEN_ERR:
            uart_send_string("LEN ERRPR!\r\n");
            break;

    case FRAME_CRC_ERR:
            uart_send_string("CRC ERROR!\r\n");
            break;
    case FRAME_TYPE_ERR:
            uart_send_string("TYPE ERROR!\r\n");
            break;
     default:
             break;
    }
 } 
// void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size)
// {   
//     if (huart->Instance == USART1)
//     {
//         FrameStatus fs;
//         // if (size == sizeof(Frame))
//         //
//         if (frame_parser(dma_rx_buf, size, &rx))
//         {
//             fs=frame_check(&rx);
//             // memcpy(&rx, dma_rx_buf, sizeof(Frame));
//             if (fs != FRAME_OK)
//             {
//                 // debug_frame(fs);
                
//             }
//             else
//             {   
//                 rx_ready=1;
//                 frame_getchannels(&rx,&ch);
//                 HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
//             }
          
//         } 
//         HAL_UARTEx_ReceiveToIdle_DMA(&huart1, dma_rx_buf, sizeof(dma_rx_buf));
//     }
// }

// void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
// {
//     if (huart->Instance == USART1)
//     {
//         HAL_UARTEx_ReceiveToIdle_DMA(&huart1, dma_rx_buf, sizeof(dma_rx_buf));
//     }
// }

void apply_failsafe(void)
{
    ch.roll = 0;
    ch.pitch = 0;
    ch.yaw = 0;
    ch.throttle = 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        sbus_encoder((int16_t *)&ch, &sbus);
        sbus_send(&sbus);
    }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
