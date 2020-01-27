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
#define USART57600          0x271       // 57600 bit per second
#define USART115200         0x138       // 115200 bit per second

void USART2_IRQHandler(void);

void InitUart(void);
void TransmitUart(uint8_t* buf, int num);
void ReceiveUart(uint8_t* buf, int num);
bool TransmittedUart(void);
bool ReceivedUart(void);

#endif
