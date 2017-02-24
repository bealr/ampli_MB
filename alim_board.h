/* 
 * File:   alim_board.h
 * Author: rbeal
 *
 * Created on February 24, 2017, 2:27 PM
 */

#ifndef ALIM_BOARD_H
#define	ALIM_BOARD_H

#define ADDR_ALIM 0x14
#define ALIM_OFF 0
#define ALIM_ON  1

void init_alim_board();
void switch_alim_pui(char state);
void switch_alim_pre(char state);

#endif	/* ALIM_BOARD_H */

