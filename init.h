// STM32F103
#include "stm32f10x.h"

#ifndef __INIT_H__
#define __INIT_H__

// Clock source select;
// Peripheral clock enable
void InitRCC(void);

// Init interrupts
void InitInterrupt(void);

// Init GPIO
void InitGPIO(void);

#endif