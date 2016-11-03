/* 
 * File:   selecter.h
 * Author: rbeal
 *
 * Created on November 1, 2016, 1:41 PM
 */

#ifndef SELECTER_H
#define	SELECTER_H

#define ADDR_SEL 0x38

#define SELECTER_NONE 0x0
#define SELECTER_E1   0x1
#define SELECTER_E2   0x2
#define SELECTER_E3   0x3
#define SELECTER_E4   0x4


void init_selecter(void);
void move_selecter(char pos);

#endif	/* SELECTER_H */

