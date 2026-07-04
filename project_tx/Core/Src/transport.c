#include "transport.h"
#include "usart.h"

static volatile int tx_busy = 0;

int transport_send(uint8_t *data, uint16_t len)
{   
    if(tx_busy)
        return 0;
    tx_busy = 1;
    if (HAL_UART_Transmit_DMA(&huart1, data, len) != HAL_OK)
    {
        tx_busy = 0;
        return 0;
    }
    return 1;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        tx_busy = 0;
    }
}
