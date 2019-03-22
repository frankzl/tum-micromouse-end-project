#include "IOSetup.h"

void configureIO()
{    
    //LED outputs
    TRISCbits.TRISC4=0; //LED front
    TRISCbits.TRISC3=0; //LED back
    
    //Button Input
    TRISAbits.TRISA10=1; //button to switch robot mode
 
    // UART RX
    TRISBbits.TRISB7 = 1; //UART RX on RB7
    
    // UART TX
    TRISBbits.TRISB8 = 0; //UART TX on RB8
    
    //LEFT MOTOR   
    TRISBbits.TRISB9 = 0; //DIR_A_LEFT for Motor LEFT
    TRISCbits.TRISC6 = 0; //DIR_B_LEFT for Motor LEFT
    
    //RIGHT MOTOR
    TRISAbits.TRISA7  = 0; // DIR_A_RIGHT for Motor RIGHT
    TRISBbits.TRISB14 = 0; // DIR_B_RIGHT for Motor RIGHT 
}

void initRemappable()
{   
    // set up remappable pins
   __builtin_write_OSCCONL(OSCCON & 0xdf); // clear bit 5 (unlock, they are usually write protected)
    
    // UART RX
    RPINR18bits.U1RXR = 7;
    
    // UART TX
    RPOR4bits.RP8R = 0b00011; //output pin remapping: map RP8 to UART TX
    
    // LEFT MOTOR QEI
    RPINR14bits.QEA1R = 13; // QEI1 A to pin RB13
    RPINR14bits.QEB1R = 12; // QEI1 B to pin RB12
    
    // RIGHT MOTOR
    RPINR16bits.QEA2R = 24; // QEI1 A to pin RB24
    RPINR16bits.QEB2R = 25; // QEI1 B to pin RB25
    
    //end of set up of remappable pins
    __builtin_write_OSCCONL(OSCCON | 0x20); // Lock PPS registers 
   
    int i;
    for (i = 0; i < 30000; i++); // short delay
}