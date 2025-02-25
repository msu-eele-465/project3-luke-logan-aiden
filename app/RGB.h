#include <msp430.h>


#define _BITS0TO2 7

int _PERIOD_MUL = 4;
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
}


void TB3_CCR4_RED(){
    P4OUT &= ~BIT0;
    TB3CCTL1 &= ~CCIFG;                 // clear interrupt flag
    return;
}

void TB3_CCR5_GREEN(){
    P4OUT &= ~BIT1;
    TB3CCTL1 &= ~CCIFG;                 // clear interrupt flag
    return;
}

void TB3_CCR6_BLUE(){
    P4OUT &= ~BIT2;
    TB3CCTL1 &= ~CCIFG;                 // clear interrupt flag
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

        case 10:
            TB3_CCR4_RED();
            return;

        case 12:
            TB3_CCR5_GREEN();
            return;

        case 14:
            TB3_CCR6_BLUE();
            return;
    }
}