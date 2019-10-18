// cstd
#include <stdbool.h>
#include <stdint.h>

// user
#include "MCP4921.h"
#include "SPI.h"

#define AB      (1 << 15)
#define BUF     (1 << 14)
#define GA      (1 << 13)
#define SHDN    (1 << 12)

static uint16_t data =
    AB      * 0 |       // Select       0: A        1: B
    BUF     * 0 |       // Turn input buffer off
    GA      * 0 |       // Select gain  0: 2x       1: 1x
    SHDN    * 1;        // Enable output

void SendDAC(uint16_t num)
{
    data &= 0xf000;
    data |= (num & 0x0fff);
    TransmitSPI(&data, 1);
}

void SelectA(void)
{
    data &= ~AB;
}
void SelectB(void)
{
    data |= AB;
}
void InputBufferOn(void)
{
    data &= ~BUF;
}
void InputBufferOff(void)
{
    data |= BUF;
}
void OutputGain1(void)
{
    data |= GA;
}
void OutputGain2(void)
{
    data &= ~GA;
}
void OuputOn(void)
{
    data |= SHDN;
}
void OutputOff(void)
{
    data &= ~SHDN;
}