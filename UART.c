// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

//user
#include "UART.h"

// Local variables
// Data
static uint8_t* transmit_buf;
static uint8_t* receive_buf;
// Number of data
static int to_transmit = 0;
static int to_receive = 0;
// Flags
static volatile bool transmitted = true;
static volatile bool received = true;

// Interrupt
void USART2_IRQHandler(void)
{
    // Transmit data register empty
    if ( (USART2->SR & USART_SR_TXE) != 0 ) {
        if (to_transmit != 0) {
            USART2->DR = transmit_buf[0];
            transmit_buf++;
            to_transmit--;
        }
        else
            USART2->CR1 &= ~USART_CR1_TXEIE;    // Transmit data register empty interrupt disable
    }
    // Transmission complete
    if ((USART2->SR & USART_SR_TC) != 0) {
        transmitted = true;
        USART2->CR1 &= ~USART_SR_TC;    // Transmission complete interrupt disable
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
    USART2->CR1 |=  USART_CR1_TXEIE * 0 |   // Transmit data register empty interrupt enable
                    USART_CR1_TCIE  * 0 |   // Transmission complete interrupt enable
                    USART_CR1_RXNEIE * 0;   // Received data register not empty interrupt enable
}
void TransmitUART(uint8_t* buf, int num)
{
    transmit_buf = buf;
    to_transmit = num - 1;
    transmitted = false;
    
    USART2->CR1 |= USART_CR1_TXEIE;    // Transmit data register empty interrupt enable
    USART2->CR1 |= USART_CR1_TCIE;      // Transmission complete interrupt enable
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
