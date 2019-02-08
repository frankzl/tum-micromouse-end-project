/*
 * File:   initIO.c
 * Author: a2-lenz
 *
 * Created on May 8, 2018, 11:30 AM
 */


#include "initIO.h"

void initIO() {

    // set up analogue pins
    // AD1CON1bits.ADON = 0; // disable ADC1 module
    // AD1PCFGL = 0xffCf; //0b1111 1111 1100 1111; 		//  AN4 and AN5 are analog inputs

    //outputs
    TRISAbits.TRISA4=0; //LED0 is output
    
    // UART RX
    TRISBbits.TRISB7 = 1; //UART RX on RB7
    
    // UART TX
    TRISBbits.TRISB8 = 0; //UART TX on RB8
    
    
    TRISBbits.TRISB9 = 0; //DIR_A_LEFT for Motor LEFT
    TRISCbits.TRISC6 = 0; //DIR_B_LEFT for Motor LEFT
    
    TRISAbits.TRISA7  = 0; // DIR_A_RIGHT for Motor RIGHT
    TRISBbits.TRISB14 = 0; // DIR_B_RIGHT for Motor RIGHT
    
    initRemappable();
    
}

void initRemappable(){
    // set up remappable pins
    __builtin_write_OSCCONL(OSCCON & 0xbf); // clear bit 6 (unlock, they are usually write protected)
    
    
    // UART RX
    RPINR18bits.U1RXR = 7;
    
    // UART TX
    RPOR4bits.RP8R = 0b00011;
    
    // LEFT MOTOR QEI
    RPINR14bits.QEA1R = 13; // QEI1 A to pin RB13
    RPINR14bits.QEB1R = 12; // QEI1 B to pin RB12
    
    // RIGHT MOTOR
    RPINR16bits.QEA2R = 24; // QEI1 A to pin RB24
    RPINR16bits.QEB2R = 25; // QEI1 B to pin RB25
    
    //end of set up of remappable pins
    __builtin_write_OSCCONL(OSCCON | 0x40); // Lock PPS registers (lock again!)
    
    int i;
    for (i = 0; i < 30000; i++); // short delay
}
