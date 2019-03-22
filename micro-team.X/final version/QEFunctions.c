#include "xc.h"
#include "UARTSetup.h"
#include "QEFunctions.h"

long positionRIGHT;
long positionLEFT;

void setupLEFTQEI()
{
    // Configure QEI module
    QEI1CONbits.QEISIDL = 1;    //Discontinue operation when in idle mode
    QEI1CONbits.QEIM = 0b111;   //x4 edge gain and reset POSCNT when == MAXCNT
    QEI1CONbits.SWPAB = 0;      //Do not swap the polarity of phase comparison
    QEI1CONbits.PCDOUT = 0;     //Disable counter direction pin (normal I/O operation)
    QEI1CONbits.POSRES = 0;     //index pulse does not reset POSCNT
    QEI1CONbits.TQCS = 0;       //internal clock source (Tcy)
    DFLT1CONbits.QEOUT = 0;     //disable digital filters

    // set initial counter value and maximum range
    MAX1CNT = 0xffff;           // set the highest possible time out
    POS1CNT = 0x7fff;           // set POSCNT into middle of range
    positionLEFT = 0x7fff; 
    
    // Configure Interrupt controller
    IFS3bits.QEI1IF = 0;        // clear interrupt flag
    IEC3bits.QEI1IE = 1;        // enable QEI interrupt
    IPC14bits.QEI1IP = 5;       // set QEI interrupt priority
}

// Check page 52
void setupRIGHTQEI()
{
    // Configure QEI module
    QEI2CONbits.QEISIDL = 1;    //Discontinue operation when in idle mode
    QEI2CONbits.QEIM = 0b111;   //x4 edge gain and reset POSCNT when == MAXCNT
    QEI2CONbits.SWPAB = 0;      //Do not swap the polarity of phase comparison
    QEI2CONbits.PCDOUT = 0;     //Disable counter direction pin (normal I/O operation)
    QEI2CONbits.POSRES = 0;     //index pulse does not reset POSCNT
    QEI2CONbits.TQCS = 0;       //internal clock source (Tcy)
    DFLT2CONbits.QEOUT = 0;     //disable digital filters

    // set initial counter value and maximum range
    MAX2CNT = 0xffff;           // set the highest possible time out
    POS2CNT = 0x7fff;           // set POSCNT into middle of range
    positionRIGHT = 0x7fff;
    
    // Configure Interrupt controller
    IFS4bits.QEI2IF  = 0;       // clear interrupt flag
    IEC4bits.QEI2IE  = 1;       // enable QEI interrupt
    IPC18bits.QEI2IP = 5;       // set QEI interrupt priority
}

// interrupt service routine

void __attribute__((interrupt, auto_psv)) _QEI1Interrupt(void)
{
    IFS3bits.QEI1IF = 0;        // clear interrupt flag
    
    if(POSCNT<32768){
        positionLEFT+=0x10000;   // over-run condition caused interrupt
    }else{
        positionLEFT-=0x10000;   // under-run condition caused interrupt
    } 
}

void __attribute__((interrupt, auto_psv)) _QEI2Interrupt(void)
{
    IFS4bits.QEI2IF = 0;        // clear interrupt flag
    
    if(POSCNT<32768){
        positionRIGHT+=0x10000;  // over-run condition caused interrupt
    }else{
        positionRIGHT-=0x10000;  // under-run condition caused interrupt
    } 
}