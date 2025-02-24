/*

Luke Johnson microcontroller application project 3.

This file is a header that includes all declarations for using the LED Bar. All pins on Port 1 will be used to operate the LED Bar.

Pins: uC: P1.i <-> i+1 LED Bar

Constants:
    - integer counter
    - integer down 256 counter1

Functions:
    - _init_LED_bar()   to initialize port1 pins 
    - __pattern0()      not present here, hardcoded in led_pattern.c
    - __pattern1()      toggle all LEDs
    - __pattern2()      256 bit binary up counter
    - __pattern3()      256 bit binary down counter 
    - __pattern4()      in and out pattern
    - __pattern5()      rotate left pattern
    - __pattern6()      rotate 0 right pattern
    - __pattern7()      fill left

*/

#ifndef _LED-BAR_H
#define _LED-BAR_H

#include <msp430.h>
#include <stdbool.h>

int counter = 0;

inline void _decrease_speed(void) {
        // if "A" is pressed decrease cycle speed by 0.25s
        return;
}

inline void _increase_speed(void) {
        // if "B" is pressed increase cycle speed by 0.25s
        return;
}

inline void init_LED_bar(void) {
    P1DIR |= BIT0; // Set Outputs
    P1DIR |= BIT1;
    P1DIR |= BIT2;
    P1DIR |= BIT3;
    P1DIR |= BIT4;
    P1DIR |= BIT5;
    P1DIR |= BIT6;
    P1DIR |= BIT7;

    // Setup Timer
    TB0CTL |= TBCLR;    // clear timers & dividers
    TB0CTL |= TBSSEL__ACLK; // Source = ACLK
    TB0CTL |= MC__UP;   // Mode=UP
    TB0CCR0 = 32769;    // CCR0=32769

    // Setup Timer Compare IRQ
    TB0CCTL0 &= ~CCIFG;   // Clear CCR0 Flag
    TB0CCTL0 |= CCIE;     // Enable TB0 CCR0 Overflow IRQ
    return;
}

inline void clear_led_bar(void)
{
    P1OUT &= ~BIT0;  // Toggle LED 1
    P1OUT &= ~BIT1;  // Toggle LED 2
    P1OUT &= ~BIT2;  // Toggle LED 3
    P1OUT &= ~BIT3;  // Toggle LED 4
    P1OUT &= ~BIT4;  // Toggle LED 5
    P1OUT &= ~BIT5;  // Toggle LED 6
    P1OUT &= ~BIT6;  // Toggle LED 7
    P1OUT &= ~BIT7;  // Toggle LED 8
}

inline void __pattern0(void) { // Pattern 0

    P1OUT |= BIT0; // Set values 
    P1OUT &= ~BIT1;
    P1OUT |= BIT2;
    P1OUT &= ~BIT3;
    P1OUT |= BIT4;
    P1OUT &= ~BIT5;
    P1OUT |= BIT6;
    P1OUT &= ~BIT7;

    TB0CCTL0 &= ~CCIFG; //Clear CCR0 Flag
    return;
}
inline void __pattern1(void) {
    P1OUT ^= BIT0;  // Toggle LED 1
    P1OUT ^= BIT1;  // Toggle LED 2
    P1OUT ^= BIT2;  // Toggle LED 3
    P1OUT ^= BIT3;  // Toggle LED 4
    P1OUT ^= BIT4;  // Toggle LED 5
    P1OUT ^= BIT5;  // Toggle LED 6
    P1OUT ^= BIT6;  // Toggle LED 7
    P1OUT ^= BIT7;  // Toggle LED 8

    TB0CCTL0 &= ~CCIFG; //Clear CCR0 Flag
    return;
}

inline void __pattern2(void) {
    (counter)++; 
    P1OUT = counter;
    
    TB0CCTL0 &= ~CCIFG; //Clear CCR0 Flag
    return;
}

inline void __pattern3(void) {
    (counter)++;

    switch(counter) {
        case 1: P1OUT |= BIT3;
                P1OUT |= BIT4;
                break;
        case 2: P1OUT &= ~BIT3;
                P1OUT &= ~BIT4;
                P1OUT |= BIT2;
                P1OUT |= BIT5;
                break;
        case 3: P1OUT &= ~BIT2;
                P1OUT &= ~BIT5;
                P1OUT |= BIT1;
                P1OUT |= BIT6;
                break;
        case 4: P1OUT &= ~BIT1;
                P1OUT &= ~BIT6;
                P1OUT |= BIT0;
                P1OUT |= BIT7;
                break;
        case 5: P1OUT &= ~BIT0;
                P1OUT &= ~BIT7;
                P1OUT |= BIT1;
                P1OUT |= BIT6;
                break;
        case 6: P1OUT &= ~BIT1;
                P1OUT &= ~BIT6;
                P1OUT |= BIT2;
                P1OUT |= BIT5;
                break;
        case 7: P1OUT &= ~BIT2;
                P1OUT &= ~BIT5;
                P1OUT |= BIT3;
                P1OUT |= BIT4;
                counter = 0;
                break;
    }

    
    TB0CCTL0 &= ~CCIFG; //Clear CCR0 Flag
    return;
}

inline void __pattern4(void) {
    //int counter1 = 256; do this somewhere else
    (counter)--;
    P1OUT = counter;
    
    TB0CCTL0 &= ~CCIFG; //Clear CCR0 Flag
    return;

}

inline void __pattern5(void) {
    (counter)++;
    switch(counter) {
        case 1: P1OUT |= BIT7;
                P1OUT &= ~BIT0;
                break;
        case 2: P1OUT |= BIT6;
                P1OUT &= ~BIT7;
                break;
        case 3: P1OUT |= BIT5;
                P1OUT &= ~BIT6;
                break;
        case 4: P1OUT |= BIT4;
                P1OUT &= ~BIT5;
                break;
        case 5: P1OUT |= BIT3;
                P1OUT &= ~BIT4;
                break;
        case 6: P1OUT |= BIT2;
                P1OUT &= ~BIT3;
                break;
        case 7: P1OUT |= BIT1;
                P1OUT &= ~BIT2;
                break;
        case 8: P1OUT |= BIT0;
                P1OUT &= ~BIT1;
                counter = 0;
                break;
    }
    
    TB0CCTL0 &= ~CCIFG; //Clear CCR0 Flag
    return;
}

inline void __pattern6(void) {
    (counter)++;
    switch(counter) {
        case 1: P1OUT &= ~BIT1;
                P1OUT |= BIT0;
                break;
        case 2: P1OUT &= ~BIT2;
                P1OUT |= BIT1;
                break;
        case 3: P1OUT &= ~BIT3;
                P1OUT |= BIT2;
                break;
        case 4: P1OUT &= ~BIT4;
                P1OUT |= BIT3;
                break;
        case 5: P1OUT &= ~BIT5;
                P1OUT |= BIT4;
                break;
        case 6: P1OUT &= ~BIT6;
                P1OUT |= BIT5;
                break;
        case 7: P1OUT &= ~BIT7;
                P1OUT |= BIT6;
                break;
        case 8: P1OUT &= ~BIT0;
                P1OUT |= BIT7;
                counter = 0;
                break;
    }
    
    TB0CCTL0 &= ~CCIFG; //Clear CCR0 Flag
    return;
}

int inline __pattern7(void) {
    (counter)++;
    switch(counter) {
        case 1: P1OUT |= BIT6;
                break;
        case 2: P1OUT |= BIT5;
                break;
        case 3: P1OUT |= BIT4;
                break;
        case 4: P1OUT |= BIT3;
                break;
        case 5: P1OUT |= BIT2;
                break;
        case 6: P1OUT |= BIT1;
                break;
        case 7: P1OUT |= BIT0;
                break;
        case 8: P1OUT &= ~BIT0;
                P1OUT &= ~BIT1;
                P1OUT &= ~BIT2;
                P1OUT &= ~BIT3;
                P1OUT &= ~BIT4;
                P1OUT &= ~BIT5;
                P1OUT &= ~BIT6;
                P1OUT |= BIT7;
                counter = 0;
    }
    
    TB0CCTL0 &= ~CCIFG; //Clear CCR0 Flag
    return;
}

inline int pattern_decide(int prev_pattern, int pattern)
{
    if (pattern == prev_pattern)
    {
        switch (pattern)
        {
            case 0:
                __pattern0();
                break;
            case 1:
                __pattern1();
                break;
            case 2:
                __pattern2();
                break;
            case 3:
                __pattern3();
                break;
            case 4:
                __pattern4();
                break;
            case 5:
                __pattern5();
                break;
            case 6:
                __pattern6();
                break;
            case 7:
                __pattern7();
                break;

        }
    }
    else 
    {
        clear_led_bar();
        if (pattern == 4)
        {
            counter = 256;
        }
        else 
        {
            counter = 0;
        }

        switch (pattern)
        {
            case 0:
                __pattern0();
                break;
            case 1:
                __pattern1();
                break;
            case 2:
                __pattern2();
                break;
            case 3:
                __pattern3();
                break;
            case 4:
                __pattern4();
                break;
            case 5:
                __pattern5();
                break;
            case 6:
                __pattern6();
                break;
            case 7:
                __pattern7();
                break;

        }
    }
    return pattern;
}

#endif 