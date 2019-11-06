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
    3. The order of colors is green, red, blue
    4. The order of digits is MSB first
*/

// cstd
#include <stdbool.h>
#include <stdint.h>

#ifndef __WS2812B_H__
#define __WS2812B_H__

#define LED_NUM                 8   // number of LEDs
#define DIGIT_NUM               8   // number of binary digits
#define COLOR_NUM               3   // number of colors
// Duty time for 0 and 1 values for LED
#define DUTY_LOW                3
#define DUTY_HIGH               6

// Code three color values into LED structure
void CodeRGB(int red, int green, int blue, int num);
// Return duty time for next binary digit
uint8_t DutyTimeValue(void);
// If all digits are send
bool AllDigits(void);

#endif