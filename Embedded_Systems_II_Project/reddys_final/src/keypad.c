#include "keypad.h"
#include "gpio.h"

#define GPIOC_MODE (0x55)

void key_init(){
	//Enable Clock for port C
	(*RCC_AHB1ENR)|=(1<<GPIOC_RCC_IDX);

	//clear rows and columns, and input mode to columns
	(GPIOC->MODER)&=~(0xFFFF);

	//enable output mode for rows
	(GPIOC->MODER)|=(GPIOC_MODE<<8);

	//enable pull up pull down register for row
	(GPIOC->PUPDR)&=~(0xFF);
	(GPIOC->PUPDR)|=(0x55);
}

uint8_t getkey_noblock(){


	uint8_t column_value=0;
    int keypressed=0;
    int col;//column number

// scan by alternating input signal. 0111, 1011, 1101, 1110
	for (int r=0; r<4;r++) {
		//CLEAR MY ROWS
		(GPIOC->ODR)&=~(0xF<<4);
		// creates 4 bit test signal
		uint8_t test_value = ~(1<<(r+4));
		//write to odr
		(GPIOC->ODR)|= test_value;
		// check columns.
		column_value = (GPIOC->IDR & 0xF);
       delay_1ms(1);
		if((column_value & 0xF) != 0xF) {
			if(column_value==0b0111){
					col=3;
				}
				if(column_value==0b1011){
					col=2;
				}
				   if(column_value==0b1101){
					   col=1;
				   }
				  if(column_value==0b1110){
					  col=0;
				  }
				  keypressed=r*4+(col+1); // calculates which key is pressed
		}
	  col=0;
	}
	      delay_1ms(18);
		  return keypressed;
}

// this function is used to get a key when there is no blocking

uint8_t key_getkey(){
	int keypressed=0;
	while(keypressed!=0){
		keypressed=getkey_noblock();
	}
	while(keypressed==0){
		keypressed=getkey_noblock();
	}
	delay_1ms(100);
	return keypressed;
}
//decides which character based on key press
uint8_t key_getchar(){
int keypressed= key_getkey();
 char getchar;
     if( keypressed==1){
    	getchar='1';
     }
     else if(keypressed==2){
        getchar='2';
     }
     else if(keypressed==3){
    	 getchar='3';
     }
     else if(keypressed==4){
    	 getchar='A';
     }
     else if(keypressed==5){
    	 getchar='4';
     }
     else if(keypressed==6){
         	 getchar='5';
          }
     else if(keypressed==7){
         	 getchar='6';
          }
     else if(keypressed==8){
         	 getchar='B';
          }
     else if(keypressed==9){
         	 getchar='7';
          }
     else if(keypressed==10){
         	 getchar='8';
          }
     else if(keypressed==11){
         	 getchar='9';
     }
     else if(keypressed==12){
         	 getchar='C';
         	     }
     else if(keypressed==13){
         	 getchar='*';
          }
     else if(keypressed==14){
         	 getchar='0';
          }
     else if(keypressed==15){
         	 getchar='#';
          }
     else if(keypressed==16){
         	 getchar='D';
          }
     return getchar;
}
