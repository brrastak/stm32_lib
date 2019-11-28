// STM32F103
#include "stm32f10x.h"

// user
#include "init.h"
#include "main.h"
#include "gpio.h"

void InitRcc(void)
{
    // port A
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    // port B
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    // port C
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    // TIM2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    // TIM4
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    // I2C2
    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
    // SPI1
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    // USART2
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    // AFIO
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    // DMA1
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;
}
void InitInterrupt(void)
{
    // TIM2
    //NVIC_EnableIRQ(TIM2_IRQn);
    // TIM3
    //NVIC_EnableIRQ(TIM3_IRQn);
    // ADC1
    //NVIC_EnableIRQ(ADC1_2_IRQn);
    // I2C1
    NVIC_EnableIRQ(I2C2_EV_IRQn);
    // USART2
    NVIC_EnableIRQ(USART2_IRQn);
}
void InitGpio(void)
{
    //GPIOMode(PWM_PORT, PWM_PIN, PIN_MODE_2MHZ_OPP);
    GPIOMode(BUTN0_PORT, BUTN0_PIN, PIN_MODE_IFLOAT);
    GPIOMode(BUTN1_PORT, BUTN1_PIN, PIN_MODE_IFLOAT);
    GPIOMode(LED_PORT, LED_PIN, PIN_MODE_2MHZ_OPP);

    GPIOMode(I2C_PORT, I2C1_PIN, PIN_MODE_2MHZ_AFOD);
    GPIOMode(I2C_PORT, I2C2_PIN, PIN_MODE_2MHZ_AFOD);
    // Display
    GPIOMode(PORTPIN(DISP_RS), PIN_MODE_2MHZ_OPP);
    GPIOMode(PORTPIN(DISP_E), PIN_MODE_2MHZ_OPP);
    GPIOMode(PORTPIN(DISP_D4), PIN_MODE_2MHZ_OPP);
    GPIOMode(PORTPIN(DISP_D5), PIN_MODE_2MHZ_OPP);
    GPIOMode(PORTPIN(DISP_D6), PIN_MODE_2MHZ_OPP);
    GPIOMode(PORTPIN(DISP_D7), PIN_MODE_2MHZ_OPP);
    // KeyBoard
    GPIOMode(KEYSCL_PORT, KEYSCL_PIN, PIN_MODE_2MHZ_OPP);
    GPIOMode(KEYSDA_PORT, KEYSDA_PIN, PIN_MODE_IFLOAT);
    // SPI
    GPIOMode(SPI_PORT, SCK_PIN, PIN_MODE_2MHZ_AFPP);
    GPIOMode(SPI_PORT, MISO_PIN, PIN_MODE_2MHZ_AFPP);
    GPIOMode(SPI_PORT, MOSI_PIN, PIN_MODE_2MHZ_AFPP);
    GPIOMode(SPI_PORT, NSS_PIN, PIN_MODE_2MHZ_OPP);
}
