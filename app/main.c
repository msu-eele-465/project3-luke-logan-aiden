#include <msp430.h>
#include <stdbool.h>

int main(void)
{
    
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mdoe to activate
    //pattern_static();                     // Pattern 0
    //pattern_toggle();                     // Pattern 1
    //pattern_up_counter();                 // Pattern 2
    //pattern_in_out();                     // Pattern 3
    //pattern_down_counter();               // Pattern 4
    //pattern_rotate_left();                // Pattern 5
    pattern_0_rotate_right();               // Pattern 6

    
    // Main loop
    while(1){}

    return 0;
}
