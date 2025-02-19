/*

Logan Graham microcontroller application project 3.

This header file establishes everything needed to run the status RGB LED.

Pins: P2.0 <-> R, P2.1 <-> G, P2.2 <-> B, GND <-> annode

Structures:

RGB: members are the RGB Values

*/

#ifndef _STATUS_LED_H
#define _STATUS_LED_H

#include <msp430.h>

// Constants defitions

#define _BITS0TO3 7

// Structures definition
struct RGB
{
    int red;
    int green;
    int blue;
};

//typedef struct rgb RGB

// RGB value definitions

struct RGB locked_rgb = {196, 62, 29};

// Function defitions

void init_status_led_timer(struct RGB* init_rgb)
{
    // Set RGB pins as outputs
    P2DIR |= _BITS0TO3;                 // set P2.0-3 to outputs
    P2OUT &= ~_BITS0TO3;                // clear outputs P2.0-3
    
    // Set up timer
    TB3CTL |= TBCLR;                    // clear timers & dividers
    TB3CTL |= TBSSEL__SMCLK;            // source = SMCLK
    TB3CTL |= MC__UP;                   // set count up
    TB3CTL |= ID__1;                    // set divider 1 to 1
    TB3CTL |= CNTL_0;                   // 16-bit clock length

    // set compares 0-3
    TB3CCR0 = 1020;                     // set period to approx 1 ms
    TB3CCTL0 |= CCIE;                   // enable compare interrupt
    TB3CCTL0 &= ~CCIFG;                 // clear interrupt flag

    TB3CCR1 = 4*(init_rgb->red);        // set CCR1 to red duty cycle
    TB3CCTL1 |= CCIE;                   // enable compaxxsre interrupt
    TB3CCTL1 &= ~CCIFG;                 // clear interrupt flag

    TB3CCR2 = 4*(init_rgb->green);     // set CCR2 to green duty cycle
    TB3CCTL2 |= CCIE;                   // enable compare interrupt
    TB3CCTL2 &= ~CCIFG;                 // clear interrupt flag

    TB3CCR3 = 4*(init_rgb->blue);       // set CCR3 to blue duty cycle
    TB3CCTL3 |= CCIE;                   // enable compare interrupt
    TB3CCTL3 &= ~CCIFG;                 // clear interrupt flag
    return;
}

void status_led_timer_ccr0(void)
{
    // set all colors high
    P2OUT |= _BITS0TO3;
    TB3CCTL0 &= ~CCIFG;                 // clear interrupt flag
    return;
}

void _status_led_timer_ccr1(void)
{
    // set red color to low
    P2OUT &= ~BIT0;
    TB3CCTL1 &= ~CCIFG;                 // clear interrupt flag
    return;
}

void _status_led_timer_ccr2(void)
{
    // set red color to low
    P2OUT &= ~BIT1;
    TB3CCTL2 &= ~CCIFG;                 // clear interrupt flag
    return;
}

void _status_led_timer_ccr3(void)
{
    // set red color to low
    P2OUT &= ~BIT2;
    TB3CCTL3 &= ~CCIFG;                 // clear interrupt flag
    return;
}

void TB3_ISR_call(int IV)
{
    switch (IV) 
    {
        case 2:
            _status_led_timer_ccr1();
            return;

        case 4:
            _status_led_timer_ccr2();
            return;

        case 6:
            _status_led_timer_ccr3();
            return;
    }
}


#endif
