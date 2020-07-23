/*
 * led.c
 *  CE 2801 021
 *  Author: Shanthosh Reddy
 */

/*
 * led.c
 *  CE 2801 021
 *  Author: Shanthosh Reddy
 */
#include "lcd.h"
#include "delay.h"
#include <inttypes.h>
#include <stdio.h>
#include "gpio.h"

/*
 * Initializing all led's

 * enabling clock
 * setting rows to output mode
 * Setting columns to input mode
 */

#define GPIOA_MODES (0x5555<<8)
#define GPIOC_MODES (0x15<<16)

static void lcd_config(int RS, int RW);

void lcd_init() {
	// Enable clock for port A
	(*RCC_AHB1ENR ) |= (1 << GPIOA_RCC_IDX);
	//Enable Clock for port C
	(*RCC_AHB1ENR ) |= (1 << GPIOC_RCC_IDX);

	//Enable GPIOA_MODER: PC[4:11]
	(GPIOA->MODER) &= ~(0xFFFF << 8);
	GPIOA->MODER |= GPIOA_MODES;
	//Enable GPIOC_MODER
	GPIOC->MODER &= ~(0x3F << 16);
	GPIOC->MODER |= GPIOC_MODES;

	delay_1ms(40);

	// function set command
	lcd_write_cmd(0x38, 37);

	//function set command
	lcd_write_cmd(0x38, 37);

	// display on
	lcd_write_cmd(0x0F, 37);

	// clear display
	lcd_write_cmd(0x01, 1520);

	// entry mode set, moves cursor to right
	lcd_write_cmd(0x06, 37);
}
static int r0 = 0;
static int c0 = 0;
void lcd_set_position(uint8_t r1, uint8_t c1) {

	uint8_t index[2][16] = { { 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
			0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F }, { 0xC0, 0xC1,
			0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC,
			0xCD, 0xCE, 0xCF } };
	uint8_t cmd = index[r1][c1];

	lcd_write_cmd(cmd, 37);
}

void set_ddram_address(uint8_t address) {
	address &= 0x07F;
	//db7 is a 1 so 0x80
	lcd_write_cmd(0x80 | address, 37);
}
uint8_t lcd_read_ddram() {
	uint8_t read_address = 0;
	//setting it to read mode
	lcd_config(1, 1);
	//7F because AC0 to AC6
	read_address = (GPIOA->IDR) & (0x7F);
	return read_address;
}

void lcd_write_ddram(char character) {
	lcd_write_cmd(0b101, 37);
}

static void lcd_config(int RS, int RW) {
	// data guard, only 1 bit
	RS &= 1;
	RW &= 1;
	// write RS and RW to LCD
	GPIOC->ODR &= ~(0b11 << 8);
	GPIOC->ODR |= (RS << 8);
	GPIOC->ODR |= (RW << 9);

}
void lcd_write_data(uint8_t data) {

	lcd_config(1, 0);

	(GPIOC->ODR) |= (0b1 << 10);

	// write data
	GPIOA->ODR &= ~(0xFF << 4);
	GPIOA->ODR |= (data << 4);

	//Enable low
	(GPIOC->ODR) &= ~(0b1 << 10);
	delay_1us(37);
}

void lcd_write_cmd(uint8_t cmd, int delay_us) {

	lcd_config(0, 0);
	(GPIOC->ODR) |= (0b1 << 10);

	GPIOA->ODR &= ~(0xFF << 4);
	GPIOA->ODR |= (cmd << 4);
	//Enable low
	(GPIOC->ODR) &= ~(0b1 << 10);

	if (delay_us > 0) {
		delay_1us(delay_us);
	}
}

void lcd_clear() {
	lcd_write_cmd(0x01, 1520);
}

#define home_databits 0b00000010
void lcd_home() {
	lcd_write_cmd(home_databits, 1520);
}

void cursor_displayshift(int a, int b) {
	a &= 1; //to make sure it is one bit
	b &= 1; // to make sure it is one bit
	//0x10 is opcode and a,b are the variables
	lcd_write_cmd(0x10 | (a << 3) | (b << 4), 37);
}

void lcd_print_string(char *string) {
	while (*string) {
		lcd_write_data(*string);
		//lcd_set_position(r0,c0+1);
		string++;
	}
}
//if cursor at (0,15) then it should move to (1,0)
void lcd_advance_cursor() {
	if (c0 >= 15) {
		lcd_set_position(r0 + 1, c0);
	}
}
void lcd_print_num(int number) {
	char buffer[100];
	//integer to Ascii, 10 represents decimal
	itoa(number, buffer, 10);
	lcd_print_string(buffer);
	//lcd_set_position(r0,c0+1);
}

