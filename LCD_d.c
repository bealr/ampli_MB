#include "LCD_d.h"
#include "I2C_d.h"
#include <xc.h>

/*
 * PCF8574AT
 * P0 -> RS
 * P1 -> RW
 * P2 -> E
 * P3 -> LED
 * P4 -> D4
 * P5 -> D5
 * P6 -> D6
 * P7 -> D7
 */

char reg_pcf;

#define CMD  0x0
#define DATA 0x1

void set_E()
{
    reg_pcf |= 0x04;
    write_pcf(reg_pcf);
}

void unset_E()
{
    reg_pcf &= 0xFB;
    write_pcf(reg_pcf);
}

void set_RS()
{
    reg_pcf |= 0x01;
    write_pcf(reg_pcf);
}

void unset_RS()
{
    reg_pcf &= 0xFE;
    write_pcf(reg_pcf);
}

void set_RW()
{
    reg_pcf |= 0x02;
    write_pcf(reg_pcf);
}

void unset_RW()
{
    reg_pcf &= 0xFD;
    write_pcf(reg_pcf);
}

void backlight_on()
{
    reg_pcf |= 0x08;
    write_pcf(reg_pcf);
}

void backlight_off()
{
    reg_pcf &= 0xF7;
    write_pcf(reg_pcf);
}


void set_data(char data)
{
    reg_pcf &= 0x0F;
    reg_pcf |= data;
    write_pcf(reg_pcf);
}

void write_pcf(char data)
{
    I2C_write(PCF_addr, 0, data&0x0F);
}

void LCD_init()
{
    int i;
    reg_pcf = 0;    
    I2C_write(PCF_addr, 0, 0);
    for (i=0;i<100;i++) __delay_ms(10);
    LCD_init_write(0x30);
    __delay_ms(10);
    LCD_init_write(0x30);
    __delay_ms(10);
    LCD_init_write(0x30);
    __delay_ms(10);
    LCD_init_write(0x20);
    
    __delay_ms(10);
    LCD_write(0x04, CMD); // cursor at begin
    
}

void LCD_init_write(char data)
{
    set_data(data>>4);
    set_E();
    __delay_ms(1);
    unset_E();
}

void LCD_write(char data, char mode)
{
    if (mode)
        set_RS();
    
    set_data(data>>4);
    set_E();
    __delay_ms(1);
    unset_E();
    
    __delay_ms(1);
    
    set_data(data);
    set_E();
    __delay_ms(1);
    unset_E();
    
    unset_RS();
}

void LCD_write_car(char data)
{
    LCD_write(data, DATA);
}

void LCD_write_str(const char *data)
{
    while(*data != '\0')
    {
        LCD_write_car(*data);
        data++;
    }
}