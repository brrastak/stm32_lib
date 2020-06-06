/*
    1. Define encoder pins, configure as floating input
    2. Create enc_t variables
    2. Call CheckEncoder about every 1 ms to update its state
    3. Call GetEncoderValue to find current value
*/

// STM8S103F3
#include "stm8s.h"

// cstd
#include <stdbool.h>

#ifndef __ENCODER_H__
#define __ENCODER_H__


// Encoder
typedef struct
{
    GPIO_TypeDef* a_port;
    int a_pin;
    GPIO_TypeDef* b_port;
    int b_pin;
    int prev_state;     // init by 0
    int cur_val;        // don't care
    int min_val;
    int max_val;
    int step;
}
enc_t;


// Update encoder state, decode it and increase or decrease value
void CheckEncoder(enc_t*);
// Return current value
int GetEncoderValue(enc_t*);
// Set encoder value
void SetEncoderValue(enc_t*, int value);


#endif
