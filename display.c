// STM32F103
#include "stm32f10x.h"

// user
#include "display.h"
#include "main.h"
#include "gpio.h"
#include "i2c.h"
#include "timer.h"

#define I2C_DISP_ADDR       0x4e // slave write address for PCF8574T

#define DISP_RS_MASK            0x01
#define DISP_RW_MASK            0x02
#define DISP_E_MASK             0x04
#define DISP_BACKLIGHT_MASK     0x08

#ifndef I2C_DISP

#define DELAY1_US       2   // more than 2us : strob
#define DELAY2_US       50  // more than 50us : wait for command execution

#else

#define DELAY1_US       200 // more than 2us : strob
#define DELAY2_US       200 // more than 50us : wait for command execution

#endif

uint8_t nibble = 0;

void WriteNibble(void);
// To reset initialization by random data
void ResetDisplay(void);

inline void WriteNibble()
{
#ifdef I2C_DISP

    nibble |= DISP_E_MASK;
    I2CWrite(I2C_DISP_ADDR, nibble, 1);
    
    Delay_us(DELAY1_US);
    nibble &= ~DISP_E_MASK;
    I2CWrite(I2C_DISP_ADDR, nibble, 1);
    Delay_us(DELAY1_US);
    
#else

    if (nibble & DISP_RS_MASK)
        PinSet(PORTPIN(DISP_RS));
    else
        PinReset(PORTPIN(DISP_RS));
    if (nibble & 0x10)
        PinSet(PORTPIN(DISP_D4));
    else
        PinReset(PORTPIN(DISP_D4));
    if (nibble & 0x20)
        PinSet(PORTPIN(DISP_D5));
    else
        PinReset(PORTPIN(DISP_D5));
    if (nibble & 0x40)
        PinSet(PORTPIN(DISP_D6));
    else
        PinReset(PORTPIN(DISP_D6));
    if (nibble & 0x80)
        PinSet(PORTPIN(DISP_D7));
    else
        PinReset(PORTPIN(DISP_D7));
    
    PinSet(PORTPIN(DISP_E));
    Delay_us(DELAY1_US);
    PinReset(PORTPIN(DISP_E));
    Delay_us(DELAY1_US);
    
#endif
}

void InitDisp(void)
{
	uint8_t byte;
    
    // To reset initialization by random data
    ResetDisplay();
    
    nibble &= ~DISP_RW_MASK;    // write
    nibble &= ~DISP_RS_MASK;    // command
    BacklightOn();
    
    // half-byte mode on
    nibble &= 0x0f;
    nibble |=   0x20 |
                0x10 * 0;   // DL   0:4 bits            1:8 bits
    WriteNibble();
    Delay_us(DELAY2_US);

    // settings
    byte = 0x20;
    byte |=     0x10 * 0 |  // DL   0:4 bits            1:8 bits
                0x08 * 1 |  // N    0:1 line            1:2 lines
                0x04 * 0;   // F    0:5x8 dots          1:5x10 dots
    WriteCommandByte(byte);
    Delay_us(DELAY2_US);

    // turn on
    byte = 0x08;
    byte |=     0x04 * 1 |  // D    0:display off       1:display on
                0x02 * 0 |  // C    0:cursor off        1:cursor on
                0x01 * 0;   // B    0:cursor blink off  1:cursor blink on
    WriteCommandByte(byte);
    Delay_us(DELAY2_US);
    
    // cursor / display
    byte = 0x04;
    byte |=     0x02 * 1 |  // I/D  0:cursor decrement  1:cursor increment
                0x01 * 0;   // S    0:display shift off 1:display shift on
    WriteCommandByte(byte);
    Delay_us(DELAY2_US);

    // cursor / display
    byte = 0x10;
    byte |=     0x08 * 0 |  // S/C  0:cursor move       1:display shift
                0x04 * 1;   // R/L  0:shift to the left 1:shift to the right
    WriteCommandByte(byte);
    Delay_us(DELAY2_US);
	
	ClrScr();
    Delay_ms(2);
}

void ResetDisplay()
{
    Delay_ms(15);
    
    nibble &= ~DISP_RW_MASK;    // write
    nibble &= ~DISP_RS_MASK;    // command
    
    // 8-bit mode on three times
    nibble &= 0x0f;
    nibble |=   0x20 |
                0x10 * 1;   // DL   0:4 bits            1:8 bits
    WriteNibble();
    Delay_ms(5);
    
    nibble &= 0x0f;
    nibble |=   0x20 |
                0x10 * 1;   // DL   0:4 bits            1:8 bits
    WriteNibble();
    Delay_us(100);
    
    nibble &= 0x0f;
    nibble |=   0x20 |
                0x10 * 1;   // DL   0:4 bits            1:8 bits
    WriteNibble();
    Delay_us(DELAY2_US);
}

void WriteCommandByte(uint8_t byte)      // RS = 0
{
	nibble &= ~DISP_RS_MASK;
    
    nibble &= 0x0f;
    nibble |= (byte & 0xf0);    // hi
    WriteNibble();
    
    nibble &= 0x0f;
    nibble |= (byte << 4);      // lo
    WriteNibble();
}

void WriteDataByte(uint8_t byte)     // RS = 1
{
    nibble |= DISP_RS_MASK;
    
    nibble &= 0x0f;
    nibble |= (byte & 0xf0);    // hi
    WriteNibble();
    
    nibble &= 0x0f;
    nibble |= (byte << 4);      // lo
    WriteNibble();
}

void ClrScr(void)
{
	WriteCommandByte(0x01);
}

void MoveToLine2(void)
{
    WriteCommandByte(0xC0);
    Delay_us(DELAY2_US);
}

void MoveScreen(bool dir)
{
    if (dir)
        WriteCommandByte(0x18);
    else
        WriteCommandByte(0x1C);
    Delay_us(DELAY2_US);
}

void WriteChar(char c)
{
	WriteDataByte(c);
    Delay_us(DELAY2_US);
}

void WriteString(char * str, int n)
{
	int i;
	for (i = 0; i < n; i++)
		WriteChar(str[i]);
}

void WriteLine(char * str)
{
	int i = 0;
	while (str[i] != 0) {
		WriteChar(str[i]);
        i++;
    }
}

inline void BacklightOn(void)
{
    nibble |= DISP_BACKLIGHT_MASK;
}
inline void BacklightOff(void)
{
    nibble &= ~DISP_BACKLIGHT_MASK;
}

