/*
    1. Configure pins as alternate function push-pull
    2. Init RCC: RCC->APB1ENR |= RCC_APB1ENR_USARTxEN;
    3. Enable interrupt
    4. Call function InitUART
    
    BRR for UART1 = (BRR for UART2 & UART3)  * 2
*/

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
