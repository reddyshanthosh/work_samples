/*
 * led.c
 *
 *  Created on: Dec 1, 2018
 *      Author: livingston
 */


#include "led.h"
#include "delay.h"
#include <inttypes.h>
#include <stdio.h>

//enable clock with a 1
#define GPIOB_RCC_IDX 1

// In GPIOB_MODER setting all the pins to output mode(0b01)
#define GPIOB_LED_MODES 0b01010101000101010101010000000000

//current speed
static uint8_t led_speed;

//function call to calculate delay
static uint32_t speedToDelay(uint8_t speed);
/*
 * Initializing all led's
 * enabling clock
 * setting Moder to output mode
 */
void led_init(){
	// Enable clock
	(*RCC_AHB1ENR)|=(1<<GPIOB_RCC_IDX);
	// Set modes for PB5 to PB15 (output, 0b01)(excluding PC11)
	*(GPIOB_MODER)|=(GPIOB_LED_MODES);
}

//In GPIOB_ODR turning on all pins by sending a 1 from pb5 to pb15 and a zero pc11
#define GPIOB_LED_ON 0b11110111111
/*
 * Turning all leds
 */
void led_allOn(){
	//Insert code here (Hint use ODR)
	//protect other pins
	(*GPIOB_ODR)|=(GPIOB_LED_ON << 5);
}

/*
 * Turning off all leds
 *
 */
void led_allOff(){
	//Insert code here (Hint use ODR)
	//protect other pins
	(*GPIOB_ODR) &= ~(GPIOB_LED_ON << 5);
}


/*
 * led_on()
 * 		Args: 0-9 to turn on specific led
 * 		print error message is arg is out of range
 */
void led_on(uint8_t ledIndex){
	//Insert code here (Hint use BSRR may be helpful)
	if( ledIndex >= 6){
	(*GPIOB_ODR)|= (1 << (5 + (ledIndex+1)));
	}
	else
	{
		(*GPIOB_ODR)|= (1 << (5 + (ledIndex)));
	}
}
/*
 * Turns off led based on ledIndex
 */
void led_off(uint8_t ledIndex){
	//Insert code here (Hint use BSRR may be helpful)
	if( ledIndex >= 6){
		(*GPIOB_ODR)&= ~(1 << (5 + (ledIndex+1)));
		}
		else
		{
			(*GPIOB_ODR)&= ~(1 << (5 + (ledIndex)));
		}
}

/*
 * led_scan()
 * 		Scan the light across and back at the current speed
 */
void led_scan(){
	//delay time is calculated here based on the current speed
	 uint32_t delaytime = speedToDelay(led_speed);
//loop for scanning light across
for ( uint8_t i = 0; i<10 ; i++){
	//i is the index
	led_on(i);
	led_off(i-1);
	delay_1ms(delaytime);
  }
//loop for scanning light backwards
	for( int i=10; i >= 0; i--){
			led_on(i);
			led_off(i+1);
			delay_1ms(delaytime);
	}
}
/*
 * led_flash()
 * 		flash all of the lights 10 times at the current speed
 */
//gpiob_led_on1 is the bit pattern for to turn on all led's ( pb5 to pb10 and pb12 to pb16)
// all ones from pb5 t0 pb 16, except for pb11 which is a zero
#define GPIOB_LED_ON1 0b11110111111
void led_flash(){
	//Insert code here
    uint32_t delaytime = speedToDelay(led_speed);
	for(  int i=0; i<10; i++) {
		(*GPIOB_ODR)|=(GPIOB_LED_ON1 << 5);
		delay_1ms(delaytime);
		(*GPIOB_ODR) &= ~(GPIOB_LED_ON1 << 5);
		delay_1ms(delaytime);
	 }
}

/*
 * led_setSpeed (uint8_t speed)
 * 		arg: speed (0 slow - 9 fast)
 * 		Args out of range should print error to console
 */
void led_setSpeed(uint8_t speed){
	//Insert code here

	led_speed = speed;
}

/*
 * led_incSpeed()
 * 		increases the speed by one
 * 		if maxed out leaves the speed at the max value
 */
void led_incSpeed(){
	//Insert code here
	if(led_speed < 9){
	led_speed++;
	}
}
/*
 * led_decSpeed()
 * 		decreases the speed by one
 * 		if at zero should stay at zero
 */
void led_decSpeed(){
	//Insert code here
	if(led_speed > 0){
	led_speed--;
    }
}

/*
 * getCurrentSpeed
 * 		returns the current speed
 */

uint8_t getCurrentSpeed()
{
	//Insert code here
	return led_speed;
}
/*
 * speedToDelay
 * calculates the time to delay
 * return delay_time
 * max delay 100ms and min delay 10ms
 *
 */
static uint32_t speedToDelay(uint8_t speed) {
	uint32_t delay_time;
	if( speed <= 9)  {
     	uint32_t max_delay= 100;
		uint32_t min_delay= 10;
		// 9 is maximum speed and 0 is minimum speed
		 delay_time= max_delay - (speed* (max_delay - min_delay))/9;
	}
	return delay_time;

}

