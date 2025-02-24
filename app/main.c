#include <msp430.h>
#include <stdbool.h>
#include <RGB.h>

int main(void)
{
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    
    // Disable the GPIO power-on default high-impedance mdoe to activate
    // previously configure port settings
    PM5CTL0 &= ~LOCKLPM5;

    while(true)
    {
    }
}


#pragma vector = TIMER1_B0_VECTOR
__interrupt void ISR_T1B0(void){
    cycleColors();
}