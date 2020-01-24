/*
    1. Configure pins as alternate function push-pull
    2. Define and configure SPI_NSS_PIN as push-pull (switching by software)
    3. Init RCC: RCC->APB2ENR |= RCC_APB2ENR_SPIxEN;
    4. Enable interrupt
    5. Call function InitSpi
*/

// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

#ifndef __SPI_H__
#define __SPI_H__

void InitSpi(void);
void TransmitSpi(uint8_t* buf, int num);
void ReceiveSpi(uint8_t* buf, int num);
bool TransmittedSpi(void);
bool ReceivedSpi(void);
void SelectChipSpi(void);
void DeselectChipSpi(void);

#endif
