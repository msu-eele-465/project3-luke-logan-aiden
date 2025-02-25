#include <msp430.h>
#include <stdbool.h>
#include "keypad.h"
#include "status-led.h"
#include "led-bar.h"

// constants
bool locked = true;
int pattern = 10;
volatile int prev_pattern = 10;
int keypad_input;
char test;

int main(void)
{
    
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mdoe to activate

    // init heartbeat LED
    P6DIR |= BIT6;
    P6OUT &= ~BIT6;

    init_LED_bar();
    clear_led_bar();
    init_status_led_timer(&locked_rgb);     // setup led status timer
    __enable_interrupt();                   // Enable Maskable IQR

    while(locked)
    {
        locked = check_unlock();
    }

    set_status_rgb(&unlocked_rgb);

    while(1)
    {
        test = _read_keypad_char();
        keypad_input = input_decide();
        if (keypad_input == 10)
        {
            pattern = prev_pattern;
        }
        else 
        {
            pattern = keypad_input;
        }

    }
}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void)
{
    P6OUT ^= BIT6;
    prev_pattern = pattern_decide(prev_pattern, pattern);
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