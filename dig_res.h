/*
    1. Configure control pins (CS should be high)
    2. Create digres_t variables
        for 64-step resistor init value = 0x1F, max value = 0x3F
        digres_t Res = {CS_PIN, UD_PIN, 0x1F, 0x3F};
*/

// STM32F103
#include "stm32f10x.h"


#ifndef __DIG_RES_H__
#define __DIG_RES_H__


// Digital resistor type
typedef struct
{
    GPIO_TypeDef* cs_port;      // Resistor chip select pin
    int cs_pin;
    GPIO_TypeDef* ud_port;      // Resistor up ~down pin
    uint16_t ud_pin;
    uint16_t value;             // Initial value (0x1F)
    int max_value;              // Max value (0x3F)
}
digres_t;


// Increase/decrease value
void ChangeRes(digres_t* res, int16_t num);
// Set value
void SetRes(digres_t* res, uint16_t num);
// Get current value
uint16_t GetRes(digres_t* res);


#endif

