// STM32F103
#include "stm32f10x.h"

#ifndef __TIMER_H__
#define __TIMER_H__

// CPU and SysTick timer frequency
#define F_CPU 		            72000000UL      // 72MHz
// every 0.5 ms
#define SYS_TIMER_TICK  	    (F_CPU/1000-1)  // 1kHz

// Timer modes
#define TIM_CounterMode_Up                  0x00
#define TIM_CounterMode_Down                0x10
#define TIM_CounterMode_CenterAligned1      0x20
#define TIM_CounterMode_CenterAligned2      0x40
#define TIM_CounterMode_CenterAligned3      0x60

// Ticks
extern volatile uint32_t sys_tick;

// Init SysTick timer
void InitSysTick(void);
// Init TIM2 for PWM generation
void InitPWMTimer(void);
// Init TIM3 for periodical ADC reading
void InitADCTimer(void);
// Delay TIM4
void Delay_ms(int time);    // 32000ms max
void Delay_us(int time);    // 32000us max
// PWM on/off
void PWMEnable(void);
void PWMDisable(void);

// SysTick timer interrupt
void SysTick_Handler(void);
// TIM2 update interrupt
void TIM2_IRQHandler(void);

#endif