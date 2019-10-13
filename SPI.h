// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

#ifndef __SPI_H__
#define __SPI_H__

void USART2_IRQHandler(void);

void InitSPI(void);
void TransmitSPI(uint8_t* buf, int num);
void ReceiveSPI(uint8_t* buf, int num);
bool SPItransmitted(void);
bool SPIreceived(void);
void ChipSelectSPI(void);
void ChipDeselectSPI(void);

#endif