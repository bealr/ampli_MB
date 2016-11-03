/*
 * File:   main.c
 * Author: rbeal
 *
 * Created on October 10, 2016, 5:49 PM
 */

// CONFIG1H
#pragma config FOSC = INTIO67   // Oscillator Selection bits (Internal oscillator block)
#pragma config PLLCFG = ON      // 4X PLL Enable (Oscillator multiplied by 4)
#pragma config PRICLKEN = ON    // Primary clock enable bit (Primary clock is always enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRTEN = OFF     // Power-up Timer Enable bit (Power up timer disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 190       // Brown Out Reset Voltage bits (VBOR set to 1.90 V nominal)

// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer Enable bits (Watch dog timer is always disabled. SWDTEN has no effect.)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTB3  // CCP2 MUX bit (CCP2 input/output is multiplexed with RB3)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<5:0> pins are configured as digital I/O on Reset)
#pragma config CCP3MX = PORTB5  // P3A/CCP3 Mux bit (P3A/CCP3 input/output is multiplexed with RB5)
#pragma config HFOFST = ON      // HFINTOSC Fast Start-up (HFINTOSC output and ready status are not delayed by the oscillator stable status)
#pragma config T3CMX = PORTB5   // Timer3 Clock input mux bit (T3CKI is on RB5)
#pragma config P2BMX = PORTC0   // ECCP2 B output mux bit (P2B is on RC0)
#pragma config MCLRE = EXTMCLR  // MCLR Pin Enable bit (MCLR pin enabled, RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled if MCLRE is also 1)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection Block 0 (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection Block 1 (Block 1 (002000-003FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection Block 0 (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection Block 1 (Block 1 (002000-003FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection Block 0 (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection Block 1 (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "I2C_d.h"
#include "LCD_d.h"
#include "uart_d.h"
#include "galva_d.h"
#include "selecter.h"

void init(void);
void soft_interrupt(void);

extern char buff_uart_esp[20];

// on a rien vu c'est pas une variable globale
char interrupt_soft=0;
/*
 * xxxxxxxx
 * |||||||| -> uart esp data available
 * |||||||  ->
 * ||||||   ->
 * |||||    ->
 * ||||     ->
 * |||      ->
 * ||       ->
 * |        ->
 * 
 */
// end of "on a rien vu"

void interrupt tc_int(void) // High priority interrupt
{
    GIE = 0;
    
    if (PIR1bits.RC1IF)
    {
        UART_esp_process(UART_esp_read());
        PIR1bits.RC1IF = 0;
    }
    
    GIE = 1;
}
 
void interrupt low_priority LowIsr(void) // Low priority interrupt
{
}

void main(void) {
    
    int i;
    
    init();
    I2C_init();
    LCD_init();
    UART_init_uart_esp();
    galva_init();
    init_selecter();
    
    backlight_on();
    LCD_cursor(4,2);
    LCD_write_str("La falaise!");
    LATA6 = 0;
    
    GIE = 1;
    PEIE = 1;
    
    __delay_ms(10);
    
    TRISD0 = 1; // reset On, pas propre !!
   
    galva_set(255);
    
    
    while (1) {
        
        if (interrupt_soft)
            soft_interrupt();
        
        LATA6 = 1;
        move_selecter(SELECTER_NONE);
        for (i=0;i<50;i++) __delay_ms(10);
        LATA6 = 0;
        move_selecter(SELECTER_E1);
        for (i=0;i<50;i++) __delay_ms(10);
        LATA6 = 1;
        move_selecter(SELECTER_E2);
        for (i=0;i<50;i++) __delay_ms(10);
        LATA6 = 0;
        move_selecter(SELECTER_E3);
        for (i=0;i<50;i++) __delay_ms(10);
        LATA6 = 1;
        move_selecter(SELECTER_E4);
        for (i=0;i<50;i++) __delay_ms(10);
        
        
        
    }
    
    return;
}


void init(void) {
    
    // oscillator mode 
    OSCCONbits.IRCF = 0b111; // 16MHz
    OSCCONbits.SCS  = 0b00;  // primary clock
    OSCCON2bits.PLLRDY = 1;
    OSCTUNEbits.PLLEN = 1;   // PLL enabled
    OSCTUNEbits.TUN   = 0b011111; // MFINTOSC max
    // normalement 64Mhz ...
    
    TRISAbits.RA6 = 0;
    TRISDbits.RD0 = 0;    // esp reset
    //ANSELDbits.ANSD0 = 0; // esp reset
    //LATD0 = 0;
}

void soft_interrupt(void)
{
    
    if (interrupt_soft&0x1) // uart esp data available
    {
        LCD_clear();
        LCD_write_str(buff_uart_esp);
        interrupt_soft &= 0xFE; // clear
    }
}