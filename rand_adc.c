// STM32F103
#include "stm32f10x.h"

//user
#include "main.h"
#include "adc.h"

#define TEMP_CHANNEL        16

// Get internal temp sensor value
uint32_t RandADC(void)
{
    // ADC on
    ADC1->CR2 |= ADC_CR2_ADON;
    // Temp sensor on
    ADC1->CR2 |= ADC_CR2_TSVREFE;
    ADC1->SQR3 = TEMP_CHANNEL;      // channel to read
    
    // Start convertion
    ADC1->CR2 |= ADC_CR2_ADON;
    
    // wait for end of convertion
    while ((ADC1->SR & ADC_SR_EOC) == 0)
        ;
    
    return (ADC1->DR);
}
