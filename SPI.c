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
#include "SPI.h"
#include "main.h"

// Local variables
// Data
uint8_t* transmit_buf;
uint8_t* receive_buf;
// Number of data
int to_transmit = 0;
int to_receive = 0;
// Flags
volatile bool transmitted = true;
volatile bool received = true;

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
        USART2->CR1 &= ~USART_CR1_TXEIE;    // Transmit data register empty interrupt disable
    }
    // Received data register not empty
    if ((USART2->SR & USART_CR1_RXNEIE) != 0) {
    }
}

void InitSPI(void)
{
    // Configuring SPI1 in master mode
    SPI1->CR1 =     SPI_CR1_BR_0        * 1 |   // baud rate = f_PCLK / 256
                    SPI_CR1_BR_1        * 1 |
                    SPI_CR1_BR_2        * 1;
    SPI1->CR1 |=    SPI_CR1_CPOL        * 0 |   // clock polarity = 0
                    SPI_CR1_CPHA        * 0 |   // clock phase = 0
                    SPI_CR1_DFF         * 1 |   // 16-bit data frame format
                    SPI_CR1_LSBFIRST    * 0 |   // MSB transmitted first
                    SPI_CR1_MSTR        * 1 |   // master mode
                    SPI_CR1_SSM         * 1 |   // software NSS
                    SPI_CR1_SSI         * 1;    // software NSS up
    //SPI1->CR2 =     SPI_CR2_SSOE        * 1;    // SS output enable
    SPI1->CR1 |=    SPI_CR1_SPE;    // SPI enable
}
void TransmitSPI(uint8_t* buf, int num)
{
    transmit_buf = buf;
    to_transmit = num - 1;
    transmitted = false;
    
    USART2->DR = transmit_buf[0];
    USART2->CR1 |=  USART_CR1_TXEIE;    // Transmit data register empty interrupt enable
    
    transmit_buf++;
}
void ReceiveSPI(uint8_t* buf, int num)
{
    receive_buf = buf;
    to_receive = num;
    received = false;
}
bool SPItransmitted(void)
{
    return transmitted;
}
bool SPIreceived(void)
{
    return received;
}
void ChipSelectSPI(void)
{
}
void ChipDeselectSPI(void)
{
}