// cstd
#include <stdbool.h>
#include <stdint.h>

#ifndef __MCP4921_H__
#define __MCP4921_H__

void SendDAC(uint16_t);

// Configuration bits for DAC
// Select A or B DAC in dual IC
void SelectA(void);
void SelectB(void);
// Input buffer on/off
void InputBufferOn(void);
void InputBufferOff(void);
// Select output gain = 1 or 2
void OutputGain1(void);
void OutputGain2(void);
// Output on/off
void OuputOn(void);
void OutputOff(void);

#endif