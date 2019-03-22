#include "ADCFunctions.h"
#include <xc.h>

void startADC1(void)
{
        AD1CON1bits.ADON=1; //set on-bit
        AD1CON1bits.ASAM=1;
}

void setupADC1()
{
    //ADCON1
    AD1CON1bits.ADON = 0;       // disable ADC1 module
    AD1PCFGL = 0xfeaf;          //0b1111 1110 1010 1111; 		//  AN4,6 and 7 set as analog inputs
    
    AD1CON1bits.ADSIDL=0;       //no sampling in idle mode
    AD1CON1bits.ADDMABM=1;      //DMA channels are written in order of conversion
                                // The module provides an address to the DMA channel
                                //that is the same as the address used for the non-DMA stand-alone buffer
    AD1CON1bits.AD12B=1;        //12-bit, 1-channel ADC operation
    AD1CON1bits.FORM=0b00;      //format is unsigned integer
    AD1CON1bits.SSRC=0b111;     //see comment below for options
            
             //   SSRC (Sample Clock Source Select bits) options:
             //   111 = Internal counter ends sampling and starts conversion (auto-convert)
             //   110 = Reserved
             //   101 = Motor Control PWM2 interval ends sampling and starts conversion
             //   100 = GP timer (Timer5 for ADC1) compare ends sampling and starts conversion
             //   011 = Motor Control PWM1 interval ends sampling and starts conversion
             //   010 = GP timer (Timer3 for ADC1) compare ends sampling and starts conversion
             //   001 = Active transition on INT0 pin ends sampling and starts conversion
             //   000 = Clearing sample bit ends sampling and starts conversion

    AD1CON1bits.ASAM=0;         //sampling starts not immediately after last conversion but when SAMP bit is set
    AD1CON1bits.SAMP=0;         //bit is automatically set if ASAM=1 (auto-sampling)

    //ADCON2
    AD1CON2bits.VCFG=0b000;     //select Vref+ and Vref- as internal reference voltage
    AD1CON2bits.CSCNA=1;        //enable analog input SCAN on channel CH0
    AD1CON2bits.SMPI=2;         //Selects Increment Rate for DMA Addresses bits or number of sample/conversion operations per interrupt
                                // set to 2 because we scan 3 channels
    AD1CON2bits.BUFM=0;         //always fill buffer starting at address 0x00
    AD1CON2bits.ALTS=0;         //always use channel A and do not alternate

    //ADCON3
    AD1CON3bits.ADRC=0;         // use internal clock source
    AD1CON3bits.SAMC=0x05;      //auto sample time bits, number of Tad
                                //only valid when SSRC=0b111
                                //minimum 3*tad=3*117.6=352.8ns=0.35us
                                //Tacq=5*Tad=1us
    AD1CON3bits.ADCS=0x07 ;     //8-bits to derive ADC clock
                                //Tad= TCY * (ADCS<7:0> + 1) = TCY*8 = 8/40M= 200ns
                                // Datasheet sets Tad minimum at 117.6ns
                                //total conversion time (12 bits)= 14*Tad=2.8us

    //ADCON4
    AD1CON4bits.DMABL=0b000;    //<2:0>: Selects Number of DMA Buffer Locations per Analog Input bits (0:1 word)


    //AD1CSSL (input scan select register)
    AD1CSSL=0b0000000101010000; //select the analog channels 4,6 and 8

    //interrupt configuration
    IFS0bits.AD1IF = 0;
    IEC0bits.AD1IE = 0;         //disable interrupt 
    IPC3bits.AD1IP = 5;
}
