// STM32F103
#include "stm32f10x.h"

//user
#include "iwdg.h"

// Key register values
// Enable watchgog
#define KEY_ENABLE      0xCCCC
// Refresh watchdog
#define KEY_REFRESH     0xAAAA
// Access to control registers
#define KEY_ACCESS      0x5555


// Init watchdog timer
void InitIwdg(void)
{
    // Enable
    IWDG->KR = KEY_ENABLE;
    // Set refresh time
    IWDG->KR = KEY_ACCESS;
    IWDG->PR = 5;           // f = 40kHz / 128
    IWDG->RLR = 10;
    // Refresh
    IWDG->KR = KEY_REFRESH;
}
// Reset watchdog timer
void ResetIwdg(void)
{
    IWDG->KR = KEY_REFRESH;
}

