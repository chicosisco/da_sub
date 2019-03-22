/*
 * DA2C_3b.c
 *
 * Created: 3/20/2019 6:05:48 PM
 * Author : Francisco mata carlos
 */ 


#define F_CPU 16000000UL   /* clock runs at 16 MHz*/
#include <avr/io.h>
#include <avr/interrupt.h>
int over_flow=0;

int main()
{
	DDRC &= (0<<2);
	PORTC |=(1<<2);  //enable pull-up
	
	DDRB |=0x10;   //make PB4 an output
	PORTB |= (1<<DDB4);
	OCR0A = 0;   // compare register value
	TCCR0B |=(1<<CS02)|(1<<CS00);    // prescaler = 256
	TCCR0A |=(1<<WGM01);   // CTC mode
	TIMSK0 = (1<<OCIE0A);  // enable Timer 0 compare match interrupt
	sei();      // enable global interrupt

	while (1)
	{
		
	}
}

// every time there's a match with the comparator register
// it jumps into this comparator interrupt
ISR (TIMER0_COMPA_vect)
{
	while (1) 
     {
			  
		if (!(PINC & (1<<PINC1))) //checking if pinc is high and complement by 
								  //pressing on the switch
		 {
			
			 while (1) 
			{
				//wait for the overflow event
				while ((TIFR0 & 0X02)==0);
				TCNT0=0X00;     //resetting counter to zero
				TIFR0=0X02;     // reset the overflow flag
				
				over_flow++;    //increasing overflow counter
		       
				// if overflow is less than or equal to 1 cycle the LED on PB4
				// turns off and stays off once it breaks
				if (over_flow<=1)
				{
				PORTB = (1<<DDB4);
				break; 
			    }
				
				else   { 
				PORTB = (0<<DDB4);       //  turn on LED on PB4 until over_flow count
										 //  resets again
				
	                   }
				if (over_flow==77) {
					over_flow=0;         //resetting overflow counter
					
				                    }	
										  
			}
			 			  
		}
		  
    //return 0;
    }
	
}
	