// STM32F103
#include "stm32f10x.h"

// user
#include "main.h"
#include "timer.h"

volatile uint32_t sys_tick = 0;

// SysTick timer interrupt
void SysTick_Handler(void)
{
    sys_tick++;         // every 1ms
}
// TIM2 update interrupt
void TIM2_IRQHandler(void)
{
    static int counter = 0;
    
    if (!(TIM2->SR & TIM_SR_UIF)) return;
    TIM2->SR &= ~TIM_SR_UIF;            // clear flag
    counter++;
    if ((counter < 5) && (TIM2->CCR1 != 0))
        TIM2->CCR1 += 10;
    if ((counter > 50) && (TIM2->CCR1 != 0))
        TIM2->CCR1 -= 10;
    if (counter == 100)
        counter = 0;
    if ((counter == 0) /*&& State.pump_on*/)
        TIM2->CCR1 = 10;
}
void InitSysTick(void)
{
    SysTick->LOAD = SYS_TIMER_TICK;
    SysTick->VAL = 0;
    SysTick->CTRL =	SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk   |    // interrupt enable
                    SysTick_CTRL_ENABLE_Msk;
}
void InitPWMTimer(void)
{
    // Timer
    TIM2->CR1 = TIM_CR1_ARPE    * 1 |   // Auto-reload preload enable
                TIM_CR1_CMS_0   * 0 |   // Center-aligned mode selection : edge-aligned mode
                TIM_CR1_CMS_1   * 0 |
                TIM_CR1_DIR     * 0;    // Direction : upcounter
    TIM2->PSC = 359;                    // CK_CNT = 200kHz
    TIM2->ARR = 39;                     // 5kHz
    TIM2->EGR = TIM_EGR_UG;             // update
    // DMA
    TIM2->DIER  |= TIM_DIER_UDE;        // update DMA request enable
    // PWM
    TIM2->CCMR1 = 0x60;                 // PWM mode 1
    TIM2->CCER |= 0x01;                 // out enable & active high
    TIM2->CCR1 = 0;                     // duty time = 50%
    // Interrupt
    TIM2->DIER |= TIM_DIER_UIE;         // update interrupt enable
}
void PWMEnable(void)
{
    TIM2->CR1 |= TIM_CR1_CEN;
}
void PWMDisable(void)
{
    TIM2->CR1 &= ~TIM_CR1_CEN;
}
void InitADCTimer(void)
{
    // Timer
    TIM3->CR1 = TIM_CR1_ARPE    * 1 |   // Auto-reload preload enable
                TIM_CR1_CMS_0   * 0 |   // Center-aligned mode selection : edge-aligned mode
                TIM_CR1_CMS_1   * 0 |
                TIM_CR1_DIR     * 0;    // Direction : upcounter
    TIM3->CR2 |= 0x20;                  // TRGO on update event
    TIM3->PSC = 3599;                   // CK_CNT = 20kHz
    TIM3->ARR = 399;                    // 50 Hz
    TIM3->EGR = TIM_EGR_UG;             // update event enable
    // Interrupt
    //TIM3->DIER |= TIM_DIER_UIE;         // update
    // Start!
    TIM3->CR1 |= TIM_CR1_CEN;
}

// Delay TIM4
void delay_ms(int time)
{
    TIM4->CR1 = 0;
    TIM4->SR = 0;
    TIM4->PSC = 35999;                  // 2kHz
    TIM4->ARR = time * 2 - 1;
    TIM4->EGR = TIM_EGR_UG;
    TIM4->SR &= ~TIM_SR_UIF;
    TIM4->CR1 |= TIM_CR1_CEN;
    while (!(TIM4->SR & TIM_SR_UIF))
        ;
    TIM4->CR1 &= ~TIM_CR1_CEN;
}
void delay_us(int time)
{
    TIM4->CR1 = 0;
    TIM4->SR = 0;
    TIM4->PSC = 35;                     // 2MHz
    TIM4->ARR = time * 2 - 1;
    TIM4->EGR = TIM_EGR_UG;
    TIM4->SR &= ~TIM_SR_UIF;
    TIM4->CR1 |= TIM_CR1_CEN;
    while (!(TIM4->SR & TIM_SR_UIF))
        ;
    TIM4->CR1 &= ~TIM_CR1_CEN;
}
