#ifndef _KEYPAD_H
#define _KEYPAD_H

#include <msp430.h>
#include <stdbool.h>

// Keypad defined as port 3

//#define KEYPADDIR P3DIR
//#define KEYPADOUT P3OUT
//#define KEYPADIN P3IN
//#define KEYPADREN P3REN

// Keypad bitmask definitions

#define ROW_MASK 0xF
#define COLUMN_MASK 0xF0

inline int _read_keypad_columns(void)
{
    int column_read = 0;

    // initialize port

    P3DIR |= ROW_MASK;                  // P3.0-3 outputs
    P3DIR &= ~COLUMN_MASK;              // P3.4-7 inputs
    P3REN |= COLUMN_MASK;               // enable resistors
    P3OUT &= ~COLUMN_MASK;              // make resistors pull down
    P3OUT |= ROW_MASK;                  // outputs set to 1

    // read port

    column_read = P3IN;
    column_read &= COLUMN_MASK;         // read input

    // reset port

    P3DIR |= 0xFF;
    P3OUT &= ~0xFF;                     // resting port to all off and output
    P3REN &= ~0xFF;                     // resetting resistor byte to all zero

    return column_read;

}

inline int _read_keypad_rows(void)
{
    int row_read = 0;

    P3DIR |= COLUMN_MASK;               // P3.0-3 outputs
    P3DIR &= ~ROW_MASK;                 // P3.4-7 inputs
    P3REN |= ROW_MASK;                  // enable resistors
    P3OUT &= ~ROW_MASK;                 // make resistors pull down
    P3OUT |= COLUMN_MASK;               // outputs set to 1

    // read port

    row_read = P3IN;
    row_read &= ROW_MASK;               // read input

    // reset port

    P3DIR |= 0xFF;
    P3OUT &= ~0xFF;                     // resting port to all off and output
    P3REN &= ~0xFF;                     // resetting resistor byte to all zero

    return row_read;
}

inline char _read_keypad_char(void)
{
    int read = (_read_keypad_columns() | _read_keypad_rows());

    switch (read) {

        case 0x11:
            return '1';
        
        case 0x21:
            return '2';
        
        default:
            return 'E';
    
    }
}


#endif // _KEYPAD_H