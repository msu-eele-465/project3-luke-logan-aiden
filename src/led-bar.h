/*

Luke Johnson microcontroller application project 3.

This file is a header that includes all declarations for using the LED Bar. All pins on Port 1 will be used to operate the LED Bar.

Pins: uC: P1.i <-> i+1 LED Bar

Constants:
    - 
    - 

Functions:
    -

*/

#ifndef _LED-BAR_H
#define _LED-BAR_H

#include <msp430.h>
#include <stdbool.h>

inline int _init_LED_bar(void) {
    P1DIR |= BIT0; // Set Outputs
    P1DIR |= BIT1;
    P1DIR |= BIT2;
    P1DIR |= BIT3;
    P1DIR |= BIT4;
    P1DIR |= BIT5;
    P1DIR |= BIT6;
    P1DIR |= BIT7;
}

inline int __pattern1(void) {
    P1OUT ^= BIT0;  // Toggle LED 1
    P1OUT ^= BIT1;  // Toggle LED 2
    P1OUT ^= BIT2;  // Toggle LED 3
    P1OUT ^= BIT3;  // Toggle LED 4
    P1OUT ^= BIT4;  // Toggle LED 5
    P1OUT ^= BIT5;  // Toggle LED 6
    P1OUT ^= BIT6;  // Toggle LED 7
    P1OUT ^= BIT7;  // Toggle LED 8
}

inline int __pattern2(void) {
    int counter = 0;
    counter++; 
    P1OUT = counter;
    
    TB0CCTL0 &= ~CCIFG; //Clear CCR0 Flag
}

inline int __pattern3(void) {
    counter++;

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
}

#endif 7