/*
    1. Configure button pins
    2. Create button_t variables
    3. Call ButtonCheck about every 1ms for every variable
*/

// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

#ifndef __BUTTON_H__
#define __BUTTON_H__

// Button
typedef struct
{
    GPIO_TypeDef* port;
    int pin;
    int counter;
    int max_count;
    volatile bool is_pressed;
    bool was_pressed;
    bool was_unpressed;
}
btn_t;
void BtnCheck(btn_t*);

#endif