#include <msp430.h>
#include <stdbool.h>
#include "keypad.h"

// constatns
bool locked = true;

int main(void)
{
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    
    // Disable the GPIO power-on default high-impedance mdoe to activate
    // previously configure port settings
    PM5CTL0 &= ~LOCKLPM5;

    while(locked)
    {
        locked = check_unlock();
    }

    while(true)
    {
        _read_keypad_char();
    }
}
