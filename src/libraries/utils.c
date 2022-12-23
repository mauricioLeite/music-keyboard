#include <stm32f10x.h>
#include "utils.h"

// Check user activity based on port and bits
char check_port( char port, char bits ) {
    switch (port) {
        case('A'):
            return !((GPIOA->IDR) & (1 << bits));
        case('B'):
            return !((GPIOB->IDR) & (1 << bits));
        case('C'):
            return !((GPIOC->IDR) & (1 << bits));
    }
}

// Set new cycle message
void set_cycle( uint8_t * percentage ) {
    char cycle_text[10];
    if ( *percentage != 25 && *percentage != 50 && *percentage != 75) *percentage = 25;
    snprintf(cycle_text, 10, "Ciclo: %d", *percentage);
    lcd_second_line(cycle_text);
}

