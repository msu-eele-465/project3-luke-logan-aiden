#include <msp430.h>
#include <stdio.h>


/*
#define ROW1 BIT0  // P1.0
#define ROW2 BIT1  // P1.1
#define ROW3 BIT2  // P1.2
#define ROW4 BIT3  // P1.3
#define COL1 BIT4  // P1.4
#define COL2 BIT5  // P1.5
#define COL3 BIT6  // P1.6
#define COL4 BIT7  // P1.7

const char keypad[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
*/
void pattern_static() { // Pattern 1
    P2DIR |= BIT0;
    P2OUT = 0b10101010; 
}

void pattern_toggle() { // Pattern 2
    P2DIR |= BIT0;
    P2OUT ^= 0xFF; 
}

/*void pattern_up_counter() { // Up Counter
    static uint8_t counter = 0; 
    P2OUT = counter++;
}

void pattern_rotate_left() { // Rotate Left
    static uint8_t val = 1;
    val = (val << 1) | (val >> 7);
    P2OUT = val;
}
*/