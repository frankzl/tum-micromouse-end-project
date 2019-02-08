#include "pwm1Functions.h"

void pwmLEFTSetup() 
{
    // switch off PWM time base during configuration
    P1TCONbits.PTEN = 0;
    
    // choose time base prescaler, options are 1:1, 1:4, 1:16, or 1:64
    P1TCONbits.PTCKPS = 0b00; // choose 1, PTPER 1999, for 20khz
    
    /*
     * PTPER+1 gives the number of Tcycles
     * although counts only up to PTPER but 100% duty cycle (DC) value is 
     * double the amount 2x(PTPER+1)
     */
    P1TPER = 2000 - 1; //20khz

    // set PWM unit 1 into the independent mode (use PWMCON1bits.PMOD1 =1)
    PWM1CON1bits.PMOD1 = 1;

    // enable PWM 1 low-side driver, (connected to LED4)
    PWM1CON1bits.PEN1L = 1;
    
    // enable PWM 1 high-side driver
    PWM1CON1bits.PEN1H = 1;
    
    // switch on PWM time base
    P1TCONbits.PTEN = 1;
}

void pwmRIGHTSetup() 
{
    // switch off PWM time base during configuration
    P2TCONbits.PTEN = 0;
    
    P2TCONbits.PTCKPS = 0b00; // choose prescalar 1, PTPER 2000 - 1, for 20khz
    
    /*
     * PTPER+1 gives the number of Tcycles
     * although counts only up to PTPER but 100% duty cycle (DC) value is 
     * double the amount 2x(PTPER+1)
     */
    
    // set the PWM period (15bit)
    P2TPER = 2000 - 1; //20khz

    // set PWM unit 1 into the independent mode (use PWMCON1bits.PMOD1 =1)
    PWM2CON1bits.PMOD1 = 1;

    // enable PWM 1 low-side driver, (connected to LED4)
    PWM2CON1bits.PEN1L = 1;
    
    // enable PWM 1 high-side driver
    PWM2CON1bits.PEN1H = 1;
   
    // switch on PWM time base
    P2TCONbits.PTEN = 1;
}

void changeDC(void) 
{
    static int counter = 0;
    
    //PDC1 = 200;
    switch(counter % 4)
    {
        case 0:
            // 10% duty cycle
            PDC1 = (int)(0.1 * LEFT_maxDC);
            break;
        case 1:
            // 50% duty cycle
            PDC1 = (int)(0.25 * LEFT_maxDC);
            break;
        case 2:
            // 75% duty cycle
            PDC1 = (int)(0.50 * LEFT_maxDC);
            break;
        case 3:
            // 100% duty cycle
            PDC1 = LEFT_maxDC;
            break;
    }
    counter++;
}


void setLEFTDC(int dc) 
{
    // WriteUART1(dc);
    PDC1 = (int)(dc*0.01 * LEFT_maxDC);
}

void setRIGHTDC(int dc) 
{
    // WriteUART1(dc);
    PDC2 = (int)(dc*0.01 * LEFT_maxDC);
}