
// cstd
#include <stdbool.h>
#include <stdint.h>

//user
#include "LCD_char.h"
#include "main.h"
#include "LCD_8bit.h"
#include "chartable.h"

// Buffer for DMA images
// must be multiple of 6
#define BUF_SIZE    DMA_BUF_SIZE
static uint16_t * buf = dma_buf;

// Font parameters
// Font char length (in charset) in bytes
const uint8_t FontArrayLength[] = {
    34*4+1      // Verdana34x32
};
// Font char height in pixels
const uint8_t FontHeight[] = {
    32          // Verdana34x32
};
// Font charset pointer
const uint8_t * const Font[] = {
    Verdana34x32
};

// Current coordinates to place char
static uint16_t current_x = 0;
static uint16_t current_y = 0;
// Current colors
static rgb_t font_color;
static rgb_t back_color;
// Current font
static font_t current_font = verdana34x32_font;

// Local functions
// Recognize '\n' and '\r'
bool IsSpecialSymbol(char c);
// Proceed '\n' and '\r'
void ProceedSpecialSymbol(char c, uint16_t start_x);

// Set coordinates to place char
// otherwise the char will be placed next to the previous
void SetCoordinatesLcd(uint16_t x, uint16_t y)
{
    current_x = x;
    current_y = y;
}
// Set font and background colors
void SetColorLcd(rgb_t font_clr, rgb_t back_clr)
{
    font_color = font_clr;
    back_color = back_clr;
}
// Set font charset
void SetFontLcd(font_t font)
{
    current_font = font;
}
// Print char
void PrintCharLcd(char c)
{
    while (! IsLcdTransmitted())
        ;
    
    // First byte of symbol; space is the first symbol in array
    uint32_t * charset = (uint32_t*)(Font[current_font] + 
                                    (c - ' ') * FontArrayLength[current_font]);
    // Length of char in pixels (first byte in charset)
    int char_length = charset[0];
    // Increase to one byte
    charset = (uint32_t*)((uint8_t*)charset + 1);
    
    //char_length = 20;                                 
    
    // Char -> data for DMA
    int i, j, k;
    k = 0;
    for (i = 0; i < char_length; i++) {
        for (j = 31; j >= 0; j--) {
            if ((charset[i] & (1 << j)) != 0) {
                buf[k++] = font_color.r;
                buf[k++] = font_color.r | (1 << WR_BIT);
                buf[k++] = font_color.g;
                buf[k++] = font_color.g | (1 << WR_BIT);
                buf[k++] = font_color.b;
                buf[k++] = font_color.b | (1 << WR_BIT);
            }
            else {
                buf[k++] = back_color.r;
                buf[k++] = back_color.r | (1 << WR_BIT);
                buf[k++] = back_color.g;
                buf[k++] = back_color.g | (1 << WR_BIT);
                buf[k++] = back_color.b;
                buf[k++] = back_color.b | (1 << WR_BIT);
            }
        }
    }   
    
    // Transmit data by DMA
    PlaceImage(current_x, current_y, char_length, FontHeight[current_font], buf);
    
    // Increase x for the next char
    current_x += char_length;
}
// Print string (null-terminated)
void PrintStringLcd(char * str)
{
    int i = 0;
    uint16_t start_x = current_x;
    
    while (str[i] != 0) {
        // Special symbols proceed
        if (IsSpecialSymbol(str[i]))
            ProceedSpecialSymbol(str[i], start_x);
        else
            PrintCharLcd(str[i]);
        
        i++;
    }
    
}
// Print string (null-terminated) and go to the next line
void PrintStringLnLcd(char * str)
{
    int i = 0;
    uint16_t start_x = current_x;
    
    while (str[i] != 0) {
        // Special symbols proceed
        if (IsSpecialSymbol(str[i]))
            ProceedSpecialSymbol(str[i], start_x);
        else
            PrintCharLcd(str[i]);
        
        i++;
    }
    ProceedSpecialSymbol('\n', start_x);
    ProceedSpecialSymbol('\r', start_x);
}
// Print num of chars
void PrintLineLcd(char * str, int num)
{
    int i;
    uint16_t start_x = current_x;
    
    for (i = 0; i < num; i++) {
        // Special symbols proceed
        if (IsSpecialSymbol(str[i]))
            ProceedSpecialSymbol(str[i], start_x);
        else
            PrintCharLcd(str[i]);
    }
}
// Print num of chars and go to the next line
void PrintLineLnLcd(char * str, int num)
{
    int i;
    uint16_t start_x = current_x;
    
    for (i = 0; i < num; i++) {
        // Special symbols proceed
        if (IsSpecialSymbol(str[i]))
            ProceedSpecialSymbol(str[i], start_x);
        else
            PrintCharLcd(str[i]);
    }
    ProceedSpecialSymbol('\n', start_x);
    ProceedSpecialSymbol('\r', start_x);
}
// Recognize '\n' and '\r'
bool IsSpecialSymbol(char c)
{
    return ((c == '\n')||(c == '\r'));
}
// Proceed '\n' and '\r'
void ProceedSpecialSymbol(char c, uint16_t start_x)
{
    if (c == '\r')
        current_x = start_x;
    if (c == '\n')
        current_y -= (FontHeight[current_font] * 3 / 2);
}

