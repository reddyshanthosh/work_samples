#include <stdio.h>
#include "buzzer.h"
#include "gpio.h"


void init_buzzer(){
	//enable clock for timer
	*(RCC_APB1ENR)|= (GPIOB_RCC_IDX << 1);
	//enable clcok for gpiob
	*(RCC_AHB1ENR)|= (GPIOB_RCC_IDX << 1);
	//enable alternate function for pb4
	(GPIOB->AFRL)=(0b0010<<16);
	//alternate mode in moder
	//Clearing
	(GPIOB->MODER)&=~(0b11<<8);
	//set to alternate mode
	(GPIOB->MODER)|=(0b10<<8);

}

/*
 * this function plays the tone when counter is enabled
 * and delays(systick) went the counter is enabled
 */

void play_tone(int note_frequency, int duration, int counter_value){
	//16Mhz/ freequncy gives the no of ticks
	//no of ticks is sent to the auto reload register
	(timer3->arr)=16000000/(note_frequency);
	//no of ticks is sent to captur/compare mode register
	 (timer3->ccr1)=16000000/(note_frequency);
	 //Output mode toggle
	 (timer3->ccmr1)=(0b011<<4);
	 //set ccer to 1
	 (timer3->ccer)=1;

	 if(counter_value == 0){
		 //disable counter in bit0
		 (timer3->cr1)=0;
	 }
	 else{
		 //enable counter in bit0
		 (timer3->cr1)=1;
		  delay_1ms(duration/2);
	 }
 }
//stops the music by disabling the counter
void stop_tone(int counter){
	play_tone(0,0,0);
}
