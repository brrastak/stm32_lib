// STM32F103
#include "stm32f10x.h"

#ifndef __I2C_H__
#define __I2C_H__

void InitI2C(void);
void I2CWrite(uint8_t addr, uint8_t data, int num);

void I2C2_EV_IRQHandler(void);

#endif