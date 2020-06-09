// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

// user
#include "exti.h"
#include "main.h"


// Line 10
void EXTI15_10_IRQHandler(void)
{   
    // Line 10 (PB10)
    if (EXTI->PR == EXTI_PR_PR10) {
    
        // Pending bit reset
        EXTI->PR |= EXTI_PR_PR10;
    
    }
    
}

void InitExti(void)
{
    // AFIO config
    AFIO->EXTICR[2] =   AFIO_EXTICR3_EXTI10_PB |    // PB10
                        AFIO_EXTICR3_EXTI11_PB;     // PB11
    
    // Interrupt mask
    EXTI->IMR =     EXTI_IMR_MR0        * 0 |   // line 0 (PA0, PB0 etc)
                    EXTI_IMR_MR1        * 0 |   // line 1
                    EXTI_IMR_MR2        * 0 |   // line 2
                    EXTI_IMR_MR3        * 0 |   // line 3
                    EXTI_IMR_MR4        * 0 |   // line 4
                    EXTI_IMR_MR5        * 0 |   // line 5
                    EXTI_IMR_MR6        * 0 |   // line 6
                    EXTI_IMR_MR7        * 0 |   // line 7
                    EXTI_IMR_MR8        * 0 |   // line 8
                    EXTI_IMR_MR9        * 0 |   // line 9
                    EXTI_IMR_MR10       * 1 |   // line 10
                    EXTI_IMR_MR11       * 0 |   // line 11
                    EXTI_IMR_MR12       * 0 |   // line 12
                    EXTI_IMR_MR13       * 0 |   // line 13
                    EXTI_IMR_MR14       * 0 |   // line 14
                    EXTI_IMR_MR15       * 0;    // line 15

    // Rising edge trigger
    EXTI->RTSR =    EXTI_RTSR_TR0       * 0 |   // line 0
                    EXTI_RTSR_TR1       * 0 |   // line 1
                    EXTI_RTSR_TR2       * 0 |   // line 2
                    EXTI_RTSR_TR3       * 0 |   // line 3
                    EXTI_RTSR_TR4       * 0 |   // line 4
                    EXTI_RTSR_TR5       * 0 |   // line 5
                    EXTI_RTSR_TR6       * 0 |   // line 6
                    EXTI_RTSR_TR7       * 0 |   // line 7
                    EXTI_RTSR_TR8       * 0 |   // line 8
                    EXTI_RTSR_TR9       * 0 |   // line 9
                    EXTI_RTSR_TR10      * 1 |   // line 10
                    EXTI_RTSR_TR11      * 0 |   // line 11
                    EXTI_RTSR_TR12      * 0 |   // line 12
                    EXTI_RTSR_TR13      * 0 |   // line 13
                    EXTI_RTSR_TR14      * 0 |   // line 14
                    EXTI_RTSR_TR15      * 0;    // line 15
    
    // Falling edge trigger
    EXTI->FTSR =    EXTI_FTSR_TR0       * 0 |   // line 0
                    EXTI_FTSR_TR1       * 0 |   // line 1
                    EXTI_FTSR_TR2       * 0 |   // line 2
                    EXTI_FTSR_TR3       * 0 |   // line 3
                    EXTI_FTSR_TR4       * 0 |   // line 4
                    EXTI_FTSR_TR5       * 0 |   // line 5
                    EXTI_FTSR_TR6       * 0 |   // line 6
                    EXTI_FTSR_TR7       * 0 |   // line 7
                    EXTI_FTSR_TR8       * 0 |   // line 8
                    EXTI_FTSR_TR9       * 0 |   // line 9
                    EXTI_FTSR_TR10      * 0 |   // line 10
                    EXTI_FTSR_TR11      * 0 |   // line 11
                    EXTI_FTSR_TR12      * 0 |   // line 12
                    EXTI_FTSR_TR13      * 0 |   // line 13
                    EXTI_FTSR_TR14      * 0 |   // line 14
                    EXTI_FTSR_TR15      * 0;    // line 15
}
