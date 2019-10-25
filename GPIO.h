// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

#ifndef __GPIO_H__
#define __GPIO_H__

// Pin modes
#define PIN_MODE_IANALOG        0x00    // in analog
#define PIN_MODE_2MHZ_OPP       0x02    // out push-pull; speed 2 MHz
#define PIN_MODE_IFLOAT         0x04    // in floating
#define PIN_MODE_2MHZ_AFPP      0x0a    // alternate function push-pull; speed 2 MHz
#define PIN_MODE_2MHZ_AFOD      0x0e    // alternate function open-drain; speed 2 MHz

// GPIO
void GPIOMode(GPIO_TypeDef* port, int pin, int mode);
bool PinState(GPIO_TypeDef* port, int pin);
void PinSet(GPIO_TypeDef* port, int pin);
void PinReset(GPIO_TypeDef* port, int pin);
void PinSwitch(GPIO_TypeDef* port, int pin);
void MulPinSet(GPIO_TypeDef* port, int mask);
void MulPinReset(GPIO_TypeDef* port, int mask);


#endif