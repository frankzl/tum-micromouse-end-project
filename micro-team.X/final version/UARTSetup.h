#ifndef UARTSETUP_H
#define	UARTSETUP_H

#include "xc.h"
#include <p33Fxxxx.h>

void uartSetup();
void uartSendChar(char sending_value);

void WriteCharUART1 (char data);
void WriteStringUART1(const char * s);
void WriteIntUART(unsigned value);
int format( char* command );

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void);


#endif	/* UARTSETUP_H */
