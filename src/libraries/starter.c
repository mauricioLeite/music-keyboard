#include <stm32f10x.h>
#include "starter.h"
#include "lcd.h"
#include "utils.h"

void GPIO_setup(void);
void ADC_setup(void);
void GPT_setup(void);

void GPIO_setup() {
    /* -- Config GPIO A, B and C -- */
    
    // PA6 and PA5 as output 
    GPIOA->CRL = 0x43344444; 
    // PA15, PA12, PA11 and PA8 as output 
    GPIOA->CRH = 0x34433443; 

    /* Config switches as inputs
       PB1 potentiometer as analog input
       PB0 as alternating function */
    GPIOB->CRL = 0x3344430B;
    // Config switches as inputs
    GPIOB->CRH = 0x44444444; 
    // Config switches as inputs
    GPIOC->CRL = 0x44433333;
}

void ADC_setup() {
    /* -- Config A/D conversor -- */
    
    // Use channel 9 as input
    ADC1->SQR3 = 9;
    // Enable ADC
    ADC1->CR2 = 1;	
    // Set SMP1 
    ADC1->SMPR2 = (1 << 3); 
    delay_us(1);
}

void setup_peripherals ( void ) {
    // Disable JTAG interface
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

    // Active clocks to GPIO ports
    RCC->APB2ENR |= 0xFC | (1<<9);
    // Enable TIM3 clock
	RCC->APB1ENR |= (1<<1); 

    GPIO_setup();
    ADC_setup();

    lcd_init();
    delay_ms(100);
}
