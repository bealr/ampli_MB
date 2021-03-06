#include <xc.h>
#include "I2C_d.h"

void I2C_init(void)
{
    TRISCbits.RC3 = 1;
    TRISCbits.RC4 = 1;
    ANSELCbits.ANSC3 = 0;
    ANSELCbits.ANSC4 = 0;
    SSP2CON1bits.SSPEN = 1;
    SSP1CON1 = 0b00101000;
    SSP1CON2 = 0;
    SSP1ADD  = 39;
    SSP1STAT = 0b10000000;
    /*
    //SSP1CON1 = 0b00101000; // mode I2C Master, pin configured
    SSP1CON1 = 0x38;
    SSP1CON2 = 0b00000000;
    //SSP1STAT = 0b10000000; // slew rate disabled, smbus disabled
    SSP1STATbits.CKE=1;
    SSP1STATbits.SMP=1;
    SSP1ADD  = 0x13;
    
    
    PIE1bits.SSP1IE = 1;
    */
}

void I2C_write(char addr_i2c, char addr, char data)
{
    I2C_busy();
    SSP1CON2bits.SEN = 1; // start bit
    while(SSP1CON2bits.SEN);
    
    I2C_busy();
    SSP1BUF = 0x7E; // write mode
    
    I2C_busy();
    SSP1BUF = data; // data
    
    I2C_busy();
    SSP1CON2bits.PEN = 1; // stop bit
    while(SSP1CON2bits.PEN);
    
    __delay_ms(5);
}

void I2C_busy(void)
{
    while((SSP1CON2 & 0x1F) || (SSP1STAT & 0x04));
}