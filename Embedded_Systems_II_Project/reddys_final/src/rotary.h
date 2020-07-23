/*
 * Created on: 2/08/2019
 * Author: reddys
 */

#ifndef ROTARY_H_
#define ROTARY_H_

#define SYSCFG_EXTICR1 (volatile uint32_t*) 0x40013808

#define EXTI_IMR (volatile uint32_t*) 0x40013C00

#define EXTI_FTSR (volatile uint32_t*) 0x40013C0C

#define EXTI_PR (volatile uint32_t*) 0x40013C14

#define NVIC_ISER0  (volatile uint32_t*) 0xE000E100

#define NVIC_ISER1  (volatile uint32_t*) 0xE000E104

//FUNCTIONS
extern void init_rotary();
extern void EXTI0_IRQHandler();
//extern void getvalue();
#endif /*ROTARY_H_*/
