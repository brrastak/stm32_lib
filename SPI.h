/*
    1. Configure pins as alternate function push-pull (NSS only software)
    2. Init RCC: RCC->APB2ENR |= RCC_APB2ENR_SPIxEN;
    3. Enable interrupt
    4. Call function InitSPI
*/

// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

#ifndef __SPI_H__
#define __SPI_H__

void SPI1_IRQHandler(void);

void InitSPI(void);
void TransmitSPI(uint16_t* buf, int num);
void ReceiveSPI(uint16_t* buf, int num);
bool SPItransmitted(void);
bool SPIreceived(void);
void ChipSelectSPI(void);
void ChipDeselectSPI(void);

#endif
