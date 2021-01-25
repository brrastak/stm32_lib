/*
    1. Configure pins as alternate function open drain
    2. Init RCC: RCC->APB1ENR |= RCC_APB1ENR_I2CxEN;
    3. Enable interrupt: NVIC_EnableIRQ(I2Cx_EV_IRQn);
    4. Call function InitI2c();
*/

// STM32F103
#include "stm32f10x.h"

#ifndef __I2C_H__
#define __I2C_H__


void InitI2c(void);

void TransmitI2c(uint8_t i2c_addr, uint8_t* buf, int num);

bool TransmittedI2c(void);
bool ReceivedI2c(void);

void WaitForTransmitI2c(void);
void WaitForReceiveI2c(void);



#endif