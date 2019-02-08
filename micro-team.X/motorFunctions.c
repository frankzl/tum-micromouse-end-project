#include <p33Fxxxx.h>

#include "motorFunctions.h"

void motorLeftSetup()
{
   // motor pins
    LEFT_DIR_A = 1;
    LEFT_DIR_B = 0;
}

void motorRightSetup()
{    
   // motor pins
    RIGHT_DIR_A = 1;
    RIGHT_DIR_B = 0;
}


void setMotorLeftDir( int direction )
{
    // save motor from burning
    LEFT_DIR_A = 0;
    LEFT_DIR_B = 0;

    // revert direction
    if ( direction == 1) {
        LEFT_DIR_A = 0;
        LEFT_DIR_B = 1;
    }
    else
    {
        LEFT_DIR_A = 1;
        LEFT_DIR_B = 0;
    }
}

void setMotorRightDir( int direction )
{
    // save motor from burning
    RIGHT_DIR_A = 0;
    RIGHT_DIR_B = 0;

    // revert direction
    if ( direction == 1) {
        RIGHT_DIR_A = 0;
        RIGHT_DIR_B = 1;
    }
    else
    {
        RIGHT_DIR_A = 1;
        RIGHT_DIR_B = 0;
    }
}

void changeMotorDir()
{
    int dirA = LATBbits.LATB2;
    int dirB = LATBbits.LATB3;
    
    // save motor from burning
    LATBbits.LATB2 = 0;
    LATBbits.LATB3 = 0;

    // revert direction
    if (dirA == 1) {
        LATBbits.LATB2 = 0;
        LATBbits.LATB3 = 1;
    }
    else if(dirB == 1)
    {
        LATBbits.LATB3 = 0;
        LATBbits.LATB2 = 1;
    }
}
