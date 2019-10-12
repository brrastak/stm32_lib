/*
    1. Configure pins as alternate function push-pull
    2. Init RCC: RCC->APB1ENR |= RCC_APB1ENR_USART_EN;
    3. Enable interrupt
    4. Call function InitUART
*/

// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

//user
#include "UART.h"

// Local variables
// Data
uint8_t* transmit_buf;
uint8_t* receive_buf;
// Number of data
int to_transmit = 0;
int to_receive = 0;
// Flags
bool transmitted = true;
bool received = true;

// Interrupt
void USART2_IRQHandler(void)
{
    // Transmit data register empty
    if ( ((USART2->SR & USART_SR_TXE) != 0) && (to_transmit != 0) ) {
        USART2->DR = transmit_buf[0];
        transmit_buf++;
        to_transmit--;
    }
    // Transmission complete
    if ((USART2->SR & USART_SR_TC) != 0) {
        transmitted = true;
    }
    // Received data register not empty
    if ((USART2->SR & USART_CR1_RXNEIE) != 0) {
    }
}

void InitUART(void)
{
    USART2->CR1 |= USART_CR1_UE;    // USART enable
    USART2->BRR = USART9600;        // set baud rate
    USART2->CR1 |= USART_CR1_TE;    // transmitter enable
    // Interrupts
    USART2->CR1 |=  USART_CR1_TXEIE * 1 |   // Transmit data register empty interrupt enable
                    USART_CR1_TCIE  * 1 |   // Transmission complete interrupt enable
                    USART_CR1_RXNEIE * 0;   // Received data register not empty interrupt enable
}
void TransmitUART(uint8_t* buf, int num)
{
    transmit_buf = buf;
    to_transmit = num - 1;
    transmitted = false;
    USART2->DR = transmit_buf[0];
    transmit_buf++;
}
void ReceiveUART(uint8_t* buf, int num)
{
    receive_buf = buf;
    to_receive = num;
    received = false;
}
bool UARTtransmitted(void)
{
    return transmitted;
}
bool UARTreceived(void)
{
    return received;
}
