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
