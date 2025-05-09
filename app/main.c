#include <msp430.h>
#include <stdbool.h>
#include "keypad.h"
#include "status-led.h"

// constants
bool locked = true;

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
    //pattern_0_rotate_right();             // Pattern 6
    //pattern_fill_left();                  // Pattern 7


    init_status_led_timer(&locked_rgb);     // setup led status timer
    __enable_interrupt();                   // Enable Maskable IQR

    while(locked)
    {
        locked = check_unlock();
    }

    set_status_rgb(&unlocked_rgb);

    while(true)
    {
        _read_keypad_char();
    }
}

#pragma vector = TIMER3_B0_VECTOR
__interrupt void ISR_CRR0(void)
{
    status_led_timer_ccr0();
}

#pragma vector = TIMER3_B1_VECTOR
__interrupt void ISR_higher_CCR(void)
{
    TB3_ISR_call(TB3IV);
}