// cstd
#include <stdbool.h>

/*  have to define
    KEYSCL_PORT, KEYSCL_PIN
    KEYSDA_PORT, KEYSDA_PIN
    and set KEYSCL_PIN to 1
*/

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

// keys numbered from 1 to 16
int KeyPressed(void);       // what key is pressed? (if none returns 0)
bool KeyState(int num);     // is key number "num" pressed?
void KeyCheck(void);        // run about every 0,5ms ( =T )
// Time for all keyboard check = T * 4 * 16

#endif