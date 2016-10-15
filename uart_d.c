#include <xc.h>
#include "uart_d.h"


char buff_uart_esp[20];
char process_state;
char process_count;

extern char interrupt_soft;

void UART_init_uart_esp(void)
{
    //TRISCbits.RC6 = 0; // Rx
    //TRISCbits.RC7 = 1; // Tx
    ANSELCbits.ANSC6 = 0;
    ANSELCbits.ANSC7 = 0;
    
    /*
     * 8 bit mode
     * Transmit enabled
     * Asynchronous mode
     * BRGH = 1
     * SPEN = 1
     * Receive enabled
     * BRG16 = 1
     */
    
    TXSTA1 = 0b00100100;
    RCSTA1 = 0b10010000;
    BAUDCON1 = 0b00000000;
        
    SPBRG1 = 34;
    SPBRGH1 = 0;
    
    PIE1bits.RCIE = 1;
    IPR1bits.RC1IP = 1;
    process_state=0;
    }

void UART_esp_write(char data)
{
    PIR1bits.TXIF = 0;
    TXREG1 = data;
    while(!PIR1bits.TXIF);
}

char UART_esp_read(void)
{
    return RCREG1;
}

void UART_esp_process(char data)
{
    switch (data)
    {
        case '$': // begin
            process_state = 1;
            process_count = 0;
            LATA6 = 1;
            break;
            
        case '#': // end
            if (process_state)
            {
                process_state = 0;
                LATA6 = 0;
                *(buff_uart_esp+process_count) = '\0';
                interrupt_soft |= 0x1;
            }
            break;
            
        default : // data or garbage
            if (process_state)
            {
                *(buff_uart_esp+process_count) = data;
                process_count++;
            }
            break;
    }
}