// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

// user
#include "EXTI.h"
#include "main.h"
#include "gpio.h"

int encoder_counter = 0;

// Line 0 interrupt
void EXTI0_IRQHandler(void)
{
    // Pending bit reset
    EXTI->PR |= EXTI_PR_PR0;    // line 0
    if (PinState(PORTPIN(B)) == false)
        encoder_counter++;
    else
        encoder_counter--;
}

void InitEXTI(void)
{
    // AFIO config
    AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PB;    // port B
    
    // Interrupt mask
    EXTI->IMR =     EXTI_IMR_MR0        * 1;    // line 0
    // Falling edge trigger
    EXTI->FTSR =    EXTI_FTSR_TR0       * 1;    // line 0
}
