// STM32F103
#include "stm32f10x.h"

//user
#include "main.h"
#include "adc.h"

void InitADC(void)
{
    // Calibration
    ADC1->CR2 |= ADC_CR2_ADON;
    for (int i = 0; i < 16; i++)    // wait at least two ADC clock cycles
        __NOP();
    ADC1->CR2 |= ADC_CR2_CAL;       // calibration
    while (ADC1->CR2 & ADC_CR2_CAL)
        ;
    // Init
    ADC1->SQR1 = (NUMBER_OF_CHANNELS-1) << 20;  // total number of conversions
    ADC1->SQR3 =    T_COUPLE_CHANNEL |          // order is important
                    (T_RES_CHANNEL << 5) | 
                    (V_LINE_CHANNEL << 10) | 
                    (V_BAT_CHANNEL << 15);
    ADC1->CR2 = 0x04 << 17;                     // timer 3 TRGO event
    ADC1->CR1 |= (1-1) << 13;  // number of channels in discontinuous mode = 1
    ADC1->CR1 |=    ADC_CR1_DISCEN |            // discontinuous mode
                    ADC_CR1_EOCIE;              // interrupt enable for EOC
    ADC1->CR2 |=    ADC_CR2_EXTTRIG |           // extern event
                    ADC_CR2_ADON;
}