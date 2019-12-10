// cstd
#include <stdbool.h>

//user
#include "button.h"
#include "gpio.h"

// Increase counter and get button state when counter == max_count (debouncing)
void CheckBtn(btn_t* butn)
{
    bool prev = butn->is_pressed;
    if (!GetPinState(butn->port, butn->pin))
        butn->counter++;
    else
        butn->counter--;
    
    if (butn->counter > butn->max_count)
        butn->counter = butn->max_count;
    if (butn->counter < 0)
        butn->counter = 0;
    
    if (butn->counter == butn->max_count)
        butn->is_pressed = true;
    if (butn->counter == 0)
        butn->is_pressed = false;
    if ((butn->is_pressed)&&(! prev))
        butn->was_pressed = true;
    if ((! butn->is_pressed)&&(prev))
        butn->was_unpressed = true;
}
// Get button state
bool IsPressed(btn_t* butn)
{
    return butn->is_pressed;
}
// Get was_pressed button state and reset it
bool WasPressed(btn_t* butn)
{
    if (butn->was_pressed == true) {
        butn->was_pressed = false;
        return true;
    }
    else
        return false;
}

