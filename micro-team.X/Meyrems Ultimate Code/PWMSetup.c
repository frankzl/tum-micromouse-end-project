#include "xc.h"
#include <p33Fxxxx.h>
#include "IOSetup.h"
#include "PWMSetup.h"
//Fpwm = 20khz 

void configurePWMLeft(){
    
P1TCONbits.PTEN = 0;         //clear PTEN : switch off PWM time base during configuration
P1TCONbits.PTCKPS = 0x0 ;    //set PTCKPS : choose time base prescaler=1
P1TPER = 1999;               //set PTPER : set the PWM period=Fcyc/(PWMfreq*prescaler)-1=40000/20 - 1
PWM1CON1bits.PMOD1 = 1;      //set PMOD1 : set PWM unit 1 into the independent mode 
PWM1CON1bits.PEN1L = 1;      //set PEN1L : enable PWM 1 low-side driver you could use just one
PWM1CON1bits.PEN1H = 1;      //set PEN1H : enable PWM 1 high-side driver
P1TCONbits.PTEN = 1;         //set PTEN : switch on the PWM generator

}

void configurePWMRight(){
    
P2TCONbits.PTEN = 0;         //clear PTEN : switch off PWM time base during configuration
P2TCONbits.PTCKPS = 0x0 ;    // set PTCKPS : choose time base prescaler=1
P2TPER = 1999;               //set PTPER : set the PWM period=Fcyc/(PWMfreq*prescaler)-1
PWM2CON1bits.PMOD1 = 1;      //set PMOD1 : set PWM unit 1 into the independent mode 
PWM2CON1bits.PEN1L = 1;      //set PEN1L : enable PWM 1 low-side driver you could use just one
PWM2CON1bits.PEN1H = 1;      //set PEN1H : enable PWM 1 high-side driver
P2TCONbits.PTEN = 1;         //set PTEN : finally, switch on the PWM generator

}

void setLEFTDC(int dc) 
{
    //pdc=2*(ptper+1)*dc/100
    PDC1 = (int)(dc*0.01 * LEFT_maxDC);
}

void setRIGHTDC(int dc) 
{
    PDC2 = (int)(dc*0.01 * LEFT_maxDC);
}