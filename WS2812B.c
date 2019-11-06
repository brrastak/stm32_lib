// cstd
#include <stdbool.h>
#include <stdint.h>

// user
#include "WS2812B.h"

typedef struct
{
    uint8_t g[DIGIT_NUM];
    uint8_t r[DIGIT_NUM];
    uint8_t b[DIGIT_NUM];
} rgb_led_t;

static rgb_led_t LED[LED_NUM] = {DUTY_LOW};
uint8_t * digit = (uint8_t *)&LED;
static int digit_counter = 0;

void CodeRGB(int red, int green, int blue, int num)
{
    int i;
    
    for (i = 0; i < DIGIT_NUM; i++) {
        if ((red & (1 << i)) != 0)
            LED[num].r[DIGIT_NUM-1-i] = DUTY_HIGH;
        else
            LED[num].r[DIGIT_NUM-1-i] = DUTY_LOW;
        if ((green & (1 << i)) != 0)
            LED[num].g[DIGIT_NUM-1-i] = DUTY_HIGH;
        else
            LED[num].g[DIGIT_NUM-1-i] = DUTY_LOW;
        if ((blue & (1 << i)) != 0)
            LED[num].b[DIGIT_NUM-1-i] = DUTY_HIGH;
        else
            LED[num].b[DIGIT_NUM-1-i] = DUTY_LOW;
    }
}
inline uint8_t DutyTimeValue()
{
    return digit[digit_counter++];
}
inline bool AllDigits()
{
    bool res = (digit_counter == LED_NUM * DIGIT_NUM * COLOR_NUM);
    if (res)
        digit_counter = 0;
    return res;
}