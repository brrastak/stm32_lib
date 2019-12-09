/*
    1. Define PARALLEL_PORT : D0-D7 in one port
    2. Define RD_PIN, WR_PIN, RS_PIN, RST_PIN
        RD - read strobe (on rising edge)
        WR - write strobe (on rising edge)
        RS - 0: command; 1: data
        RST - reset (active low)
    3. Call InitLcd();
    4. Declare buffer variable
        set BUF_SIZE and *buf at LCD_8bit.c

    Start pixel coordinate = (0, 0)
*/

// cstd
#include <stdbool.h>
#include <stdint.h>

#ifndef __LCD_8BIT_H__
#define __LCD_8BIT_H__

// LCD dimensions in pixels
#define LCD_MAX_X                               480
#define LCD_MAX_Y                               320
// LCD display command codes
#define LCD_COMMAND_DISPLAY_ON                  0x29
#define LCD_COMMAND_SLEEP_OUT                   0x11
#define LCD_COMMAND_MEMORY_WRITE                0x2C
#define LCD_COMMAND_COLUMN_ADDRESS_SET          0x2A
#define LCD_COMMAND_PAGE_ADDRESS_SET            0x2B
#define LCD_COMMAND_INTERFACE_PIXEL_FORMAT      0x3A
#define LCD_COMMAND_MADCTL                      0x36    // Memory access control
// LCD command parameters
#define LCD_16BIT_COLOR                         0x55
// Bit mask for memory access control command
#define LCD_MY                                  0x80
#define LCD_MX                                  0x40
#define LCD_MV                                  0x20
#define LCD_ML                                  0x10
#define LCD_BGR                                 0x08
#define LCD_MH                                  0x04


typedef struct
{
    uint16_t r;
    uint16_t g;
    uint16_t b;
}
rgb_t;

// Init LCD
void InitLcd(void);
// Reset signal
void ResetLcd(void);

// Start communication
// Using DMA
void FillRectangle(uint16_t x, uint16_t y, uint16_t dx, uint16_t dy, rgb_t color);
// Image must be prepared: uint16_t = uint8_t data | WR_BIT; RGB
void PlaceImage(uint16_t x, uint16_t y, uint16_t dx, uint16_t dy, uint16_t* buf);
// Using delay_us
void TransmitLcdCommand(uint8_t command);
void TransmitLcdData(uint8_t data);
void ReceiveLcdData(uint8_t * buf, int num);

// Communication state
bool IsLcdTransmitted(void);

// Convert RGB formst color into 16-bit format color
// 15:0 = RRRRRGGG GGGBBBBB
uint16_t PackRgbColor(uint8_t red, uint8_t green, uint8_t blue);

#endif
