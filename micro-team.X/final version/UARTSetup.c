#include "UARTSetup.h"
#include "MotorControl.h"
#include "PWMSetup.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
   
    U1BRG = 42;            //choose appropriate baud rate (57.6 kbit/s)
    U1MODEbits.LPBACK = 0; //disable loopback mode
    U1MODEbits.WAKE = 0;    //do not wake-up on serial activity (don?t care)
    U1MODEbits.ABAUD = 0;   // no auto-baud detection
    U1MODEbits.PDSEL = 0;   // clear (8 databits, no parity)
    U1MODEbits.STSEL = 0;   //clear one stop bit
    U1STAbits.URXISEL = 0;  // clear (receive interrupt when 1 character arrives)
    
    IFS0bits.U1RXIF = 0;    // clear rx interrupt flag
    IFS0bits.U1TXIF = 0;    // clear tx interrupt flag
    IPC2bits.U1RXIP = 6;    //set receive interrupt priority
    IEC0bits.U1RXIE = 1;    // enable receive interupts
    IEC0bits.U1TXIE = 0;    // disable transmit interrupts
    
    // U1MODEbits.ALTIO = 1; //alternate the output pin to pin 13
    
    U1MODEbits.UARTEN = 1;  // enable UART
    U1STAbits.UTXEN = 1;    //and enable transmission (order important)
}

// Sends a single character through UART
void WriteCharUART1 (char data)
{
    while(U1STAbits.UTXBF); //wait if buffer is full 
    U1TXREG = data;         //Write char to send
}

// Sends a string through UART
void WriteStringUART1(const char * s)
{
    // iterate through the string
    while(*s)
    {
        while(U1STAbits.UTXBF);
        WriteCharUART1(*s++);
    }
}

//Interpret the absolute value as int
int format( char* command )
{
    int value = 0;
    sscanf(command, "%d", &value);   
    return(value);
}

void WriteIntUART( unsigned value )
{
    char poscnt[30];
    sprintf(poscnt, "%u: \n", value);
    
    WriteStringUART1(poscnt);
}

//Receive interrupt (currently for every received character)
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    static char buffer[10]; // stores the complete received string
    static int flag;        // flag = 1 when we are receiving a string (in the sequence: <>)
    char *response = "Received:";
    char temp_char[] = "a";
    
    // clear rx interrupt flag
    IFS0bits.U1RXIF = 0;
    // toggle LED2
    // LED2 = ~LED2;        
    
    //Read content of receiver 
    temp_char[0] = U1RXREG;
    
    if (temp_char[0] == '<') 
    {
        //start of string
        memset(buffer, 0, sizeof buffer); //empty buffer
        flag = 1;
    }
    else if(temp_char[0] == '>')
    {   
        //end of string
        flag = 0;
        int drive_level=format(buffer);
        motorDriveLeft(drive_level);
        WriteStringUART1(response);
        WriteStringUART1(buffer);
    }
    else if (flag == 1)
    {   
        // We received a meaningful char, so store it
        strcat(buffer, temp_char); //concatenate
    }
    
}

