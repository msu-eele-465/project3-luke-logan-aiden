#include <msp430.h>


#define _BITS0TO2 7

int REDVAR = 255;
int GREENVAR = 0;
int BLUEVAR = 0;
int status = 0;
//Setup Ports

void init_RGB_LEDs(){
    P4DIR |= _BITS0TO2;
    P4OUT &= ~_BITS0TO2;

    TB3CCR4 = _PERIOD_MUL*REDVAR;       // set CCR4 red duty cycle
    TB3CCTL4 |= CCIE;                   // enable compaxxsre interrupt
    TB3CCTL4 &= ~CCIFG;                 // clear interrupt flag

    TB3CCR5 = _PERIOD_MUL*GREENVAR;     // set CCR5 to green duty cycle
    TB3CCTL5 |= CCIE;                   // enable compare interrupt
    TB3CCTL5 &= ~CCIFG;                 // clear interrupt flag

    TB3CCR6 = _PERIOD_MUL*BLUEVAR;      // set CCR6 to blue duty cycle
    TB3CCTL6 |= CCIE;                   // enable compare interrupt
    TB3CCTL6 &= ~CCIFG;                 // clear interrupt flag

    TB1CTL |= TBCLR;                    // clear timers & dividers
    TB1CTL |= TBSSEL__SMCLK;            // source = SMCLK
    TB1CTL |= MC__UP;                   // set count up
    TB1CTL |= ID__1;                    // set divider 1 to 1
    TB1CTL |= CNTL_0;                   // 16-bit clock length

    TB1CCR0 = //put something here that gives us a good period - probably a variable that is changed by keypad      //set TB1CCR0 to whatever number needed to change colors
    TB1CCTL0 |= CCIE;                   //enable compare interrupt
    TB1CCTL0 &= ~CCIFG;                 //clear interrupt flag

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
    }else if(satus == 2){
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
}