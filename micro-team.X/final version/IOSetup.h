#include "xc.h"

#ifndef IOSETUP_H
#define	IOSETUP_H

#define LED_FRONT LATCbits.LATC4
#define LED_BACK LATCbits.LATC3
//button ? A10
    
#define   DIR_A_LEFT LATBbits.LATB9
#define   DIR_B_LEFT LATCbits.LATC6
    
#define   DIR_A_RIGHT LATAbits.LATA7
#define   DIR_B_RIGHT LATBbits.LATB14 

void configureIO();
void initRemappable();

#endif	
