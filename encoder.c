// cstd
#include <stdbool.h>

//user
#include "encoder.h"
#include "main.h"
#include "gpio.h"

// Local variables
static int prev_state = 0;
static int cur_state;

static int value = INIT_VAL;

static const int state_decode_table[2][2] =
{   2, 3,
    1, 0
};
static const int dir_decode_table[4][4] =
{   0,  1,  0, -1,
    0,  0,  0,  0,
    0,  0,  0,  0,
    0,  0,  0,  0
};

// Read A and B pin values and translate into number (0-3)
int read_pins(void);

void GetEncoder(void)
{    
    cur_state = read_pins();
    
    value += dir_decode_table[prev_state][cur_state];
    prev_state = cur_state;
    
    #ifdef USE_MIN_MAX
    
    if (value < MIN_VAL)
        value = MIN_VAL;
    if (value > MAX_VAL)
        value = MAX_VAL;
    
    #endif 
}
int ValueEncoder(void)
{
    return value;
}
int read_pins(void)
{
    int A, B;
    
    A = ( PinState(PORTPIN(A))) ? 1 : 0;
    B = ( PinState(PORTPIN(B))) ? 1 : 0;
    
    return state_decode_table[A][B];
}