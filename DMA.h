/*
    2. Init RCC: RCC->AHBENR |= RCC_AHBENR_DMA1EN;
    4. Call function InitDMA

*/

// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

#ifndef __DMA_H__
#define __DMA_H__

extern uint32_t one[10];
extern uint32_t two[10];

void InitDma(uint32_t mem, uint32_t periph);


#endif