#ifndef TIMER1FUNCTIONS_H
#define	TIMER1FUNCTIONS_H

void timer1Setup();
void startTimer1();

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void);

#endif	

