#include <msp430.h> 
#include <stdio.h> 
#include "led-bar.h"
int counter = 0;
int counter1 = 256;

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

void pattern_up_counter() { // Pattern 2
    _init_LED_bar(); // Set up Ports

    P1OUT &= ~BIT0; // Initialize starting LEDs
    P1OUT &= ~BIT1;
    P1OUT &= ~BIT2;
    P1OUT &= ~BIT3;
    P1OUT &= ~BIT4;
    P1OUT &= ~BIT5;
    P1OUT &= ~BIT6;
    P1OUT &= ~BIT7;

    // Setup Timer
    TB0CTL |= TBCLR;    // clear timers & dividers
    TB0CTL |= TBSSEL__ACLK; // Source = ACLK
    TB0CTL |= MC__UP;   // Mode=UP
    TB0CCR0 = 16384;    // CCR0=16384

    // Setup Timer Compare IRQ
    TB0CCTL0 &= ~CCIFG;   // Clear CCR0 Flag
    TB0CCTL0 |= CCIE;     // Enable TB0 CCR0 Overflow IRQ
    __enable_interrupt();   // Enable Maskable IRQs

}

void pattern_in_out() {
    _init_LED_bar();

    P1OUT &= ~BIT0; // Initialize starting LEDs
    P1OUT &= ~BIT1;
    P1OUT &= ~BIT2;
    P1OUT &= ~BIT3;
    P1OUT &= ~BIT4;
    P1OUT &= ~BIT5;
    P1OUT &= ~BIT6;
    P1OUT &= ~BIT7;

    // Setup Timer
    TB0CTL |= TBCLR;    // clear timers & dividers
    TB0CTL |= TBSSEL__ACLK; // Source = ACLK
    TB0CTL |= MC__UP;   // Mode=UP
    TB0CCR0 = 16384;    // CCR0=16384

    // Setup Timer Compare IRQ
    TB0CCTL0 &= ~CCIFG;   // Clear CCR0 Flag
    TB0CCTL0 |= CCIE;     // Enable TB0 CCR0 Overflow IRQ
    __enable_interrupt();   // Enable Maskable IRQs
}

void pattern_down_counter() {
    _init_LED_bar();

    P1OUT &= ~BIT0; // Initialize starting LEDs
    P1OUT &= ~BIT1;
    P1OUT &= ~BIT2;
    P1OUT &= ~BIT3;
    P1OUT &= ~BIT4;
    P1OUT &= ~BIT5;
    P1OUT &= ~BIT6;
    P1OUT &= ~BIT7;

    // Setup Timer
    TB0CTL |= TBCLR;    // clear timers & dividers
    TB0CTL |= TBSSEL__ACLK; // Source = ACLK
    TB0CTL |= MC__UP;   // Mode=UP
    TB0CCR0 = 8192;    // CCR0=8192

    // Setup Timer Compare IRQ
    TB0CCTL0 &= ~CCIFG;   // Clear CCR0 Flag
    TB0CCTL0 |= CCIE;     // Enable TB0 CCR0 Overflow IRQ
    __enable_interrupt();   // Enable Maskable IRQs
}

void pattern_rotate_left() {
    _init_LED_bar();

    P1OUT &= ~BIT0; // Initialize starting LEDs
    P1OUT &= ~BIT1;
    P1OUT &= ~BIT2;
    P1OUT &= ~BIT3;
    P1OUT &= ~BIT4;
    P1OUT &= ~BIT5;
    P1OUT &= ~BIT6;
    P1OUT &= ~BIT7;

    // Setup Timer
    TB0CTL |= TBCLR;    // clear timers & dividers
    TB0CTL |= TBSSEL__ACLK; // Source = ACLK
    TB0CTL |= MC__UP;   // Mode=UP
    TB0CCR0 = 49153;    // CCR0=49153

    // Setup Timer Compare IRQ
    TB0CCTL0 &= ~CCIFG;   // Clear CCR0 Flag
    TB0CCTL0 |= CCIE;     // Enable TB0 CCR0 Overflow IRQ
    __enable_interrupt();   // Enable Maskable IRQs
}

void pattern_0_rotate_right() {
_init_LED_bar();

    P1OUT |= ~BIT0; // Initialize starting LEDs
    P1OUT |= BIT1;
    P1OUT |= BIT2;
    P1OUT |= BIT3;
    P1OUT |= BIT4;
    P1OUT |= BIT5;
    P1OUT |= BIT6;
    P1OUT |= BIT7;

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

void pattern_fill_left() {
    _init_LED_bar();

    P1OUT &= ~BIT0; // Initialize starting LEDs
    P1OUT &= ~BIT1;
    P1OUT &= ~BIT2;
    P1OUT &= ~BIT3;
    P1OUT &= ~BIT4;
    P1OUT &= ~BIT5;
    P1OUT &= ~BIT6;
    P1OUT |= BIT7;

    // Setup Timer
    TB0CTL |= TBCLR;    // clear timers & dividers
    TB0CTL |= TBSSEL__ACLK; // Source = ACLK
    TB0CTL |= MC__UP;   // Mode=UP
    TB0CCR0 = 16384;    // CCR0=16384

    // Setup Timer Compare IRQ
    TB0CCTL0 &= ~CCIFG;   // Clear CCR0 Flag
    TB0CCTL0 |= CCIE;     // Enable TB0 CCR0 Overflow IRQ
    __enable_interrupt();   // Enable Maskable IRQs
    
}


//------ Interrupt Service Routines -----------------------------
#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void)
{
    counter++;
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
}