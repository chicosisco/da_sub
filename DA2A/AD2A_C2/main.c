/*   
 * This C code generates a 1.25s pulse when a push down switch is pressed. The switch (S2) is
 * pressed it creates a pulse that is demonstrated by using an LED. The LED turns on for 
 * about 1.25 seconds, which is the requirement for this assignment. 
 *
 *
 * AD2A_C2.c
 *
 * Created: 3/2/2019 1:24:19 PM
 * Author : Francisco Mata Carlos
 */ 

  
#define F_CPU 16000000UL   /* clock runs at 16 MHz*/
	
#include <avr/io.h>   
#include <util/delay.h>

int main(void)
{
	/* set PORTB2 for output */
	DDRB |= (1<<2);
	PORTB |=(1<<2); // led off
	/* set PORTC2 for input */
	DDRC &= (0<<2);
	PORTC |=(1<<2);  //enable pull-up
   
   
    while (1) {
		if (!(PINC & (1<<PINC1))) //checking if pinc is high and complement
		{
			PORTB &= ~(1<<2); // turn led on because sending a zero to the connection
			_delay_ms(1250);  // 1.25s delay
		}
		
		else
			PORTB |= (1<<2); // keep PORTB2 high 
	}
    return 0;
}


