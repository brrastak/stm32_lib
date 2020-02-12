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
    // Remap USART
    AFIO->MAPR |= AFIO_MAPR_USART1_REMAP;
    // Remap TIM2
    //AFIO->MAPR |= AFIO_MAPR_TIM2_REMAP_1;   // remap C4 to PB11
    // Remap SPI1
    AFIO->MAPR |= AFIO_MAPR_SPI1_REMAP;
    // Remap A15, B3, B4
    AFIO->MAPR |=   AFIO_MAPR_SWJ_CFG_2 * 0 |
                    AFIO_MAPR_SWJ_CFG_1 * 1 |
                    AFIO_MAPR_SWJ_CFG_0 * 0;
    
    // Debug LED
    SetGpioMode(LED_PIN, PIN_MODE_2MHZ_OPP);
    
    // Buttons
    SetGpioMode(BTN_L0, PIN_MODE_IFLOAT);
    SetGpioMode(BTN_L1, PIN_MODE_IFLOAT);
    //SetGpioMode(BTN_R0, PIN_MODE_IFLOAT);
    //SetGpioMode(BTN_R1, PIN_MODE_IFLOAT);
    SetGpioMode(BTN_R2, PIN_MODE_IFLOAT);
    SetGpioMode(BTN_R3, PIN_MODE_IFLOAT);
    
    // LCD
    SetGpioMode(RD_PIN, PIN_MODE_10MHZ_OPP);
    SetGpioMode(RS_PIN, PIN_MODE_10MHZ_OPP);
    SetGpioMode(RST_PIN, PIN_MODE_10MHZ_OPP);
    SetGpioMode(WR_PIN, PIN_MODE_10MHZ_OPP);

    // USART
    SetGpioMode(USART_TX_PIN, PIN_MODE_2MHZ_AFPP);
    //SetGpioMode(USART_RX_PIN, PIN_MODE_2MHZ_OPP);
    SetGpioMode(USART_RX_PIN, PIN_MODE_IFLOAT);
    
    // TIM1 PWM
    SetGpioMode(PWM_1P, PIN_MODE_2MHZ_AFPP);
    SetGpioMode(PWM_1N, PIN_MODE_2MHZ_AFPP);
    SetGpioMode(PWM_2P, PIN_MODE_2MHZ_AFPP);
    SetGpioMode(PWM_2N, PIN_MODE_2MHZ_AFPP);
    
    // SPI1
    SetGpioMode(SPI_NSS_PIN, PIN_MODE_10MHZ_OPP);
    SetGpioMode(SPI_SCK_PIN, PIN_MODE_10MHZ_AFPP);
    SetGpioMode(SPI_MISO_PIN, PIN_MODE_10MHZ_AFPP);
    SetGpioMode(SPI_MOSI_PIN, PIN_MODE_10MHZ_AFPP);
}
