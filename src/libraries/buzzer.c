#include <stm32f10x.h>
#include "buzzer.h"

static uint16_t notes_first[13] = { 132, 140, 148, 157, 166, 176, 187, 198, 209, 222, 235, 249, 132 };

// Scale factor choose for project
static uint16_t pre_scaler = 10;
//Default clock for AHB Bus
static uint32_t default_f_clk = 72000000;

void generate_sound ( int note, uint8_t octave, uint8_t cycle, uint32_t potentiometer ) {
    uint16_t frequency = ( octave == 1 )? notes_first[note] : 2*notes_first[note];

    // Compute reference value to compare with TIM3_CNT
    // N = f_clk /(2*fn + (pot/100))
    uint16_t N = (uint16_t) ((default_f_clk / pre_scaler) / ((2*frequency + (potentiometer/100.0))));
    
    // PW1 Mode
    TIM3->CCMR2 = 0x0060;  
    // Set 1 on CC3E - Enable output buffer
    TIM3->CCER = ( 1 << 8 );
    // Set clock frequency 100kHz
    TIM3->PSC = pre_scaler - 1;	
    // Pulse frequency
    TIM3->ARR = N - 1;
    // Pulse Width
    TIM3->CCR3 = (uint16_t) (N * (cycle / 100.0));

    // Enable timer
    TIM3->CR1 = 1;	
}

void off_sound () {
    // Disable output buffer
    TIM3->CCER = 0;
}
