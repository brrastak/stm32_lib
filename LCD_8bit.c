
// cstd
#include <stdbool.h>
#include <stdint.h>

//user
#include "LCD_8bit.h"
#include "main.h"
#include "GPIO.h"
#include "timer.h"
#include "DMA.h"

// Buffer for DMA images
// must be multiple of 6
#define BUF_SIZE    DMA_BUF_SIZE
static uint16_t * buf = dma_buf;

// Local variables
// Reading enabled (for MCU pins safety)
static bool can_read = false;


// Local functions
// WR and RD lines to default state
void ResetWR(void);
void ResetRD(void);
// WR and RD lines to ready-to-read state
void SetWR(void);
void SetRD(void);
// Data/command mode switch
void SetCommandMode(void);
void SetDataMode(void);
// Init GPIO pins in suitable mode
void InitReading(void);
void InitWriting(void);
// Physical level
void SetLineState(uint8_t data);
uint8_t GetLineState(void);
// Set start coordinats for rectangle and get number of pixels to written
uint32_t SetCoordGetNum(uint16_t x, uint16_t y, uint16_t dx, uint16_t dy);
// Wait for the end of DMA transmission
void WaitEndTransmission(void);


// Start communication
// Using DMA
void FillRectangle(uint16_t x, uint16_t y, uint16_t dx, uint16_t dy, rgb_t color)
{
    int i;
    uint32_t num;
    uint16_t buf_size;
    
    WaitEndTransmission();
    
    // Set coordinats
    num = SetCoordGetNum(x, y, dx, dy);
    num *= 6;   // 6 bytes for one pixel
    
    // Size of buffer to be filled by color
    if (num < BUF_SIZE)
        buf_size = num;
    else
        buf_size = BUF_SIZE;
    // Three color components and value of strobe - WR PIN
    for (i = 0; i < buf_size; i+=6) {
        buf[i] = color.r;
        buf[i+1] = color.r | (1 << WR_BIT);
        buf[i+2] = color.g;
        buf[i+3] = color.g | (1 << WR_BIT);
        buf[i+4] = color.b;
        buf[i+5] = color.b | (1 << WR_BIT);
    }
    
    // Transmitting
    TransmitLcdCommand(LCD_COMMAND_MEMORY_WRITE);
    
    SetDataMode();
    TransmitDma(buf, BUF_SIZE, num);
}
void PlaceImage(uint16_t x, uint16_t y, uint16_t dx, uint16_t dy, uint16_t* buf)
{
    uint32_t num;
    
    WaitEndTransmission();
    
    // Set coordinats
    num = SetCoordGetNum(x, y, dx, dy);
    num *= 6;   // 6 bytes for one pixel
    
    // Transmitting
    TransmitLcdCommand(LCD_COMMAND_MEMORY_WRITE);
    
    SetDataMode();
    TransmitDma(buf, num, num);
}
void TransmitLcdData(uint8_t data)
{
    WaitEndTransmission();
    
    // Configure
    InitWriting();
    SetDataMode();
    
    // Start strobe
    SetWR();
    SetLineState(data);
    
    delay_us(1);
    
    // End strobe
    ResetWR();
}
void TransmitLcdCommand(uint8_t command)
{
    WaitEndTransmission();
    
    // Configure
    InitWriting();
    SetCommandMode();
    
    // Start strobe
    SetWR();
    SetLineState(command);
    
    delay_us(1);
    
    // End strobe
    ResetWR(); 
}
void ReceiveLcdData(uint8_t * buf, int num)
{
    WaitEndTransmission();
    
    // Configure
    InitReading();
    SetDataMode();
    
    int i;
    for (i = 0; i < num; i++) {
        // Start strobe
        SetRD();
        
        delay_us(1);
        
        // End strobe
        ResetRD();
        buf[i] = GetLineState();
    }
      
}
// Init LCD
void InitLcd()
{
    InitWriting();  // by default
    
    ResetWR();
    ResetRD();
    SetPin(RST_PIN);
    delay_ms(150);

    ResetLcd();
    delay_ms(150);
    
    // Turn display on
    TransmitLcdCommand(LCD_COMMAND_SLEEP_OUT);
    delay_ms(5);
    TransmitLcdCommand(LCD_COMMAND_DISPLAY_ON);
    
    // Memory access control
    TransmitLcdCommand(LCD_COMMAND_MADCTL);
    TransmitLcdData(
        LCD_MY  * 1 |   // row address order
        LCD_MX  * 0 |   // column address order
        LCD_MV  * 0 |   // row/column exchange
        LCD_ML  * 0 |   // vertical refresh order
        LCD_BGR * 1 |   // RGB-BGR order
        LCD_MH  * 0     // horizontal refresh order
    );
    
    // Set 16-bit color mode
    //TransmitLcdCommand(LCD_COMMAND_INTERFACE_PIXEL_FORMAT);
    //TransmitLcdData(LCD_16BIT_COLOR);
}
// Reset signal
void ResetLcd()
{
    ResetPin(RST_PIN);
    delay_ms(10);
    SetPin(RST_PIN);
}
// Communication state
bool IsLcdTransmitted()
{
    return TransmittedDma();
}
// Read/write switch - init GPIO
void InitReading()
{
    int i;
    for (i = 0; i < 8; i++)
        SetGpioMode(PARALLEL_PORT, i, PIN_MODE_IFLOAT);
    
    can_read = true;
}
void InitWriting()
{
    int i;
    for (i = 0; i < 8; i++)
        SetGpioMode(PARALLEL_PORT, i, PIN_MODE_10MHZ_OPP);
    
    can_read = false;
}
// 1-st stage of writing
void SetWR()
{
    ResetPin(WR_PIN);
}
// 1-st stage of reading
void SetRD()
{
    if (can_read == false)  // pin protection
        return;
    
    ResetPin(RD_PIN);
}
// 2-nd stage of writing
void ResetWR()
{
    SetPin(WR_PIN);
}
// 2-nd stage of reading
void ResetRD()
{
    SetPin(RD_PIN);
}
// Set data line
void SetLineState(uint8_t data)
{
    SetMulPin(PARALLEL_PORT, (0x000000ff & data));
    ResetMulPin(PARALLEL_PORT, (0x000000ff & ~data));
}
// Get data line
uint8_t GetLineState()
{
    return (PARALLEL_PORT->IDR);
}
// Data/command switch
void SetCommandMode(void)
{
    ResetPin(RS_PIN);
}
void SetDataMode(void)
{
    SetPin(RS_PIN);
}
// Convert RGB formst color into 16-bit format color
uint16_t PackRgbColor(uint8_t red, uint8_t green, uint8_t blue)
{
    uint16_t res;
    
    res = (red & 0x1F);
    res <<= 6;
    res += (green & 0x1F);
    res <<= 5;
    res += (blue & 0x1F);
    
    return res;
}
uint32_t SetCoordGetNum(uint16_t x, uint16_t y, uint16_t dx, uint16_t dy)
{
    uint32_t start_x, start_y, end_x, end_y;
    
    // Control of coordinats accuracy
    // Start x
    if (x < LCD_MAX_X)
        start_x = x;
    else
        start_x = 0;
    // Start y
    if (y < LCD_MAX_Y)
        start_y = y;
    else
        start_y = 0;
    // End x
    if (x + dx - 1 < LCD_MAX_X)
        end_x = x + dx - 1;
    else
        end_x = LCD_MAX_X;
    // End y
    if (y + dy - 1 < LCD_MAX_Y)
        end_y = y + dy - 1;
    else
        end_y = LCD_MAX_Y;

    // Set coordinats
    // x
    TransmitLcdCommand(LCD_COMMAND_PAGE_ADDRESS_SET);
    TransmitLcdData(start_x >> 8);
    TransmitLcdData(start_x);
    TransmitLcdData(end_x >> 8);
    TransmitLcdData(end_x);
    // y
    TransmitLcdCommand(LCD_COMMAND_COLUMN_ADDRESS_SET);
    TransmitLcdData(start_y >> 8);
    TransmitLcdData(start_y);
    TransmitLcdData(end_y >> 8);
    TransmitLcdData(end_y);
    
    // Get number
    return (dx * dy);
}
// Wait for the end of DMA transmission
void WaitEndTransmission()
{
    while (! TransmittedDma())
        ;
}

