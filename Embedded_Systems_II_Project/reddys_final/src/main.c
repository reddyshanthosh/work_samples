/*
 * main.c
 *
 *  Created on: Feb 9, 2019
 *      Author: reddys
 */
#include <stdio.h>
#include <stdlib.h>
#include "uart_driver.h"
#include "delay.h"
#include "lcd.h"
#include "led.h"
#include "keypad.h"
#include "gpio.h"
#include "buzzer.h"
#include "rotary.h"

#define F_CPU 16000000UL
#define ARSIZE 10
//tells which direction the rotary moves
static int direction = 0;
//tells which row the cursor should move
static int row = 0;
//decide the row when menu displays option 3 and 4
static int last_row = 0;
// main
int main(void) {
	//initialization of all components
	init_usart2(19200, F_CPU);
	lcd_init();
	lcd_clear();
	init_buzzer();
	key_init();
	led_init();
	init_rotary();
//used to print option 3 and 4 only once on the lcd
	int print2 = 0;
//used to print option 1 and 2 only once on the lcd
	int print1 = 0;
//decides whethers the menu is displaying option 1,2 or option 3,4
	int choice = 0;
	while (1) {
		if (last_row == row && row == 1) {
			//prints menu with option 3 and 4
			if (print2 == 0) {
				lcd_clear();
				lcd_set_position(0, 0);
				lcd_print_string("3.Alternatelights");
				lcd_set_position(1, 0);
				lcd_print_string("4.All lights on");
				lcd_set_position(0, 0);
				//decides that it is option 2
				print2 = 1;
				print1 = 0;
				//tells that it is option 2
				choice = 2;
			}
		}
		//prints menu with option 1 and 2
		else if (last_row == row && row == 0) {
			if (print1 == 0) {
				lcd_clear();
				lcd_set_position(0, 0);
				lcd_print_string("1.Scan Lights");
				lcd_set_position(1, 0);
				lcd_print_string("2.Flash Lights");
				lcd_set_position(0, 0);
				//decides that it is option 1
				print1 = 1;
				print2 = 0;
				//tells that it is option 1
				choice = 1;
			}
		}
		//waits for the user to enter
		uint8_t key = getkey_noblock();
		//15 is the '#' key or the enter key
		if (key == 15) {
			//if I am at option 1,2 then following code executes
			if (choice == 1) {
				led_allOff();
				if (row == 0) {
					led_scan();
				} else if (row == 1) {
					led_flash();
				}
			}
			//if i am at option 3,4 then following code executes
			else if (choice == 2) {
				led_allOff();
				if (row == 0) {
					led_on(1);
					led_on(3);
					led_on(5);
					led_on(7);
					led_on(9);
				} else if (row == 1) {
					led_allOn();
				}
			}
		}
	}
}

void EXTI0_IRQHandler(void) {
	//printf("Pass");
	//lcd_print_string("pass");
	if ((*(EXTI_PR ) & (0x1)) != 0) {
		delay_1ms(10);
		//disable interupt
		*(EXTI_PR ) |= (0x1);
		last_row = row;
		if (((GPIOA->IDR) & 0x2) == 0x2) {
			//ENCODER IN CLOCKWISE DIRECTION
			direction = direction + 1;
			if (direction > 2) {
				direction = 0;
			}
			//produces a beep sound as i scroll the menu
			play_tone(400, 10, 1);
			//moves to the next row
			row = 1;
			lcd_set_position(row, 0);
			printf("right\n");
		} else {
			//ENCODER IN ANTICLOCKWISE DIRECTION
			direction = direction - 1;
			if (direction < 0) {
				direction = 2;
			}
			play_tone(400, 10, 1);
			//moves to above row
			row = 0;
			lcd_set_position(row, 0);
			printf("left\n");
		}

	}
	stop_tone(0);
	delay_1ms(10);
}

