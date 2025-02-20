#include <msp430.h> 
#include <stdio.h> 
#include "led-bar.h"


void pattern_static() { // Pattern 0

    _init_LED_bar();

    P1OUT |= BIT0; // Set values 
    P1OUT &= ~BIT1;
    P1OUT |= BIT2;
    P1OUT &= ~BIT3;
    P1OUT |= BIT4;
    P1OUT &= ~BIT5;
    P1OUT |= BIT6;
    P1OUT &= ~BIT7;
}

void pattern_toggle() { // Pattern 1

    _init_LED_bar(); // Set up Ports

    P1OUT |= BIT0; 
    P1OUT &= ~BIT1;
    P1OUT |= BIT2;
    P1OUT &= ~BIT3;
    P1OUT |= BIT4;
    P1OUT &= ~BIT5;
    P1OUT |= BIT6;
    P1OUT &= ~BIT7;
    
    // Setup Timer
    TB0CTL |= TBCLR;    // clear timers & dividers
    TB0CTL |= TBSSEL__ACLK; // Source = ACLK
    TB0CTL |= MC__UP;   // Mode=UP
    TB0CCR0 = 32769;    // CCR0=32769

    // Setup Timer Compare IRQ
    TB0CCTL0 &= ~CCIFG;   // Clear CCR0 Flag
    TB0CCTL0 |= CCIE;     // Enable TB0 CCR0 Overflow IRQ
    __enable_interrupt();   // Enable Maskable IRQs
    
}

void pattern_up_counter() { // Pattern 
    int i = 0;
    P1DIR |= BIT0;
     while(1)                                  // continuous loop
  {
    P1OUT ^= BIT0;                          // XOR P1.0
    for(i=5000;i>0;i--);                    // Delay
  }
}

/*
void pattern_rotate_left() { // Pattern 3
    static uint8_t val = 1;
    val = (val << 1) | (val >> 7);
    P2OUT = val;
}
*/

/*
    // If able to:

    // Pattern 4


    // Pattern 5


    // Pattern 6


    // Pattern 7
*/


//------ Interrupt Service Routines -----------------------------
#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void)
{
    P1OUT ^= BIT0;  // Toggle LED 1
    P1OUT ^= BIT1;  // Toggle LED 2
    P1OUT ^= BIT2;  // Toggle LED 3
    P1OUT ^= BIT3;  // Toggle LED 4
    P1OUT ^= BIT4;  // Toggle LED 5
    P1OUT ^= BIT5;  // Toggle LED 6
    P1OUT ^= BIT6;  // Toggle LED 7
    P1OUT ^= BIT7;  // Toggle LED 8
    TB0CCTL0 &= ~CCIFG; //Clear CCR0 Flag
}