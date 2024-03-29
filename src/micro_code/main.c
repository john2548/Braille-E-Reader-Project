/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f0xx.h"
#include "char_c.h"
#include "pin.h"
#include <stdint.h>
#include <stdio.h>

#define MAX_CELLS 1 // maximum number of cells per line
#define MAX_LINES 0 // maximum number of lines

// Things that should be done
//      * enable pins
//      * clear pins interrupt
//      * loops that run thru each pin in each cell
// The functions we should implement

void nano_wait(unsigned int n);
void enable_ports();
void init_exti();
void EXTI0_1_IRQHandler(); // for 'previous' button
void EXTI2_3_IRQHandler(); // for 'next' button
void update_pins(Char_c in, bool prev_raised[MAX_CELLS][6]);

void nano_wait(unsigned int n) {
    asm(    "        mov r0,%0\n"
            "repeat: sub r0,#83\n"
            "        bgt repeat\n" : : "r"(n) : "r0", "cc");
}

void enable_ports(){
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // enables port B
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN; // enables port B

    GPIOC->MODER &= ~0x3F3; // set pins 0, 2, 3, 4 to inputs
    GPIOC->PUPDR &= ~0xF0; // clear pins 2 and 3
    GPIOC->PUPDR |= 0xA0; // enable pull down resistors for pins 2 and 3

    GPIOB->MODER &= ~0xFFFFFF; // clear pins 0-23
    GPIOB->MODER |= 0x555555; // set pins 0-23 to output
}

void init_exti() {
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN; // enables SYSCFG subsystem

    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PB;
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PB;
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PB;
    SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI4_PB;

    EXTI->RTSR |= EXTI_RTSR_TR0; // produces an EXTI event on the rising edge of pin 0
    EXTI->RTSR |= EXTI_RTSR_TR2; // produces an EXTI event on the rising edge of pin 2
    EXTI->RTSR |= EXTI_RTSR_TR3; // produces an EXTI event on the rising edge of pin 3
    EXTI->RTSR |= EXTI_RTSR_TR4; // produces an EXTI event on the rising edge of pin 4

    EXTI->IMR |= EXTI_IMR_MR0; // initializes the interrupt mask register for pin 0
    EXTI->IMR |= EXTI_IMR_MR2; // initializes the interrupt mask register for pin 2
    EXTI->IMR |= EXTI_IMR_MR3; // initializes the interrupt mask register for pin 3
    EXTI->IMR |= EXTI_IMR_MR4; // initializes the interrupt mask register for pin 4

    NVIC->ISER[0] |= 0x7FFFF; // enables the ISER for the NVIC (i have no clue what the ISER reg. looks like)
}

void update_pins(Char_c in, bool prev_raised[MAX_CELLS][6]) {
	int pin_vals[12] = {0};
	int pin_out = 0;

	for(int i = 0; i < MAX_CELLS; i++) {
    	for(int j = 0; j < 6; j++) {
        	if(prev_raised[i][j] == in.pinOut[j].raised) { // pin already raised or lower so no motor movement
        		pin_vals[2*j] = 0;
        		pin_vals[2*j+1]= 0;
        	} else if(prev_raised[i][j] < in.pinOut[j].raised) { // raise pin case
        	    pin_vals[2*j] = 1;
        	    pin_vals[2*j+1]= 0;

        	    prev_raised[i][j] = in.pinOut[j].raised; // put raised into previous array
        	} else { // lower pin case
        	    pin_vals[2*j] = 0;
        	    pin_vals[2*j+1]= 1;

        	    prev_raised[i][j] = in.pinOut[j].raised; // put raised into previous array
        	}
        }

    	for(int i = 0; i < 12; i++) {
    		pin_out |= (pin_vals[i] << i);
    	}
    	GPIOB->ODR &= ~0xFFFF;
    	GPIOB->ODR |= pin_out;
    }
}

int main(void)
{
//    bool sample_a[6] = {1,0,0,0,0,0};
//    bool sample_n[6] = {1,0,1,1,1,0};
    bool sample_n[6] = {0,0,0,0,0,0};
//    bool sample_n[6] = {1,1,1,1,1,1};
//	bool sample_n[6] = {1,0,1,0,1,0};
//    bool prev_raised[1][6] = {{0,0,0,0,0,0}};
    bool prev_raised[1][6] = {{1,1,1,1,1,1}};
//	bool prev_raised[1][6] = {{0,1,0,1,0,1}};
//    char char_a = 'a';
    char char_n = 'n';
//    Char_c a = createChar(char_a, sample_a);
    Char_c n = createChar(char_n, sample_n);

    enable_ports();
    update_pins(n, prev_raised);

}
