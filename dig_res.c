// cstd
#include <stdbool.h>

//user
#include "dig_res.h"
#include "gpio.h"
#include "timer.h"


// Increase/decrease value
void ChangeRes(digres_t* res, int16_t num)
{
    int i;
    
    if (num == 0)
        return;
    
    if (num > 0) {  // increase
    
        // Preparing
        SetPin(res->ud_port, res->ud_pin);
        delay_us(2);
        // Start transmission
        ResetPin(res->cs_port, res->cs_pin);
        delay_us(2);
        
        for (i = 0; i < num; i++) {
        
            // Increase to one step
            ResetPin(res->ud_port, res->ud_pin);
            delay_us(2);
            SetPin(res->ud_port, res->ud_pin);
            delay_us(2);
            
            res->value ++;
            if (res->value == res->max_value)
                break;
        }
        
        // End transmission
        SetPin(res->cs_port, res->cs_pin);
        delay_us(2);
    }
    else {          // decrease
        
        // Preparing
        ResetPin(res->ud_port, res->ud_pin);
        delay_us(2);
        // Start transmission
        ResetPin(res->cs_port, res->cs_pin);
        delay_us(2);
        
        for (i = 0; i > num; i--) {
        
            // Decrease to one step
            SetPin(res->ud_port, res->ud_pin);
            delay_us(2);
            ResetPin(res->ud_port, res->ud_pin);
            delay_us(2);
            
            res->value --;
            if (res->value == 0)    // min value
                break;
        }
        
        // End transmission
        SetPin(res->cs_port, res->cs_pin);
        delay_us(2);
    }
}
// Set value
void SetRes(digres_t* res, uint16_t num)
{
    int16_t dif;
    
    if (num > res->max_value)
        num = res->max_value;
    
    // Number of steps to increase/decrease
    dif = num - res->value;
    
    ChangeRes(res, dif);
}
// Get current value
uint16_t GetRes(digres_t* res)
{
    return res->value;
}

