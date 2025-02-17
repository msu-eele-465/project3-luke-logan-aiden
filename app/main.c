#include <msp430.h>
#include <stdbool.h>
#include "keypad.h"

int output;

int main(void)
{
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    
    // Disable the GPIO power-on default high-impedance mdoe to activate
    // previously configure port settings
    PM5CTL0 &= ~LOCKLPM5;

    while(true)
    {
        output = _read_keypad_char();
    }
}
