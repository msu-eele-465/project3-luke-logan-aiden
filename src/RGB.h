#ifndef RGB_H
#define RGB_H

#include <msp430.h>


#define _BITS4TO6 112

int _PERIOD_MUL = 4;
int REDVAR = 255;
int GREENVAR = 0;
int BLUEVAR = 0;
int status = 0;
int RGB_Change_Speed = 1000;
//Setup Ports

void init_RGB_LEDs(){
    P4DIR |= _BITS4TO6;
    P4OUT &= ~_BITS4TO6;

    TB3CCR4 = _PERIOD_MUL*REDVAR;       // set CCR4 red duty cycle
    TB3CCTL4 |= CCIE;                   // enable compaxxsre interrupt
    TB3CCTL4 &= ~CCIFG;                 // clear interrupt flag

    TB3CCR5 = _PERIOD_MUL*GREENVAR;     // set CCR5 to green duty cycle
    TB3CCTL5 |= CCIE;                   // enable compare interrupt
    TB3CCTL5 &= ~CCIFG;                 // clear interrupt flag

    TB3CCR6 = _PERIOD_MUL*BLUEVAR;      // set CCR6 to blue duty cycle
    TB3CCTL6 |= CCIE;                   // enable compare interrupt
    TB3CCTL6 &= ~CCIFG;                 // clear interrupt flag

    TB3CTL |= TBCLR;                    // clear timers & dividers
    TB3CTL |= TBSSEL__SMCLK;            // source = SMCLK
    TB3CTL |= MC__UP;                   // set count up
    TB3CTL |= ID__1;                    // set divider 1 to 1
    TB3CTL |= CNTL_0;                   // 16-bit clock length

    TB1CCR0 = RGB_Change_Speed;
    TB1CCTL0 |= CCIE;                   //enable compare interrupt
    TB1CCTL0 &= ~CCIFG;                 //clear interrupt flag

    TB1CTL |= TBCLR;                    // clear timers & dividers
    TB1CTL |= TBSSEL__SMCLK;            // source = SMCLK
    TB1CTL |= MC__UP;                   // set count up
    TB1CTL |= ID__1;                    // set divider 1 to 1
    TB1CTL |= CNTL_0;                   // 16-bit clock length

    return;
}

void cycleColors(){
    if(status == 0){
        GREENVAR++;
        if(GREENVAR == 255){
            status = 1;
        }
    }else if(status == 1){
        REDVAR--;
        if(REDVAR == 0){
            status = 2;
        }
    }else if(status == 2){
        BLUEVAR++;
        if(BLUEVAR == 255){
            status = 3;
        }
    }else if(status == 3){
        GREENVAR--;
        if(GREENVAR == 0){
            status = 4;
        }
    }else if(status == 4){
        REDVAR++;
        if(REDVAR == 255){
            status = 5;
        }
    }else if(status == 5){
        BLUEVAR--;
        if(BLUEVAR == 0){
            status = 0;
        }
    }
    TB3CCR6 = _PERIOD_MUL*BLUEVAR;      // set CCR6 to blue duty cycle
    TB3CCR5 = _PERIOD_MUL*GREENVAR;     // set CCR5 to green duty cycle
    TB3CCR4 = _PERIOD_MUL*REDVAR;       // set CCR4 red duty cycle
    TB1CCTL0 &= ~CCIFG;                 //clear interrupt flag
}


void TB3_CCR4_RED(){
    P4OUT &= ~BIT4;
    TB3CCTL1 &= ~CCIFG;                 // clear interrupt flag
    return;
}

void TB3_CCR5_GREEN(){
    P4OUT &= ~BIT5;
    TB3CCTL1 &= ~CCIFG;                 // clear interrupt flag
    return;
}

void TB3_CCR6_BLUE(){
    P4OUT &= ~BIT6;
    TB3CCTL1 &= ~CCIFG;                 // clear interrupt flag
    return;
}

void RGB_SpeedUp(){
    RGB_Change_Speed = 2000;
    TB1CCR0 = RGB_Change_Speed;
    return;
}


void RGB_SlowDown(){
    RGB_Change_Speed = 500;
    TB1CCR0 = RGB_Change_Speed;
    return;
}

#endif