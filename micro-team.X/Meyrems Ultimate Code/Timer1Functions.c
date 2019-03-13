#include "timer1Functions.h"
#include "IOSetup.h"
#include "PWMSetup.h"
#include "math.h"
#include "DMA.h"
#include "UARTSetup.h"
#include "QEFunctions.h"
#include "MotorControl.h"

//10ms timer interrupt, based on a 1.6 us base = presclar/40MIPS, pr=6250

void timer1Setup(void)
{
    T1CON = 0;              // ensure Timer 1 is in reset state
    T1CONbits.TGATE = 0;    // gated time accumulation disabled
    T1CONbits.TCKPS = 0b10; // FCY divide by 8 [prescaler=64; tick=1.6us]
    T1CONbits.TCS = 0;      // select internal FCY clock source
    TMR1 = 0;
    PR1 = 6249;             // set Timer 1 period register
    IFS0bits.T1IF = 0;      // reset Timer 1 interrupt flag
    IPC0bits.T1IP = 4;      // set Timer1 interrupt priority level to 4
    IEC0bits.T1IE = 1;      // enable Timer 1 interrupt
    T1CONbits.TON = 0;      // leave timer disabled initially
}

void startTimer1(void) {
    T1CONbits.TON = 1; 
}

void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF=0;         //clear  interrupt flag
    
    AD1CON1bits.ASAM=1;      //start adc sampling
   
    mainControl();

}
