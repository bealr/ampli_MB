#include <xc.h>
#include "I2C_d.h"

/* --- ADDRESS ---
 * LCD  : 0x3F
 * ALIM : 0x14
 * SELE : 0x38
 
 */


void I2C_init(void)
{
    TRISCbits.RC3 = 1;
    TRISCbits.RC4 = 1;
    ANSELCbits.ANSC3 = 0;
    ANSELCbits.ANSC4 = 0;
    SSP1CON1 = 0b00101000;
    SSP1CON2 = 0;
    SSP1ADD  = 254;
    SSP1STAT = 0b10000000;
    
    SSP2CON1bits.SSPEN = 1;
}

void I2C_write(char addr_i2c, char addr, char data)
{
    SSP1CON2bits.SEN = 1; // start bit
    I2C_busy();
    
    SSP1BUF = (addr_i2c<<1) & 0xFE; // write mode
    I2C_busy();
    wait_ack();
    
    SSP1BUF = addr; // addr
    I2C_busy();
    wait_ack();
    
    SSP1BUF = data; // data
    I2C_busy();
    wait_ack();
    
    SSP1CON2bits.PEN = 1; // stop bit
    I2C_busy();
}

char I2C_read(char addr_i2c, char addr)
{
    char tmp;
    
    SSPCON2bits.SEN = 1; // start bit
    I2C_busy();
    
    SSPBUF = (addr_i2c<<1) & 0xFE; // write mode
    I2C_busy();
    wait_ack();
    
    SSPBUF = addr; // addr
    I2C_busy();
    wait_ack();
    
    SSPCON2bits.PEN = 1; // stop bit
    I2C_busy();
    
    SSPCON2bits.RSEN = 1; // Restart bit
    I2C_busy();
    
    
    SSPBUF = addr_i2c | 0x01; // read mode
    I2C_busy();
    wait_ack();
    
    SSPCON2bits.RCEN = 1;
    I2C_busy();
    
    tmp = SSPBUF;
    SSPCON2bits.ACKDT = 0;
    SSPCON2bits.ACKEN = 1;
    while(SSPCON2bits.ACKEN == 1);
    
    SSPCON2bits.PEN = 1; // stop bit
    I2C_busy();
    
    return tmp;
}

void I2C_busy(void)
{
    while((SSP1CON2 & 0x1F) || (SSP1STAT & 0x04));
}

void wait_ack(void)
{
    char timeout=100;
    
    while (!SSP1CON2bits.ACKSTAT && timeout)
    {
        timeout--;
        __delay_us(1);
    }
}