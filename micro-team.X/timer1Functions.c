#include "timer1Functions.h"
// #include "IOSetup.h"
// #include "uartFunctions.h"

// PR1 = 2500 - 1; // 50ms value for the period register

void timer1Setup() 
{
    int period = 6250 - 1;
    
    T1CON = 0; // ensure Timer 1 is in reset state
    T1CONbits.TGATE = 0; // gated time accumulation disabled
    T1CONbits.TCKPS = 0b10; // FCY divide by 64: 1 tick = 25ns * 64 = 1600
    T1CONbits.TCS = 0; // select internal FCY clock source
    TMR1 = 0;
    PR1 = period; // set Timer 1 period register ()
    IFS0bits.T1IF = 0; // reset Timer 1 interrupt flag
    IPC0bits.T1IP = 4; // set Timer1 interrupt priority level to 4
    IEC0bits.T1IE = 1; // enable Timer 1 interrupt
    T1CONbits.TON = 0; // leave timer disabled initially
    
    startTimer1();
}

void startTimer1(void){
    T1CONbits.TON = 1;
}


void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF=0; //reset the timer 1 interrupt flag
    //WriteIntUART(POSCNT);

    //LED2Latch = ~LED2Latch; // switch the LED2
    //LED1Latch = ~LED1Latch; // switch the LED1
    //uartSendChar('a');
    //LED3Latch = ~LED3Latch; // switch the LED3
}
