/*
    1. Enable AFIO RCC
    2. Configure pin as input floating
    3. Call function InitEXTI
    4. Enable interrupt
*/

#ifndef __ENCODER_H__
#define __ENCODER_H__

extern int encoder_counter;

// Line 0 interrupt
void EXTI0_IRQHandler(void);

void InitEXTI(void);

#endif