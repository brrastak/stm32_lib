// cstd
#include <stdbool.h>

//user
#include "gpio.h"

void GPIOMode(GPIO_TypeDef* port, int pin, int mode)
{
    if (pin > 7)
        port->CRH = (port->CRH & ~(0x0f << (pin-8)*4)) | (mode << (pin-8)*4);
    else
        port->CRL = (port->CRL & ~(0x0f << pin*4)) | (mode << pin*4);
}
inline bool PinState(GPIO_TypeDef* port, int pin)
{
    return ((port->IDR & (1 << pin)) != 0);
}
inline void PinSet(GPIO_TypeDef* port, int pin)
{
    port->BSRR = (1 << pin);
}
inline void PinReset(GPIO_TypeDef* port, int pin)
{
    port->BSRR = (1 << (pin+16));
}
inline void PinSwitch(GPIO_TypeDef* port, int pin)
{
    if (PinState(port, pin))
        PinReset(port, pin);
    else
        PinSet(port, pin);
}
inline void MulPinSet(GPIO_TypeDef* port, int mask)
{
    port->BSRR = (mask & 0x0ffff);
}
inline void MulPinReset(GPIO_TypeDef* port, int mask)
{
    port->BSRR = (mask & 0x0ffff) << 16;
}
// Button
void ButtonCheck(Button* butn)
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