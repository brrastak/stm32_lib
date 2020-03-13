// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

//user
#include "stepper_motor.h"
#include "main.h"
#include "gpio.h"

// Local types
// State of each of four outputs for control stepper motor
typedef enum
{
    l,          // low voltage
    h           // high voltage
}
output_state_t;
// Outputs
typedef struct
{
    output_state_t a;
    output_state_t c;
    output_state_t b;
    output_state_t d;
}
output_t;

// Local variables
// Current stepper control mode
static stepper_mode_t current_mode = fullstep_mode;
// Step counter
static int current_step = 0;
// Full-step mode steps: voltage level (low or high) for each output and each step
static const output_t fullstep_steps[4] =
{
    {h, l, h, l},
    {l, h, h, l},
    {l, h, l, h},
    {h, l, l, h}
};

// Local function prototypes
// Set output state depending on current step
void SetOutput(const output_t * step_mode, int step);

// Set current control mode
void SetStepperControlMode(stepper_mode_t new_mode)
{
    current_mode = new_mode;
}
// Set outputs state depending on current control mode
void DoNextStep(void)
{
    switch (current_mode)
    {
    case fullstep_mode:
        SetOutput(fullstep_steps, current_step);
        break;
    }
    
    current_step++;
    if (current_step > 3)
        current_step = 0;
}
// Start stepping from the beginning
void ResetStep(void)
{
    
}
// Set output state depending on current step
void SetOutput(const output_t * step_mode, int step)
{
    if (step_mode[step].a == h)
        SetPin(STEP_A_PIN);
    else
        ResetPin(STEP_A_PIN);
    if (step_mode[step].c == h)
        SetPin(STEP_C_PIN);
    else
        ResetPin(STEP_C_PIN);
    if (step_mode[step].b == h)
        SetPin(STEP_B_PIN);
    else
        ResetPin(STEP_B_PIN);
    if (step_mode[step].d == h)
        SetPin(STEP_D_PIN);
    else
        ResetPin(STEP_D_PIN);
}

