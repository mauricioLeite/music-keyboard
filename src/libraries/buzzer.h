#include <stm32f10x.h>

#ifndef BUZZER_H
#define BUZZER_H

    void generate_sound ( int note, uint8_t octave, uint8_t cycle, uint32_t potentiometer );

    void off_sound ( void );

#endif
