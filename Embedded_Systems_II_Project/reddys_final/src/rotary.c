/*
 * rotary.c
 *
 *  Created on: Feb 9, 2019
 *      Author: reddys
 */
#include "rotary.h"
#include "gpio.h"
#include "lcd.h"
#include <inttypes.h>
#include <stdio.h>


void init_rotary() {
	//enable clcok for GPIOA
	*(RCC_AHB1ENR ) |= (1<<GPIOA_RCC_IDX);

	//Enable clock for SYSCFG
	 *(RCC_APB2ENR ) |= 0x1 << 14;

	//Set PA0 and PA1 to input
	(GPIOA->MODER) &= ~(0xF);

	//Set PA0 and PA1 to pull up
	(GPIOA->PUPDR) &= ~(0xF);
	(GPIOA->PUPDR) |= (0x5);

	//Initialize Interupt

	//PA0 is connected to EXTI0
	//PA pin requires 0B0000
	*(SYSCFG_EXTICR1 ) &= ~(0xF);

	// Unmask NVIC at location 6
	*(NVIC_ISER0 ) |= 1 << 6;

	//unmask EXTIO in EXTI_IMR
	*(EXTI_IMR) |= 0x1;
	//need falling edge
	*(EXTI_FTSR ) |= 0x1;
}
/*
void getvalue(){
	//int encodervalue=(GPIOA->IDR)&0x2;
  while((*(EXTI_PR ) & (0x1)) != 0){
		//disable interupt
				*(EXTI_PR ) |= (0x1);
	  if (((GPIOA->IDR) & 0x2) == 0x2) {
	  			//ENCODER IN CLOCKWISE DIRECTION
	  			direction = direction + 1;
	  		} else {
	  			//ENCODER IN ANTICLOCKWISE DIRECTION
	  			direction = direction - 1;
	  		}
	}
}
*/
















