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

int main(void) 
{
    /*oscillator setup --------------------------------------------------
    Here we are using PPL for 8MHz to generate 80MHz clock.
    FCY = 0.5 * (8MHz*40/(2*2)) = 40 MIPS
    ---------------------------------------------------------------------*/
    PLLFBD = 38; //set PPL to M=40
    CLKDIVbits.PLLPRE = 0; //N1 = input/2
    CLKDIVbits.PLLPOST = 0; //N2 = output/2
    if (IN_SIMULATION_MODE != 1)
    {
        while (OSCCONbits.LOCK != 1); //Wait for PPL to lock
    }
    
    //initialise all necessary modules
    configureIO();          //Configure the IO ports
    initRemappable();       //configure pin remapping
    timer1Setup();          //Configure Timer 1 (T=10ms, priority=3)
    configurePWMLeft();     //Configure PWM
    configurePWMRight();    //Configure PWM
    setupLEFTQEI();         // Configure Quardature Encoder Interface 1 (left??)
    setupRIGHTQEI();        // Configure Quardature Encoder Interface 2 (right)??
    setupADC1();
    initDmaChannel4();      //ADC DMA
    uartSetup();            //Configure UART
    
    startADC1();
  
    //initPID(int i, float Kp, float Ki, float Kd, float Imax, float omax)
    PID_init(   RIGHT_WHEEL_VELO ,       145,   10.0,       0.0 ,    10000,    40000); //right wheel velocity
    PID_init(   LEFT_WHEEL_VELO  ,       145,   10.0,       0.0 ,    10000,    40000); //left wheel velocity
    PID_init(   RIGHT_WHEEL_POS  ,       1.0,    0.0,       0.0 ,     1,       15); //right wheel position (cascade into velocity)
    PID_init(   LEFT_WHEEL_POS   ,        1.0,    0.0,       0.0 ,    1,       15); //left wheel position (cascade into velocity)
    //initMainControl();
   
    startTimer1();//timer interrupt starts
    
    
    while(1); //remain here forever, never end the main function.
    return 0; //we should never really return
}
