// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>
#include <stdint.h>

//user
#include "LCD_8bit.h"
#include "main.h"
#include "GPIO.h"
#include "timer.h"
#include "debug_led.h"
#include "UART.h"

// Communication cycle state
typedef enum
{
    stop_state,
    start_reading_state,
    start_writing_state,
    end_reading_state,
    end_writing_state
}
com_state_t;

// Local variables
// Communication cycle state
static com_state_t com_state = stop_state;
// Reading enabled (for MCU pins safety)
static bool can_read = false;
// Data
static uint8_t* transmit_buf;
static uint8_t* receive_buf;
static uint8_t command_buf[1];
// Number of data
static int to_transmit = 0;
static int to_receive = 0;
// Flags
static volatile bool transmitted = true;
static volatile bool received = true;

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
// One byte reading/writing
void StartReading(void);
void StartWriting(void);
void EndReading(void);
void EndWriting(void);
// Physical level
void SetLineState(uint8_t data);
uint8_t GetLineState(void);
// Stop communication process
void StopCommunication();

// Receiving and transmitting process handled by timer
void HandleLcd()
{
    switch (com_state)
    {
    case stop_state:
        break;
    case start_reading_state:
        com_state = end_reading_state;
        StartReading();
        break;
    case start_writing_state:
        com_state = end_writing_state;
        StartWriting();
        break;
    case end_reading_state:
        com_state = start_reading_state;
        EndReading();
        break;
    case end_writing_state:
        com_state = start_writing_state;
        EndWriting();
        break;
    }
}
// Stop communication process
void StopCommunication()
{
    com_state = stop_state;
}
// Start communication
void TransmitLcdData(uint8_t * buf, int num)
{
    transmit_buf = buf;
    to_transmit = num;
    transmitted = false;
    
    com_state = start_writing_state;
    
    InitWriting();
    SetDataMode();
}
void TransmitLcdCommand(uint8_t command)
{
    command_buf[0] = command;
    transmit_buf = command_buf;
    to_transmit = 1;
    transmitted = false;
    
    com_state = start_writing_state;
    
    InitWriting();
    SetCommandMode();
}
void ReceiveLcdData(uint8_t * buf, int num)
{
    receive_buf = buf;
    to_receive = num;
    received = false;
    
    com_state = start_reading_state;    
    
    InitReading();
    SetDataMode();
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
}
// Reset signal
void ResetLcd()
{
    ResetPin(RST_PIN);
    delay_ms(10);
    SetPin(RST_PIN);
}
// Communication state
bool IsLcdReceived()
{
    return received;
}
bool IsLcdTransmitted()
{
    return transmitted;
}
// One byte reading/writing
void StartReading()
{
    SetRD();
}
void StartWriting()
{
    SetWR();
    
    SetLineState(transmit_buf[0]);
    transmit_buf++;
    to_transmit--;
}
void EndReading()
{
    // Reading
    ResetRD();
    
    receive_buf[0] = GetLineState();
    receive_buf++;
    to_receive--;

    if (to_receive == 0)    // end communication process
    {
        StopCommunication();
        received = true;
    }
}
void EndWriting()
{
    // Writing
    ResetWR();

    if (to_transmit == 0)    // end communication process
    {
        StopCommunication();
        transmitted = true;
    }
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
        SetGpioMode(PARALLEL_PORT, i, PIN_MODE_2MHZ_OPP);
    
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
// Set data line and reset strobe
void SetLineState(uint8_t data)
{
    SetMulPin(PARALLEL_PORT, (0x000000ff & data));
    ResetMulPin(PARALLEL_PORT, (0x000000ff & ~data));
}
// Reset strobe and get data line
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
