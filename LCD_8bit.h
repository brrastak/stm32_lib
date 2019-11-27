/*
    1. Define PARALLEL_PORT : D0-D7 in one port
    2. Define RD_PIN, WR_PIN, RS_PIN, RST_PIN
        RD - read strobe (on rising edge)
        WR - write strobe (on rising edge)
        RS - 0: command; 1: data
        RST - reset (active low)
    3. Call InitLcd();
    4. Call HandleLcd(); periodically
*/

// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>
#include <stdint.h>

#ifndef __LCD_8BIT_H__
#define __LCD_8BIT_H__

// Receiving and transmitting process handled by timer
void HandleLcd(void);
// Init LCD
void InitLcd(void);
// Reset signal
void ResetLcd(void);
// Start communication
void TransmitLcdData(uint8_t * buf, int num);
void TransmitLcdCommand(uint8_t command);
void ReceiveLcdData(uint8_t * buf, int num);
// Communication state
bool IsLcdReceived(void);
bool IsLcdTransmitted(void);


#endif