/*
    1. Define and configure PARALLEL_PORT
    2. Init RCC: RCC->AHBENR |= RCC_AHBENR_DMA1EN;
    3. Enable DMAx_Channely interrupt
    4. Call function InitDMA();
*/

// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

#ifndef __DMA_H__
#define __DMA_H__


void InitDma(void);
// From buf to PARALLEL_PORT
void TransmitDma(uint16_t * buf, uint16_t buf_size, uint32_t num);
void DisableDma(void);

bool TransmittedDma(void);


#endif