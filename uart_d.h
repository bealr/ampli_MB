/* 
 * File:   uart_d.h
 * Author: rbeal
 *
 * Created on October 15, 2016, 11:22 AM
 */

#ifndef UART_D_H
#define	UART_D_H

void UART_init_uart_esp(void);
void UART_esp_write(char data);
char UART_esp_read(void);
void UART_esp_process(char data);

#endif	/* UART_D_H */

