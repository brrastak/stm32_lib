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
// TIM2 capture interrupt
void TIM2_IRQHandler(void)
{   
    static uint16_t prev_captured3, prev_captured4;
    
    if ((TIM2->SR & TIM_SR_CC4IF) != 0) {   // capture/compare 4 interrupt
        
        TIM2->SR &= ~TIM_SR_CC4IF;          // clear flag
        
        pitch_freq = TIM2->CCR4 - prev_captured4;
        prev_captured4 = TIM2->CCR4;
    }
    if ((TIM2->SR & TIM_SR_CC3IF) != 0) {   // capture/compare 3 interrupt
        
        TIM2->SR &= ~TIM_SR_CC3IF;          // clear flag
        
        volume_freq = TIM2->CCR3 - prev_captured3;
        prev_captured3 = TIM2->CCR3;
    }
}
// TIM1 update interrupt
void TIM1_UP_IRQHandler(void)
{       
    if (!(TIM1->SR & TIM_SR_UIF)) return;
    TIM1->SR &= ~TIM_SR_UIF;            // clear flag
    
    // Duty time from sound.c
    SetTim1DutyTime(0);
}
void InitSysTick(void)
{
    SysTick->LOAD = SYS_TIMER_TICK;
    SysTick->VAL = 0;
    SysTick->CTRL =	SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk   |    // interrupt enable
                    SysTick_CTRL_ENABLE_Msk;
}
// Proceed SysTick value and reset counter
bool IfDelayPassed(uint32_t &cnt, uint32_t delay_ms)
{
    if ((sys_tick - cnt) > delay_ms) {
        
        cnt = sys_tick;
        return true;
    }
    else
        return false;
}
// Reset counter
void ResetCounter(uint32_t &cnt)
{
    cnt = sys_tick;
}
void InitTim2(void)
{
    // Timer
    TIM2->CR1 = TIM_CR1_ARPE    * 1 |   // Auto-reload preload enable
                TIM_CR1_CMS_0   * 0 |   // Center-aligned mode selection : edge-aligned mode
                TIM_CR1_CMS_1   * 0 |
                TIM_CR1_DIR     * 0;    // Direction : upcounter
    TIM2->PSC = 359;                    // CK_CNT = 200kHz
    TIM2->ARR = 39;                     // 5kHz
    TIM2->EGR = TIM_EGR_UG;             // update event enable
    // DMA
    TIM2->DIER  |= TIM_DIER_UDE;        // update DMA request enable
    // PWM
    TIM2->CCMR2 =   TIM_CCMR2_OC4M_0    * 1 |   // C4 PWM mode 2
                    TIM_CCMR2_OC4M_1    * 1 |
                    TIM_CCMR2_OC4M_2    * 1;
    TIM2->CCER  =   TIM_CCER_CC4E       * 1 |   // C4 out enable
                    TIM_CCER_CC4P       * 0;    // C4 active high
    TIM2->CCR4  = 20;                           // duty time = 50%
    // External input
    TIM2->CCMR1 =   TIM_CCMR1_CC1S_0    * 1 |   // channel 1 input on TI1
                    TIM_CCMR1_CC1S_1    * 0 |
                    TIM_CCMR1_IC1F_0    * 0 |   // input filter disable
                    TIM_CCMR1_IC1F_1    * 0 |
                    TIM_CCMR1_IC1F_2    * 0 |
                    TIM_CCMR1_IC1F_3    * 0;
    TIM2->CCER =    TIM_CCER_CC1P       * 0;    // rising edge capture
    TIM2->SMCR =    TIM_SMCR_SMS_0      * 1 |   // external clock mode 1
                    TIM_SMCR_SMS_1      * 1 |
                    TIM_SMCR_SMS_2      * 1 |
                    TIM_SMCR_TS_0       * 1 |   // TI1 input source
                    TIM_SMCR_TS_1       * 0 |
                    TIM_SMCR_TS_2       * 1;
    // Input capture
    TIM2->CCMR2 =   TIM_CCMR2_CC4S_0    * 1 |   // channel 4 input on TI4
                    TIM_CCMR2_CC4S_1    * 0 |
                    TIM_CCMR2_IC4F_0    * 0 |   // channel 4 input filter disable
                    TIM_CCMR2_IC4F_1    * 0 |
                    TIM_CCMR2_IC4F_2    * 0 |
                    TIM_CCMR2_IC4F_3    * 0 |
                    TIM_CCMR2_IC4PSC_0  * 1 |   // channel 4 prescaler = 8
                    TIM_CCMR2_IC4PSC_1  * 1 |
                    TIM_CCMR2_CC3S_0    * 1 |   // channel 3 input on TI3
                    TIM_CCMR2_CC3S_1    * 0 |
                    TIM_CCMR2_IC3F_0    * 0 |   // channel 3 input filter disable
                    TIM_CCMR2_IC3F_1    * 0 |
                    TIM_CCMR2_IC3F_2    * 0 |
                    TIM_CCMR2_IC3F_3    * 0 |
                    TIM_CCMR2_IC3PSC_0  * 1 |   // channel 3 prescaler = 8
                    TIM_CCMR2_IC3PSC_1  * 1;
    
    TIM2->CCER =    TIM_CCER_CC4P       * 0 |   // channel 4 rising edge capture
                    TIM_CCER_CC4E       * 1 |   // channel 4 capture input enable
                    TIM_CCER_CC3P       * 0 |   // channel 3 rising edge capture
                    TIM_CCER_CC3E       * 1;    // channel 3 capture input enable
    // Interrupt
    TIM2->DIER |= TIM_DIER_UIE;         // update interrupt enable
    TIM2->DIER |=   //TIM_DIER_UIE |      // update interrupt enable
                    TIM_DIER_CC4IE |    // capture/compare 4 interrupt enable
                    TIM_DIER_CC3IE;     // capture/compare 3 interrupt enable
}
void SetTim2DutyTime(int duty_time)
{
    TIM2->CCR1 = duty_time;
}
void EnableTim2(void)
{
    TIM4->EGR = TIM_EGR_UG;         // update
    TIM2->CR1 |= TIM_CR1_CEN;       // start
    TIM2->CCER |= TIM_CCER_CC1E;    // out enable
}
void DisableTim2(void)
{
    TIM2->CR1 &= ~TIM_CR1_CEN;      // stop
    TIM2->CCER &= ~TIM_CCER_CC1E;   // out disable
}
void InitTim1(void)
{
    // Timer
    TIM1->CR1 =     TIM_CR1_CKD_0       * 0 |   // clock division for dead time : DTS = CK_INT
                    TIM_CR1_CKD_1       * 0 |
                    TIM_CR1_ARPE        * 0 |   // auto-reload preload enable
                    TIM_CR1_CMS_0       * 0 |   // center-aligned mode selection : edge-aligned mode
                    TIM_CR1_CMS_1       * 0 |
                    TIM_CR1_DIR         * 0;    // direction : upcounter
    
    TIM1->PSC = F_CPU / SAMPLING_RATE / BIT_DEPTH - 1;
    TIM1->ARR = BIT_DEPTH - 1;             // 16kHz
    
    // PWM
    TIM1->CCMR1 =   TIM_CCMR1_CC1S_0    * 0 |   // capture/compare 1 selection: compare
                    TIM_CCMR1_CC1S_1    * 0 |
                    TIM_CCMR1_OC1PE     * 0 |   // output compare 1 preload enable
                    TIM_CCMR1_OC1M_0    * 0 |   // output compare 1 mode: PWM mode 1 (active->inactive)
                    TIM_CCMR1_OC1M_1    * 1 |
                    TIM_CCMR1_OC1M_2    * 1 |
                        
                    TIM_CCMR1_CC2S_0    * 0 |   // capture/compare 2 selection: compare
                    TIM_CCMR1_CC2S_1    * 0 |
                    TIM_CCMR1_OC2PE     * 0 |   // output compare 2 preload enable
                    TIM_CCMR1_OC2M_0    * 0 |   // output compare 2 mode: PWM mode 1 (active->inactive)
                    TIM_CCMR1_OC2M_1    * 1 |
                    TIM_CCMR1_OC2M_2    * 1;
    
    TIM1->CCER =    TIM_CCER_CC1E       * 1 |   // capture/compare 1 output enable
                    TIM_CCER_CC1P       * 1 |   // capture/compare 1 output polarity: active low
                    TIM_CCER_CC1NE      * 1 |   // capture/compare 1 complementary output enable
                    TIM_CCER_CC1NP      * 0 |   // capture/compare 1 complementary output polarity: active high
                        
                    TIM_CCER_CC2E       * 1 |   // capture/compare 2 output enable
                    TIM_CCER_CC2P       * 1 |   // capture/compare 2 output polarity: active low
                    TIM_CCER_CC2NE      * 1 |   // capture/compare 2 complementary output enable
                    TIM_CCER_CC2NP      * 0;    // capture/compare 2 complementary output polarity: active high
        
    TIM1->CCR1 = 0;             // channel 1 duty time = 0%
    TIM1->CCR2 = 0;             // channel 2 duty time = 0%
    
    TIM1->BDTR =    0x04 |                      // dead time
                    TIM_BDTR_MOE        * 1;    // main output enable
    
    // Generate update event
    TIM1->EGR = TIM_EGR_UG;
    
    // Interrupt
    TIM1->DIER |= TIM_DIER_UIE;         // update interrupt enable
    
    // Start!
    TIM1->CR1 |= TIM_CR1_CEN;
}
void SetTim1DutyTime(uint16_t duty)
{
    if (duty >= 128) {
        TIM1->CCR1 = (duty - 128) & 0xFF;
        TIM1->CCR2 = 0;
    }
    else {
        TIM1->CCR1 = 0;
        TIM1->CCR2 = (128 - duty) & 0xFF;
    }
}

void InitTim3(void)
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
