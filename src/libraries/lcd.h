#include <stm32f10x.h>

#ifndef LCD_H
#define LCD_H

    void lcd_init ( void ); 
    void lcd_command ( unsigned char cmd ); 
    void lcd_first_line( char * str );
    void lcd_second_line( char * str );
    void lcd_data ( unsigned char data );
    void lcd_print ( char * str );
    void lcd_putValue ( unsigned char value ); 

    void delay_us ( uint16_t t ); 
    void delay_ms ( uint16_t t );
    
#endif
