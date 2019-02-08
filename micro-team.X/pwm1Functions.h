#ifndef PWM1FUNCTIONS_H
#define	PWM1FUNCTIONS_H

#include "xc.h"

// Define the maximum value of the PWM duty cycle register, for easy reference
#define LEFT_maxDC (2*(P1TPER + 1))
#define RIGHT_maxDC (2*(P2TPER + 1))

void pwmLEFTSetup();
void pwmRIGHTSetup();

void setLEFTDC(int dc);
void setRIGHTDC(int dc);

#endif	/* PWM1FUNCTIONS_H */