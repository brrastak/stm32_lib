/*
    1. Define A_PIN and B_PIN, configure as floating input
    2. Call InitEncoder
    3. Call GetEncoder about every 1 ms to get its state
    4. Call ValEncoder to find current value
*/

// cstd
#include <stdbool.h>

#ifndef __ENCODER_H__
#define __ENCODER_H__

// Encoder number values
#define INIT_VAL        1
#define MIN_VAL         1
#define MAX_VAL         8

#define USE_MIN_MAX

// Get encoder state, decode it and increase or decrease value
void GetEncoder(void);
// Return current value
int ValueEncoder(void);

#endif