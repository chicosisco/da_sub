
/*
 * DA2C_2a
 *
 * Created: 3/17/2019 11:55:51 PM
 * Author : Francisco Mata Carlos
 */ 

#define F_CPU 16000000   /* clock runs at 16 MHz*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
int over_flow=0;

int main()
{
	
    DDRB |=(1<<DDB4);  // setting PB1 as output
	TIMSK0 |= (1<<TOIE0);
	TCNT0 = 0; // setting initial value for counter
	sei();     // enable interrupts
	TCCR0B |=(1<<CS02);  // setting prescaler to 256
	
	
    while (1) 
    {
		
		//main loop
    }
}
	
	ISR(TIMER0_OVF_vect) // timer_0 overflow interrupt
	{
		while (!(TIFR0 & 0X01)==0);
		TCNT0=0X00;  //resetting counter to zero
		TIFR0=0X01;  // reset the overflow flag
		over_flow++;  //increasing overflow counter
		
		// if overflow is equal to 71 cycles turn on LED on PB4	
		if (over_flow>=71){
		PORTB = (0<<DDB4);
		}
		else 
		PORTB = (1<<DDB4);  // or turn off LED on PB4
		
		if (over_flow==178) {
			over_flow=0; //resetting overflow counter
			} 
		
	}
	
		
		