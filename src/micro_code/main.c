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
void update_pins(Char_c in, bool prev_raised[MAX_CELLS][6]);

void nano_wait(unsigned int n) {
    asm(    "        mov r0,%0\n"
            "repeat: sub r0,#83\n"
            "        bgt repeat\n" : : "r"(n) : "r0", "cc");
}

void enable_ports(){
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // enables port B

    GPIOB->MODER &= ~0xFF; // clear pins 0-3
    GPIOB->MODER |= 0x55; // set pins 0-3 to output
}

void update_pins(Char_c in, bool prev_raised[MAX_CELLS][6]) {
    for(int i = 0; i < MAX_CELLS; i++) {
        for(int j = 0; j < 6; j++) {
            // put raised into pin 3
            switch(j) {
                case 0: if(prev_raised[i][j] == in.pinOut[j].raised) {
                            break;
                        } else if(prev_raised[i][j] < in.pinOut[j].raised) {
                            GPIOB->ODR &= 0xF; // clears pins 0-3
                            GPIOB->ODR |= (1 << 3) | 0x1; // raise pin i
                            nano_wait(2000000000);
                            GPIOB->ODR &= ~0xF; // clears pins 0-3
                        } else {
                            GPIOB->ODR &= 0xF; // clears pins 0-3
                            GPIOB->ODR |= (0 << 3) | 0x1; // lower pin i
                            nano_wait(4000000000);
                            GPIOB->ODR &= ~0xF; // clears pins 0-3
                        }

                        break;
                case 1: if(prev_raised[i][j] == in.pinOut[j].raised) {
                            break;
                        } else if(prev_raised[i][j] < in.pinOut[j].raised) {
                            GPIOB->ODR &= 0xF; // clears pins 0-3
                            GPIOB->ODR |= (1 << 3) | 0x2; // raise pin i
                            nano_wait(2000000000);
                            GPIOB->ODR &= ~0xF; // clears pins 0-3
                        } else {
                            GPIOB->ODR &= 0xF; // clears pins 0-3
                            GPIOB->ODR |= (0 << 3) | 0x2; // lower pin i
                            nano_wait(4000000000);
                            GPIOB->ODR &= ~0xF; // clears pins 0-3
                        }

                        break;
                case 2: if(prev_raised[i][j] == in.pinOut[j].raised) {
                            break;
                        } else if(prev_raised[i][j] < in.pinOut[j].raised) {
                            GPIOB->ODR &= 0xF; // clears pins 0-3
                            GPIOB->ODR |= (1 << 3) | 0x3; // raise pin i
                            nano_wait(2000000000);
                            GPIOB->ODR &= ~0xF; // clears pins 0-3
                        } else {
                            GPIOB->ODR &= 0xF; // clears pins 0-3
                            GPIOB->ODR |= (0 << 3) | 0x3; // lower pin i
                            nano_wait(4000000000);
                            GPIOB->ODR &= ~0xF; // clears pins 0-3
                        }

                        break;
                case 3: if(prev_raised[i][j] == in.pinOut[j].raised) {
                            break;
                        } else if(prev_raised[i][j] < in.pinOut[j].raised) {
                            GPIOB->ODR &= 0xF; // clears pins 0-3
                            GPIOB->ODR |= (1 << 3) | 0x4; // raise pin i
                            nano_wait(2000000000);
                            GPIOB->ODR &= ~0xF; // clears pins 0-3
                        } else {
                            GPIOB->ODR &= 0xF; // clears pins 0-3
                            GPIOB->ODR |= (0 << 3) | 0x4; // lower pin i
                            nano_wait(4000000000);
                            GPIOB->ODR &= ~0xF; // clears pins 0-3
                        }

                        break;
                case 4: if(prev_raised[i][j] == in.pinOut[j].raised) {
                            break;
                        } else if(prev_raised[i][j] < in.pinOut[j].raised) {
                            GPIOB->ODR &= 0xF; // clears pins 0-3
                            GPIOB->ODR |= (1 << 3) | 0x5; // raise pin i
                            nano_wait(2000000000);
                            GPIOB->ODR &= ~0xF; // clears pins 0-3
                        } else {
                            GPIOB->ODR &= 0xF; // clears pins 0-3
                            GPIOB->ODR |= (0 << 3) | 0x5; // lower pin i
                            nano_wait(4000000000);
                            GPIOB->ODR &= ~0xF; // clears pins 0-3
                        }

                        break;
                case 5: if(prev_raised[i][j] == in.pinOut[j].raised) {
                            break;
                        } else if(prev_raised[i][j] < in.pinOut[j].raised) {
                            GPIOB->ODR &= 0xF; // clears pins 0-3
                            GPIOB->ODR |= (1 << 3) | 0x6; // raise pin i
                            nano_wait(2000000000);
                            GPIOB->ODR &= ~0xF; // clears pins 0-3
                        } else {
                            GPIOB->ODR &= 0xF; // clears pins 0-3
                            GPIOB->ODR |= (0 << 3) | 0x6; // lower pin i
                            nano_wait(4000000000);
                            GPIOB->ODR &= ~0xF; // clears pins 0-3
                        }

                        break;
                default: GPIOB->ODR &= ~0xF; // clears pins 0-3
                        break;
            }
        }
        *prev_raised[i] = in.pinOut->raised;
    }
}

int main(void)
{
    bool sample_a[6] = {1,0,0,0,0,0};
    bool prev_raised[MAX_CELLS][6] = {{0,0,0,0,0,0}};
    char char_a = 'a';
    Char_c a = createChar(char_a, sample_a);

    update_pins(a, prev_raised);

}
