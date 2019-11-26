// cstd
#include <stdbool.h>

//user
#include "gpio.h"

void SetGpioMode(GPIO_TypeDef* port, int pin, int mode)
{
    if (pin > 7)
        port->CRH = (port->CRH & ~(0x0f << (pin-8)*4)) | (mode << (pin-8)*4);
    else
        port->CRL = (port->CRL & ~(0x0f << pin*4)) | (mode << pin*4);
}
inline bool GetPinState(GPIO_TypeDef* port, int pin)
{
    return ((port->IDR & (1 << pin)) != 0);
}
inline void SetPin(GPIO_TypeDef* port, int pin)
{
    port->BSRR = (1 << pin);
}
inline void ResetPin(GPIO_TypeDef* port, int pin)
{
    port->BSRR = (1 << (pin+16));
}
inline void SwitchPin(GPIO_TypeDef* port, int pin)
{
    if (GetPinState(port, pin))
        ResetPin(port, pin);
    else
        SetPin(port, pin);
}
inline void SetMulPin(GPIO_TypeDef* port, int mask)
{
    port->BSRR = (mask & 0x0ffff);
}
inline void ResetMulPin(GPIO_TypeDef* port, int mask)
{
    port->BSRR = (mask & 0x0ffff) << 16;
}
