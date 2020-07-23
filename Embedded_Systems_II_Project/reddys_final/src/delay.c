/*
 * delay.c
 *
 * Starter Code
 */

#include <inttypes.h>
#include "delay.h"  //include declaration header file
/*
 * delay_1ms
 * 		Busy wait for n ms
 *
 * 		For n iterations
 * 			load number of cycles for 1 ms
 * 			set one to enable and clock source
 *
 * 			wait for countflag to be set
 */
void delay_1ms(uint32_t n){
//Insert code here
for(uint32_t i=0; i<n; i++) {
    //Loading ticks for 1ms
	*(STK_LOAD)=16000;

	*(STK_CTRL)= (1<<EN)|(1<<CLKSOURCE);

	int done=0;
	int flagVal;

	while( done==0) {
		flagVal= *(STK_CTRL) & (1<<COUNTFLAG);
				if( flagVal == (1<<COUNTFLAG)) {
					done = 1;
				}
      	}
}
}

void delay_1us(uint32_t n){
//Insert code here
for(uint32_t i=0; i<n; i++) {
    //Loading ticks for 1us
	*(STK_LOAD)=16;

	*(STK_CTRL)= (1<<EN)|(1<<CLKSOURCE);

	int done=0;
	int flagVal;

	while( done==0) {
		flagVal= *(STK_CTRL) & (1<<COUNTFLAG);
				if( flagVal == (1<<COUNTFLAG)) {
					done = 1;
				}
      	}
     }
}



