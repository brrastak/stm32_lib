/*
    1. Configure button pins
    2. Create btn_t variables
        max_count should be about 20 for 20ms debouncing
        btn_t BtnL0 = {BTN_L0, 0, 20, false, false, false};
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

// Increase counter and set button state when counter == max_count (debouncing)
void CheckBtn(btn_t*);
// Get button state
bool IsPressed(btn_t*);
// Get was_pressed button state and reset it
bool WasPressed(btn_t*);

#endif