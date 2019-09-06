// TIM1 PWM
#define PWM_1P_PORT             GPIOA
#define PWM_1P_PIN              8
#define PWM_1N_PORT             GPIOB
#define PWM_1N_PIN              13
#define PWM_2P_PORT             GPIOA
#define PWM_2P_PIN              9
#define PWM_2N_PORT             GPIOB
#define PWM_2N_PIN              14

// TIM1
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    GPIOMode(PORTPIN(PWM_1P), PIN_MODE_2MHZ_AFPP);
    GPIOMode(PORTPIN(PWM_1N), PIN_MODE_2MHZ_AFPP);
    GPIOMode(PORTPIN(PWM_2P), PIN_MODE_2MHZ_AFPP);
    GPIOMode(PORTPIN(PWM_2N), PIN_MODE_2MHZ_AFPP);

void InitTIM1(void)
{
    // Timer
    TIM1->CR1 =     TIM_CR1_CKD_0       * 0 |   // clock division for dead time : DTS = CK_INT
                    TIM_CR1_CKD_1       * 0 |
                    TIM_CR1_ARPE        * 0 |   // auto-reload preload enable
                    TIM_CR1_CMS_0       * 0 |   // center-aligned mode selection : edge-aligned mode
                    TIM_CR1_CMS_1       * 0 |
                    TIM_CR1_DIR         * 0;    // direction : upcounter
    
    TIM1->PSC = 35999;                  // CK_CNT = 2kHz
    TIM1->ARR = 39;                     // 50Hz
    
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
                    TIM_CCER_CC1P       * 0 |   // capture/compare 1 output polarity: active high
                    TIM_CCER_CC1NE      * 1 |   // capture/compare 1 complementary output enable
                    TIM_CCER_CC1NP      * 0 |   // capture/compare 1 complementary output polarity: active high
                        
                    TIM_CCER_CC2E       * 1 |   // capture/compare 2 output enable
                    TIM_CCER_CC2P       * 0 |   // capture/compare 2 output polarity: active high
                    TIM_CCER_CC2NE      * 1 |   // capture/compare 2 complementary output enable
                    TIM_CCER_CC2NP      * 0;    // capture/compare 2 complementary output polarity: active high
        
    TIM1->CCR1 = 20;       // channel 1 duty time = 50%
    TIM1->CCR2 = 20;       // channel 2 duty time = 50%
    
    TIM1->BDTR =    0xff |                      // dead time
                    TIM_BDTR_MOE        * 1;    // main output enable
    
    // Generate update event
    TIM1->EGR = TIM_EGR_UG;
    
    // Interrupt
    //TIM1->DIER |= TIM_DIER_UIE;         // update interrupt enable
    
    // Start!
    TIM1->CR1 |= TIM_CR1_CEN;
}
