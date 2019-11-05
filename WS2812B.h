/*
    1. Configure timer output pin as 2MHz alternate function output push-pull
    2. Configure timer:
        TIMx->PSC = 9;                      // CK_CNT = 7,2MHz
        TIMx->ARR = 9;                      // T = 1,25 us
        TIMx->CCMR1 = 0x60;                 // PWM mode 1
        TIMx->CCER |= 0x01;                 // out enable & active high
        TIMx->CCR1:     3 for logical "0"; 6 for logical "1"
        duty time for logical "0": 0,4 mks
        duty time for logical "1": 0,8 mks
        period: 1,25 mks
*/

// cstd
#include <stdbool.h>
#include <stdint.h>

#ifndef __WS2812B_H__
#define __WS2812B_H__



#endif