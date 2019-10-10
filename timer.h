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
// Init TIM2 for PWM generation
void InitPWMTimer(void);
// Init TIM3 for periodical ADC reading
void InitADCTimer(void);
// Delay TIM4
void delay_ms(int time);    // 32000ms max
void delay_us(int time);    // 32000us max
// PWM on/off
void PWMEnable(void);
void PWMDisable(void);

// SysTick timer interrupt
void SysTick_Handler(void);
// TIM2 update interrupt
void TIM2_IRQHandler(void);

#endif
