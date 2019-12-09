/*
    1. Declare buffer variable
        set BUF_SIZE and *buf at LCD_char.c
    Size of buffer must be char X dimension in pixels * Y dimension in pixels * 6
    For example: Verdana34x32 -> 34 * 32 * 6 bytes

    \n and \r chars work
*/


// cstd
#include <stdbool.h>
#include <stdint.h>

// user
#include "LCD_8bit.h"
#include "chartable.h"

#ifndef __LCD_CHAR_H__
#define __LCD_CHAR_H__

// Font styles type
typedef enum
{
    verdana34x32_font
}
font_t;

// Set coordinates to place char
// otherwise the char will be placed next to the previous
void SetCoordinatesLcd(uint16_t x, uint16_t y);
// Set font and background colors
void SetColorLcd(rgb_t font_color, rgb_t back_color);
// Set font charset
void SetFontLcd(font_t font);
// Print char
void PrintCharLcd(char c);
// Print string (null-terminated)
void PrintStringLcd(char * str);
// Print string (null-terminated) and go to the next line
void PrintStringLnLcd(char * str);
// Print num of chars
void PrintLineLcd(char * str, int num);
// Print num of chars and go to the next line
void PrintLineLnLcd(char * str, int num);

#endif
