//Include Guards (More to come)
#ifndef keypad_H_
#define keypad_H_

#include <inttypes.h>

void key_init();

uint8_t getkey_noblock();

uint8_t key_getkey();

uint8_t key_getchar();

#endif
