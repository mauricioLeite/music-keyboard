#include <stm32f10x.h>
#include "lcd.h"

#define LCD_RS 15
#define LCD_EN 12


void lcd_putValue ( unsigned char value ) {
    uint16_t aux ; 

    aux = 0x0000 ; 
    GPIOA -> BRR = (1 <<5)|(1 <<6)|(1 <<8)|(1 <<11); 
    aux = value & 0xF0 ;
    aux = aux >>4;
    GPIOA -> BSRR = (uint32_t) (( aux &0x0008 ) <<8) | (uint32_t) (( aux &0x0004 ) <<3) | (uint32_t) (( aux &0x0002 ) <<5) | (uint32_t) (( aux &0x0001 ) <<8);
    GPIOA -> ODR |= (1 << LCD_EN ); 
    delay_ms (3); 

    GPIOA -> ODR &= (uint32_t) ~(1 << LCD_EN );
    delay_ms (1); 

    GPIOA -> BRR = (1 <<5)|(1 <<6)|(1 <<8)|(1 <<11); 
    aux = 0x0000 ; 
    aux = value & 0x0F ;
    GPIOA -> BSRR = (uint32_t) (( aux &0x0008 ) <<8) | (uint32_t) (( aux &0x0004 ) <<3) | (uint32_t) (( aux & 0x0002 ) <<5) | (uint32_t) (( aux &0x0001 ) <<8);
    GPIOA -> ODR |= (1 << LCD_EN );
    delay_ms (3);

    GPIOA -> ODR &= (uint32_t) ~(1 << LCD_EN );
    delay_ms (1);
}

void lcd_command ( unsigned char cmd ) {
    GPIOA -> ODR &= (uint32_t) ~(1 << LCD_RS );
    lcd_putValue ( cmd );
}


void lcd_data ( unsigned char data ){
    GPIOA -> ODR |= (1 << LCD_RS );
    lcd_putValue ( data );
}

void lcd_first_line ( char * str ) {
    lcd_command(0x80);
    lcd_print(str);
}

void lcd_second_line ( char * str ) {
    lcd_command(0xC0);
    lcd_print(str);
}

void lcd_print ( char * str ) {
    unsigned char i = 0;

    while ( str [ i ] != 0) {
        lcd_data ( str [ i ]);
        i ++;
    }
}

void lcd_init (){
    delay_ms (15);
    GPIOA -> ODR &= (uint32_t) ~(1 << LCD_EN );
    delay_ms (3);
    lcd_command (0x33 );
    delay_ms (5);
    lcd_command (0x32 );
    delay_us (3000);
    lcd_command (0x28 );
    delay_ms (3);
    lcd_command (0x0e );
    delay_ms (3);
    lcd_command (0x01 );
    delay_ms (3);
    lcd_command (0x06 );
    delay_ms (3);
    // TODO: Change color, but working only on line 1 (???)
    /*
    lcd_command (0x20 );
    delay_ms (3);
    */
}

void delay_us ( uint16_t t ) {
    volatile unsigned long l = 0;
    for ( uint16_t i = 0; i < t ; i ++){
        for ( l = 0; l < 6; l ++) {
        }
    }
}

void delay_ms ( uint16_t t ) {
    volatile unsigned long l = 0;
    for ( uint16_t i = 0; i < t ; i ++){
        for ( l = 0; l < 6000; l ++) {
        }
    }
}
