#ifndef PWMFUNCTIONS_H
#define	PWMFUNCTIONS_H

// Define the maximum value of the PWM duty cycle register, for easy reference (*6/9=0.667)
#define LEFT_maxDC (2*(P1TPER + 1))*0.667
#define RIGHT_maxDC (2*(P2TPER + 1))*0.667

void configurePWMLeft();
void configurePWMRight();

void setLEFTDC(int dc);
void setRIGHTDC(int dc);

#endif



