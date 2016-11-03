/* 
 * File:   selecter.c
 * Author: rbeal
 *
 * Created on November 1, 2016, 1:41 PM
 */

#include <xc.h>
#include "selecter.h"
#include "I2C_d.h"

void init_selecter(void)
{
    I2C_write(ADDR_SEL, 0x00,0x00);
}

void move_selecter(char pos)
{
    switch(pos)
    {
            case SELECTER_E1:
            I2C_write(ADDR_SEL, 0x00,0x0C);
            break;
            
            case SELECTER_E2:
            I2C_write(ADDR_SEL, 0x00,0x30);
            break;
            
            case SELECTER_E3:
            I2C_write(ADDR_SEL, 0x00,0x03);
            break;
            
            case SELECTER_E4:
            I2C_write(ADDR_SEL, 0x00,0xC0);
            break;
            
        default :
            I2C_write(ADDR_SEL, 0x00,0x00);
            break;
    }
}