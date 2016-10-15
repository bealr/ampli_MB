/* 
 * File:   LCD_d.h
 * Author: rbeal
 *
 * Created on October 10, 2016, 7:42 PM
 */

#ifndef LCD_D_H
#define	LCD_D_H

#define PCF_addr 0x7E

void LCD_init();
void LCD_init_write(char data);
void LCD_write(char data, char mode);

void set_E();
void unset_E();
void set_RS();
void unset_RS();
void set_RW();
void unset_RW();
void backlight_on();
void backlight_off();
void set_data(char data);
void write_pcf(char data);
void LCD_write_car(char data);
void LCD_write_str(const char *data);
void LCD_cursor(char x, char y);
void LCD_clear();

#endif	/* LCD_D_H */

