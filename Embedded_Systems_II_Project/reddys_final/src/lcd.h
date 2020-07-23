//Include Guards (More to come)
#ifndef LCD_H_
#define LCD_H_

#include <inttypes.h>


/*
 * led_init()

 * This function should:
 * 		1. Enable the GPIOB in RCC_AHB1ENR
 * 		2. Turn on to set LED0 - LED9 to output mode ("01")
 */
void lcd_init();

void lcd_write_data(uint8_t data);

void lcd_write_cmd(uint8_t rwe, int delay_us);

void lcd_clear();

void cursor_displayshift(int a, int b);

void lcd_home();

void lcd_set_position(uint8_t r1, uint8_t c1);

void set_ddram_address(uint8_t address);

void lcd_write_ddram(char character);

void lcd_print_string(char *string);

void lcd_advance_cursor();

uint8_t lcd_read_ddram();

void lcd_print_string(char *string);

void lcd_print_num(int number);

#endif
