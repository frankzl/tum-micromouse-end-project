#ifndef	QEI_FUNCTIONS_H
#define	QEI_FUNCTIONS_H

extern long positionRIGHT;
extern long positionLEFT;

void setupLEFTQEI();
void setupRIGHTQEI();

void __attribute__((interrupt, auto_psv)) _QEI1Interrupt(void);
void __attribute__((interrupt, auto_psv)) _QEI2Interrupt(void);


#endif
