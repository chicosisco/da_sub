
/*
 * DA2C_3a
 *
 * Created: 3/17/2019 11:55:51 PM
 * Author : Francisco Mata Carlos
 */ 


#define F_CPU 16000000UL   /* clock runs at 16 MHz*/
#include <avr/io.h>
#include <avr/interrupt.h>
int over_flow=0;

int main()
{
	DDRB |=0x10;   //make PB4 an output
	OCR0A = 128;   // compare register value
	TCCR0B |=(1<<CS02);    // prescaler = 256
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
	
		//wait for the overflow event
		while ((TIFR0 & 0X02)==0);
		TCNT0=0X0;  //resetting counter to zero
		TIFR0=0X02;  // reset the overflow flag
		over_flow++;  //increasing overflow counter
		
		// if overflow is equal to 71 cycles turn on LED on PB4	
		if (over_flow>=71){
		PORTB = (0<<DDB4);
		}
		else 
		PORTB = (1<<DDB4);  // or turn off LED on PB4
		
		if (over_flow==175) {
			over_flow=0; //resetting overflow counter
			} 
		}
	