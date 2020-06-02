// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

//user
#include "SPI.h"
#include "main.h"
#include "GPIO.h"

// Local variables
// Data
static uint16_t* transmit_buf;
static uint16_t* receive_buf;
// Number of data
static int to_transmit = 0;
static int to_receive = 0;

// Interrupt
void SPI1_IRQHandler(void)
{
    // Transmit data register empty
    if ( (SPI1->SR & SPI_SR_TXE) != 0 ) {
        if (to_transmit != 0) {
            SPI1->DR = transmit_buf[0];
            transmit_buf++;
            to_transmit--;
        }
        else
            SPI1->CR2 &= ~SPI_CR2_TXEIE;    // TX buffer empty interrupt disable
    }
    // Received data register not empty
    if ((SPI1->SR & SPI_SR_RXNE) != 0) {
        if (to_receive != 0) {
            receive_buf[0] = SPI1->DR;
            receive_buf++;
            to_receive--;
        }
        else {
            (void)SPI1->DR;     // clear interrupt flag
        }
    }
}

void InitSpi(void)
{
    // Configuring SPI1 in master mode
    SPI1->CR1 =     SPI_CR1_BR_0        * 1 |   // baud rate = f_PCLK / (2 * 2^BR)
                    SPI_CR1_BR_1        * 0 |
                    SPI_CR1_BR_2        * 0;
    SPI1->CR1 |=    SPI_CR1_CPOL        * 0 |   // clock polarity = 0
                    SPI_CR1_CPHA        * 0 |   // clock phase = 0
                    SPI_CR1_DFF         * 1 |   // 16-bit data frame format
                    SPI_CR1_LSBFIRST    * 0 |   // MSB transmitted first
                    SPI_CR1_MSTR        * 1 |   // master mode
                    SPI_CR1_SSM         * 1 |   // software NSS enable
                    SPI_CR1_SSI         * 1;    // software NSS up
    SPI1->CR2 =     SPI_CR2_SSOE        * 1;    // SS output enable
    
    SPI1->CR1 |=    SPI_CR1_SPE;        // SPI enable
    SPI1->CR2 |=    SPI_CR2_RXNEIE;     // RX buffer not empty interrupt enable
    
    DeselectChipSpi();
}
void TransmitSpi(uint16_t* buf, int num)
{
    transmit_buf = buf;
    to_transmit = num - 1;
    
    SelectChipSpi();
    
    SPI1->DR = transmit_buf[0];
    transmit_buf++;
    
    SPI1->CR2 |= SPI_CR2_TXEIE;     // TX buffer empty interrupt enable
}
void ReceiveSpi(uint16_t* buf, int num)
{
    receive_buf = buf;
    to_receive = num;
}
bool TransmittedSpi(void)
{
    return ((SPI1->SR & SPI_SR_BSY) == 0);
}
bool ReceivedSpi(void)
{
    return ((SPI1->SR & SPI_SR_BSY) == 0);
}
void SelectChipSpi(void)
{
    ResetPin(SPI_NSS_PIN);
}
void DeselectChipSpi(void)
{
    SetPin(SPI_NSS_PIN);
}
