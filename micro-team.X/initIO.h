/* 
 * File:   initIO.h
 * Author: a2-lenz
 *
 * Created on May 8, 2018, 11:31 AM
 */
#include "xc.h"

#ifndef INITIO_H
#define	INITIO_H

#ifdef	__cplusplus
extern "C" {
#endif

#define LED0 LATAbits.LATA4
    
void initIO();
void initRemappable();

#ifdef	__cplusplus
}
#endif

#endif	/* INITIO_H */

