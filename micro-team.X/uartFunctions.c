#include "uartFunctions.h"
#include <string.h>
#include "motorFunctions.h"
#include "pwm1Functions.h"
#include <stdio.h>

/*
*	set-up the serial port
*   here we aim to achieve a data transfer rate of 57.6 kbit/s,
*   based on Fcycle=40Mhz (40MIPS with 80MHz clock)
*   BaudRate=Fcycle/(16*(BRG+1))
*   ==> BRG=Fcy/(16*BaudRate) - 1 = 40Mhz/(16*57600) - 1 = 42.40
*   ==> choose 42 ==> BaudRate= 58.139  kbit/s, which is ~ 1% off.
*/

void uartSetup()
{
    U1MODEbits.UARTEN = 0; // disable UART during config
    U1BRG = 42; //choose appropriate baud rate (57.6 kbit/s)
    U1MODEbits.LPBACK = 0; //disable loopback mode
    
    U1MODEbits.WAKE = 0; //do not wake-up on serial activity (don?t care)
    
    U1MODEbits.ABAUD = 0; // no auto-baud detection
    U1MODEbits.PDSEL = 0; // clear (8 databits, no parity)
    U1MODEbits.STSEL = 0; //clear one stop bit
    
    U1STAbits.URXISEL = 0; // clear (receive interrupt when 1 character arrives)
    
    IFS0bits.U1RXIF = 0; // clear rx interrupt flag
    IFS0bits.U1TXIF = 0; // clear tx interrupt flag
    
    IPC2bits.U1RXIP = 6; //set receive interrupt priority
    
    IEC0bits.U1RXIE = 1; // enable receive interupts
    IEC0bits.U1TXIE = 0; // disable transmit interrupts
    
    
    // U1MODEbits.ALTIO = 1; //alternate the output pin to pin 13
    
    U1MODEbits.UARTEN = 1;  // enable UART
    U1STAbits.UTXEN = 1; //and enable transmission (order important)
}
void WriteUART1 (char data)
{
    U1TXREG = data;
}

void WriteStringUART1(const char * s)
{
    while(*s)
    {
        while(U1STAbits.UTXBF);
        WriteUART1(*s++);
    }
}

void WriteIntUART( unsigned value )
{
    char poscnt[30];
    sprintf(poscnt, "%u: \n", value);
    
    WriteStringUART1(poscnt);
}

void uartSendChar(char sending_value)
{
    U1TXREG = sending_value;
}

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    static char buffer[10];
    static int flag;
    //char temp_char;
    char temp_char[] = "a";
    // clear rx interrupt flag
    IFS0bits.U1RXIF = 0;
    temp_char[0] = U1RXREG;
    
    if (temp_char[0] == '<') 
    {
        memset(buffer, 0, sizeof buffer);
        flag = 1;
    }
    else if(temp_char[0] == '>')
    {
        flag = 0;

        WriteStringUART1(buffer);
        interpret(buffer);
    }
    else if (flag == 1)
    {
        strcat(buffer, temp_char);
    }
    //U1TXREG = U1RXREG;
    // U1RXREG buffer gets full after 4 characters and stops interrupt getting called
}

void interpret( char* command ){
    int motorDir = 0;
    
    switch(command[0]){
        case '+':
            motorDir = 1;
            break;
        case '-':
            motorDir = 0;
            break;
            
        default: 
            break;
    }
    
    setMotorLeftDir(motorDir);
    
    int value = 0;
    
    int index;

    for ( index = 1; command[index] != '\0'; index++) {
        value = value * 10 + (int) ( command[index] - '0');
    }
    char te = (char) value;
    WriteUART1(te);
    setLEFTDC( value );
}