/* 
 * File:   alim_board.c
 * Author: rbeal
 *
 * Created on February 24, 2017, 2:27 PM
 */

#include "alim_board.h"
#include "I2C_d.h"

void init_alim_board() {
    switch_alim_pui(ALIM_OFF);
    switch_alim_pre(ALIM_OFF);
}

void switch_alim_pui(char state) {
    
    if (state)
        I2C_write(ADDR_ALIM, 0x00, 0x01);
    else
        I2C_write(ADDR_ALIM, 0x00, 0x00);
}


void switch_alim_pre(char state) {

    if (state)
        I2C_write(ADDR_ALIM, 0x01, 0x01);
    else
        I2C_write(ADDR_ALIM, 0x01, 0x00);
}
