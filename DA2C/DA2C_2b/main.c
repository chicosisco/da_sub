/*
 * DA2C_2b.c
 *
 * Created: 3/20/2019 1:57:38 PM
 * Author : Francisco Mata Carlos
 */ 


#define F_CPU 16000000   /* clock runs at 16 MHz*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
int over_flow=0;

int main()
{
	DDRC &= (0<<2);
	PORTC |=(1<<2); //enable pull-up
	
	DDRB |=(1<<DDB4);     // setting PB4 as output
	PORTB |=(1<<DDB4);    // set PB2 high to keep D2 LED off, as starting state
	TIMSK0 |= (1<<TOIE0);
	TCNT0 = 0;            // setting initial value for counter
	sei();                // enable interrupts
	TCCR0B |=(1<<CS02)|(1<<CS00);   // setting prescaler to 1024
	
	
	while (1)
	{
	
	}
}

ISR(TIMER0_OVF_vect)     // timer_0 overflow interrupt
{
	while (1) 
     {
			  
		if (!(PINC & (1<<PINC1))) //checking if pinc is high and complement by 
								  //pressing on the switch
		 {
			
			 while (1) 
			{
				//wait for the overflow event
				while ((TIFR0 & 0X01)==0);
				TCNT0=0X00;     //resetting counter to zero
				TIFR0=0X01;     // reset the overflow flag
				
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


