#ifndef TIMER1FUNCTIONS_H
#define	TIMER1FUNCTIONS_H

extern long positionRIGHT;
extern long positionLEFT;

void timer1Setup();
void startTimer1();

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void);

#endif	

