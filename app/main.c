#include <msp430.h>
#include <stdbool.h>

int main(void)
{
    
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mdoe to activate
    //pattern_static();
    //pattern_toggle();
    //pattern_up_counter();
    //pattern_in_out();
    //pattern_down_counter();
    pattern_rotate_left();

    
    // Main loop
    while(1){}

    return 0;
}
