/*
 * DA2C.c
 *
 * Created: 3/17/2019 3:25:11 AM
 * Author : Francisco Mata carlos
 */ 

#define F_CPU 16000000UL    /* clock runs at 16 MHz*/
#include <avr/io.h>
#include<util/delay.h>


int main()

{
	int over_flow=0; //over-flow counter
	
	DDRB |= (1<<DDB4); // PB4 as output
	TCCR0A = 0; // normal operation.
	TCNT0 = 0x00;   //start timer/counter
	
	TCCR0B |=(1<<CS02);  // setting prescaler to 256

    while (1) 
    {
	  
		//wait for the overflow event
		while ((TIFR0 & 0X01)==0);
		TCNT0=0X00;  //resetting counter to zero
		TIFR0=0X01;  // reset the overflow flag
		over_flow++;  //increasing overflow counter
		
		// if overflow is equal to 71 cycles turn on LED on PB4	
		if (over_flow>=71){
		PORTB = (0<<DDB4);
		}
		else 
		PORTB = (1<<DDB4);  // or turn off LED on PB4
		
		if (over_flow==177) {
			over_flow=0; //resetting overflow counter
			} 
		}
    }


