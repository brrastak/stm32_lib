/*
    Define and configure STEP_A_PIN, STEP_B_PIN, STEP_C_PIN, STEP_D_PIN
    Colours:
        A: black
        C: green

        B: red
        D: blue
*/

// cstd
#include <stdint.h>
#include <stdbool.h>

#ifndef __STEPPER_MOTOR_H__
#define __STEPPER_MOTOR_H__

// Types
// Stepper control mode
typedef enum
{
    wave_mode,
    fullstep_mode,
    halfstep_mode
}
stepper_mode_t;

// Functions
// Set current control mode
void SetStepperControlMode(stepper_mode_t);
// Set outputs state depending on current control mode
void DoNextStep(void);
// Start stepping from the beginning
void ResetStep(void);


#endif
