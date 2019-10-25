// cstd
#include <stdbool.h>

//user
#include "button.h"

void BtnCheck(btn_t* butn)
{
    bool prev = butn->is_pressed;
    if (!PinState(butn->port, butn->pin))
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