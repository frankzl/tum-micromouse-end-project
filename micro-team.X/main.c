/*
 * File:   main.c
 * Author: a2-lenz
 *
 * Created on May 8, 2018, 11:16 AM
 */


// FBS
#pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)

// FGS
#pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
#pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
#pragma config FNOSC = PRIPLL           // Oscillator Mode (Primary Oscillator (XT, HS, EC) w/ PLL)
#pragma config IESO = ON                // Internal External Switch Over Mode (Start-up device with FRC, then automatically switch to user-selected oscillator source when ready)

// FOSC
#pragma config POSCMD = HS              // Primary Oscillator Source (HS Oscillator Mode)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function (OSC2 pin has clock out function)
#pragma config IOL1WAY = OFF            // Peripheral Pin Select Configuration (Allow Multiple Re-configurations)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPOST = PS1            // Watchdog Timer Postscaler (1:1)
#pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)

// FPOR
#pragma config FPWRT = PWR1             // POR Timer Value (Disabled)
#pragma config ALTI2C = ON             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)
#pragma config LPOL = ON                // Motor Control PWM Low Side Polarity bit (PWM module low side output pins have active-high output polarity)
#pragma config HPOL = ON                // Motor Control PWM High Side Polarity bit (PWM module high side output pins have active-high output polarity)
#pragma config PWMPIN = ON              // Motor Control PWM Module Pin Mode bit (PWM module pins controlled by PORT register at device Reset)

// FICD
#pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include "xc.h"

#define IN_SIMULATION_MODE 0

#include "initIO.h"
#include "qeiFunctions.h"
#include "timer1Functions.h"
#include "motorFunctions.h"
#include "uartFunctions.h"

int main(void) 
{
        /*** oscillator setup --------------------------------------------------
    Here we are using PPL for 8MHz to generate 80MHz clock.
    FCY = 0.5 * (8MHz*40/(2*2)) = 40 MIPS
    ---------------------------------------------------------------------***/
    PLLFBD = 38; //set PPL to M=40
    CLKDIVbits.PLLPRE = 0; //N1 = input/2
    CLKDIVbits.PLLPOST = 0; //N2 = output/2
    if (IN_SIMULATION_MODE != 1)
    {
        while (OSCCONbits.LOCK != 1); //Wait for PPL to lock
    }
    
    //now we are ready to run
    initIO();
    timer1Setup();
    qeiLeftSetup();
    qeiRightSetup();
    motorLeftSetup();
    motorRightSetup();
    uartSetup();
    
    while(1){}
    
    return 0;
}

