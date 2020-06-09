/*
    1. Enable AFIO RCC
    2. Configure pin as input floating
    3. Call function InitExti
    4. Enable interrupt EXTIx_IRQn
*/

#ifndef __EXTI_H__
#define __EXTI_H__


void InitExti(void);

#endif
