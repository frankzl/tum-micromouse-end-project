/* 
 * File:   MotorFunctions.h
 * Author: Natalia
 *
 * Created on 07 December 2018, 14:23
 */

#ifndef MOTORFUNCTIONS_H
#define	MOTORFUNCTIONS_H

#include "xc.h"
#include <p33Fxxxx.h>

 #define   LEFT_DIR_A LATBbits.LATB9 //DIR_A for Motor LEFT
 #define   LEFT_DIR_B LATCbits.LATC6 //DIR_B for Motor LEFT

 #define   RIGHT_DIR_A LATAbits.LATA7 //DIR_A for Motor RIGHT
 #define   RIGHT_DIR_B LATBbits.LATB14 //DIR_B for Motor RIGHT


void motorLeftSetup();
void motorRightSetup();

void setMotorLeftDir( int );
void setMotorRightDir( int );

void changeMotorDir();

#endif	/* MOTORFUNCTIONS_H */

