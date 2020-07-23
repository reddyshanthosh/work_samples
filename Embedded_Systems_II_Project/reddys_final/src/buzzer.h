/*
  * main.c
 *
 *  Created on: Jan 20, 2019
 *      Author: reddys
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include <inttypes.h>

typedef struct {
uint32_t cr1;
uint32_t cr2;
uint32_t smcr;
uint32_t dier;
uint32_t sr;
uint32_t egr;
uint32_t ccmr1;
uint32_t ccmr2;
uint32_t ccer;
uint32_t cnt;
uint32_t psc;
uint32_t arr;
uint32_t ccr1;
uint32_t ccr2;
uint32_t ccr3;
uint32_t ccr4;
uint32_t dcr;
uint32_t dmar;
}timer;

#define timer3 ((volatile timer*)0x40000400)


extern void init_buzzer();
extern void play_tone(int,int,int);
extern void stop_tone(int);
#endif
