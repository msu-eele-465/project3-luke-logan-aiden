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

#endif 7