/* 
 * File:   I2C_d.h
 * Author: rbeal
 *
 * Created on October 10, 2016, 6:59 PM
 */

#ifndef I2C_D_H
#define	I2C_D_H

void I2C_init(void);
void I2C_write(char addr_i2c, char addr, char data);
void I2C_busy(void);
void wait_ack(void);

#endif	/* I2C_D_H */

