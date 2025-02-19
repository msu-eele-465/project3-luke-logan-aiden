#include <msp430.h>
#include <stdbool.h>
#include "keypad.h"
#include "status-led.h"

// constants
bool locked = true;

// set up status LED


int main(void)
{
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    
    // Disable the GPIO power-on default high-impedance mdoe to activate
    // previously configure port settings
    PM5CTL0 &= ~LOCKLPM5;

    init_status_led_timer(&locked_rgb);     // setup led status timer
    __enable_interrupt();                   // Enable Maskable IQR

    while(locked)
    {
        locked = check_unlock();
    }

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