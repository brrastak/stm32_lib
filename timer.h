// STM32F103
#include "stm32f10x.h"

#ifndef __TIMER_H__
#define __TIMER_H__

// CPU and SysTick timer frequency
#define F_CPU 		            72000000UL      // 72MHz
// every 1 ms
#define SYS_TIMER_TICK  	    (F_CPU/1000-1)  // 1kHz

// Ticks
extern volatile uint32_t sys_tick;

// Init SysTick timer
void InitSysTick(void);
// Proceed SysTick value and reset counter
bool IfDelayPassed(uint32_t* cnt, uint32_t delay_ms);
// Reset counter
void ResetCounter(uint32_t* cnt);
// Init TIM2 for PWM generation
void InitTim2(void);
void SetTim2DutyTime(uint16_t);
void SetTim2Per(uint16_t);
// Delay TIM4
void delay_ms(int time);    // 32000ms max
void delay_us(int time);    // 32000us max
// TIM2 on/off
void EnableTim2(void);
void DisableTim2(void);


#endif
