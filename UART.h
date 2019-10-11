// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

#ifndef __UART_H__
#define __UART_H__

// Baud rate for USART->BRR register
#define USART9600           0xEA6       // 9600 bit per second

void USART2_IRQHandler(void);

void InitUART(void);
void TransmitUART(uint8_t* buf, int num);
void ReceiveUART(uint8_t* buf, int num);
bool UARTtransmitted(void);
bool UARTreceived(void);

#endif