#include <stm32f10x.h>
#include "keys.h"
#include "utils.h"

// Map GPIO port by switch
static uint8_t GPIO_map[13] = {'B', 'B', 'B', 'A', 'B', 'A', 'C', 'A', 'C', 'B', 'C', 'B', 'B'};

// Map switchs
static uint8_t SW_map[13] = {5, 10, 4, 7, 3, 3, 15, 4, 14, 8, 13, 9, 11};		

// Read switchs and return if pressed
int read_switch() {
    for ( int i = 0; i < 13; i++) {
        if (check_port(GPIO_map[i], SW_map[i]) == 1) return i;
    }
    return -1;
}

// Read potentiometer and convert to digital data
uint32_t read_potentiometer() {
    // Use channel 9 as input
    ADC1->SQR3 = 9;
    // Enable ADC
    ADC1->CR2 = 1;	
    // Wait state registry update after conversion
    while((ADC1->SR & (1<<1)) == 0);
    // Return data
    return ADC1->DR; 
}
