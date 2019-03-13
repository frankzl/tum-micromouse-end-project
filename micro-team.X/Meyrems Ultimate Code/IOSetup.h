#include "xc.h"

#ifndef IOSETUP_H
#define	IOSETUP_H

#define LED0 LATAbits.LATA4
    
#define   DIR_A_LEFT LATBbits.LATB9
#define   DIR_B_LEFT LATCbits.LATC6
    
#define   DIR_A_RIGHT LATAbits.LATA7
#define   DIR_B_RIGHT LATBbits.LATB14 

void configureIO();
void initRemappable();

#endif	
