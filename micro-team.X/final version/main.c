#include "xc.h"
#define IN_SIMULATION_MODE 0
#include "main.h"
#include "IOSetup.h"
#include "Timer1Functions.h"
#include "PWMSetup.h"
#include "ADCFunctions.h"
#include "DMA.h"
#include "QEFunctions.h"
#include "UARTSetup.h"
#include "MotorControl.h"
#include "DriverFunctions.h"
#include "stateFunctions.h"

int main(void) 
{
    /*oscillator setup --------------------------------------------------
    Configure Phase Lock Loop (PLL) for  the system clock reference at 40MHz 
    Fosc (Clock frequency) is set at 80MHz
    Fin (Oscillator frequency) is 16MHz
    FCY = 1/2 * Fosc = 1/2 * (Fin*M/(N1*N2)) = 0.5 * (16MHz*20/(2*2)) = 40 MIPS
    ---------------------------------------------------------------------*/
    PLLFBD = 18;                //set PPL to M=20 PLL Feedback Divisor 
    CLKDIVbits.PLLPRE = 0;      //N1 = input/2
    CLKDIVbits.PLLPOST = 0;     //N2 = output/2
    
    if (IN_SIMULATION_MODE != 1)
    {
        while (OSCCONbits.LOCK != 1); //Wait for PPL to lock
    }
    
    //initialise all necessary modules
    configureIO();          //Configure the IO ports
    initRemappable();       //configure pin remapping
    timer1Setup();          //Configure Timer 1 (T=10ms, priority=3)
    configurePWMLeft();     //Configure PWM for left motor (Tpwm=20KHz, priority=)
    configurePWMRight();    //Configure PWM for right motor (Tpwm=20KHz, priority=)
    setupLEFTQEI();         //Configure Quardature Encoder Interface 1 
    setupRIGHTQEI();        //Configure Quardature Encoder Interface 2 
    setupADC1();            //Configure ADC
    initDmaChannel4();      //configure DMA
    uartSetup();            //Configure UART
    
    //start running
    startADC1();            //Start sampling
  
    //initialize PID
    //initPID(int i, float Kp, float Ki, float Kd, float Imax, float omax)
    PID_init(   RIGHT_WHEEL_VELO ,       8.0,   0.2,       0.0 ,    1000,    4000); //right wheel velocity
    PID_init(   LEFT_WHEEL_VELO  ,       8.0,   0.2,       0.0 ,    1000,    4000); //left wheel velocity
    PID_init(   RIGHT_WHEEL_POS  ,       1.0,    0.0,       0.0 ,     1,       15); //right wheel position (cascade into velocity)
    PID_init(   LEFT_WHEEL_POS   ,        1.0,    0.0,       0.0 ,    1,       15); //left wheel position (cascade into velocity)
   
    startTimer1();          //enable timer
    
    
    while(1);               //background loop: remain here forever, never end the main function.
    return 0;               //we should never really return
}
