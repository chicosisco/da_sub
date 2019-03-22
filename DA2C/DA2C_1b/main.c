/*
 * DA2C_1b.c
 *
 * Created: 3/19/2019 5:00:50 PM
 * Author : Francisco Mata carlos
 */ 


#define F_CPU 16000000UL /* clock runs at 16 MHz*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
int over_flow=0;

int main(void)
{
	
	DDRC &= (0<<2);
	PORTC |=(1<<2); //enable pull-up
	
    DDRB |= (1<<DDB4); // PB4 as output
	PORTB |=(1<<DDB4); // Set PB2 high to keep LED off
	                   // as the starting position
	TCCR0A = 0; // normal operation.
	TCNT0 = 0;   //start timer/counter
	
	TCCR0B |=(1<<CS02)|(1<<CS00);  // setting prescaler to 1024

	while (1) 
   {
	
			  
		if (!(PINC & (1<<PINC1))) //checking if pinc is high and complement
		{
			 while (1) 
			{
				//wait for the overflow event
				while ((TIFR0 & 0X01)==0);
				TCNT0=0X00;  //resetting counter to zero
				TIFR0=0X01;  // reset the overflow flag
				
				over_flow++;  //increasing overflow counter
		
				// if overflow is less than or equal to 1 cycle the LED on PB4
				// turns off and stays off once it breaks
				if (over_flow<=1){
				PORTB = (1<<DDB4);
				break; 
				}
				
				else{ 
				PORTB = (0<<DDB4);  // or turn off LED on PB4
				//break; 
				}
				if (over_flow==76) {
					over_flow=0; //resetting overflow counter
				}					
			}			  
		}
			  
    //return 0;
    }
}