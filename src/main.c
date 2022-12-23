#include <stdio.h>
#include <stm32f10x.h>
#include "starter.h"
#include "lcd.h"
#include "utils.h"
#include "keys.h"
#include "buzzer.h"

/* Functions prototypes */
void start_keyboard( void );
void octave_check( void );
void cycle_check( void );
void keys_check( void );

/* Control variables */
static uint8_t octave, sound, cycle;

int main() {
    setup_peripherals();
    delay_us(1);
    start_keyboard();

    while (1) {
        octave_check();
        cycle_check();
        keys_check();
    }

}

/* Logical functions */

// Set initial state os control variables and print message
void start_keyboard() {
    octave = 1;
    sound = 0;
    cycle = 25;
    lcd_first_line("Oitava: 1");
    set_cycle(&cycle);
}

// Check if the octave is updated by user
void octave_check() {
    int selected = 0;
    char octave_text[10];

    if (check_port('B', 12) == 1) selected = 1;
    if (check_port('B', 13) == 1) selected = 2;
    
    if (selected != 0) {
        octave = (uint8_t) selected;
        snprintf(octave_text, 10, "Oitava: %d", octave);
        lcd_first_line(octave_text);
    }
}

// Check if cycle is updated by user
void cycle_check() {
    if (check_port('B', 14) == 0) return;
    
    if (cycle == 75) cycle = 25;
    else cycle += 25;

    set_cycle(&cycle);
    delay_ms( 100 );
}

// Check if user click any key or change potentiometer state
void keys_check() {
    uint32_t potentiometer;

    int key = read_switch();
    if ( key == -1 ) {
        if (sound == 0) off_sound();
        sound = 0;
        return;
    }

    potentiometer = read_potentiometer();
    generate_sound(key, octave, cycle, potentiometer);
    sound = 1;
}
