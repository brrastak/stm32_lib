// cstd
#include <stdbool.h>

//user
#include "encoder.h"
#include "main.h"
#include "gpio.h"


// Data do decode encoder state
static const int state_decode_table[2][2] =
{   2, 3,
    1, 0
};
static const int dir_decode_table[4][4] =
{   0, -1,  0,  1,
    0,  0,  0,  0,
    0,  0,  0,  0,
    0,  0,  0,  0
};

// Read A and B pin values and translate into number (0-3)
int read_pins(enc_t*);

void CheckEncoder(enc_t* enc)
{    
    int cur_state;
    
    // Get current encoder state
    cur_state = read_pins(enc);
    
    // Change value if rotation detected
    enc->cur_val += (dir_decode_table[enc->prev_state][cur_state])*(enc->step);
    enc->prev_state = cur_state;
    
    // Value limits checking
    if (enc->cur_val < enc->min_val)
        enc->cur_val = enc->min_val;
    if (enc->cur_val > enc->max_val)
        enc->cur_val = enc->max_val;

}
int GetEncoderValue(enc_t* enc)
{
    return enc->cur_val;
}
void SetEncoderValue(enc_t* enc, int value)
{
    enc->cur_val = value;
}
int read_pins(enc_t* enc)
{
    int A, B;
    
    A = ( GetPinState(enc->a_port, enc->a_pin)) ? 1 : 0;
    B = ( GetPinState(enc->b_port, enc->b_pin)) ? 1 : 0;
    
    return state_decode_table[A][B];
}