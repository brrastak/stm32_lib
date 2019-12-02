// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

#ifndef __GPIO_H__
#define __GPIO_H__

// Pin modes
#define PIN_MODE_IANALOG        0x00    // in analog
#define PIN_MODE_IFLOAT         0x04    // in floating

#define PIN_MODE_2MHZ_OPP       0x02    // out push-pull; speed 2 MHz
#define PIN_MODE_10MHZ_OPP      0x01    // out push-pull; speed 10 MHz
#define PIN_MODE_50MHZ_OPP      0x03    // out push-pull; speed 50 MHz

#define PIN_MODE_2MHZ_AFPP      0x0a    // alternate function push-pull; speed 2 MHz
#define PIN_MODE_2MHZ_AFOD      0x0e    // alternate function open-drain; speed 2 MHz

// GPIO
void SetGpioMode(GPIO_TypeDef* port, int pin, int mode);
bool GetPinState(GPIO_TypeDef* port, int pin);
void SetPin(GPIO_TypeDef* port, int pin);
void ResetPin(GPIO_TypeDef* port, int pin);
void SwitchPin(GPIO_TypeDef* port, int pin);
void SetMulPin(GPIO_TypeDef* port, int mask);
void ResetMulPin(GPIO_TypeDef* port, int mask);


#endif
