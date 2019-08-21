// cstd
#include <stdbool.h>

//user
#include "keyboard.h"
#include "gpio.h"
#include "main.h"

bool key[16] = {false};

int KeyPressed(void)
{
    int i;
    for (i = 0; i < 16; i++)
        if (key[i])
            break;
    if (i == 16)
        return 0;
    else
        return (i+1);
}
bool KeyState(int num)
{
    if ((num > 0)&&(num < 17))
        return key[num];
    else
        return true;
}
void KeyCheck(void)
{
    static int cycle_state = 0;
    static int key_number = 0;
    
    switch (cycle_state)
    {
    case 0:
        PinReset(KEYSCL_PORT, KEYSCL_PIN);
        break;
    case 1:
        key[key_number] = ! PinState(KEYSDA_PORT, KEYSDA_PIN);
        key_number++;
        if (key_number == 16)
            key_number = 0;
        break;
    case 2:
        PinSet(KEYSCL_PORT, KEYSCL_PIN);
    }
    cycle_state++;
    if (cycle_state == 4)
        cycle_state = 0;
}
