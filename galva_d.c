#include <xc.h>
#include "galva_d.h"

void galva_init(void)
{
    CCPTMRS0bits.C1TSEL = 0b00; // tmp on TMR2
    
    // Timer2
    T2CONbits.T2OUTPS = 0b0000; // Postscaler : 1:1
    T2CONbits.T2CKPS = 0b10; // 1:16 -> 1MHz input
    
    CCP1CONbits.CCP1M = 0b1100; // PWM mode
    
    CCPR1L = 0b11100000;     // 8 MSB duty cycle
    CCP1CONbits.DC1B = 0b00; // 2 LSB duty cycle
    
    PIR1bits.TMR2IF = 0;
    
    T2CONbits.TMR2ON = 1; // TMR2 : On
    
    TRISCbits.RC2 = 0;
}

void galva_set(char val)
{
    unsigned value;
    value = val * 4;
    
    CCPR1L = (value>>2)&0xFF;
    CCP1CONbits.DC1B = value&0x03;
}