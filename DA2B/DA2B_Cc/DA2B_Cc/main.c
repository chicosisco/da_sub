
/* This C code creates an interruption on PORTD2 of 1.25s, and this is shown 
 * by the LED2 turning off for about 1.25s. The assignment is requesting for
 * LED on PB2 to turn on, however LED on PB2 is burnt and not working, which is
 * the reason for using LED on PB4
 * DA2B_C.c
 *
 * Created: 3/9/2019 12:50:59 AM
 * Author : Francisco Mata Carlos
 */

#define F_CPU 16000000UL // clock
#include <avr/io.h>   //header files
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
	
	DDRB = (1<<4) ; //PB4 as an output
	DDRB = 0XFF;
	PORTB = 0xFF;  // setting portb high, which turns led off
	PORTD = 1<<2; //pull-up activated
	EICRA = 0x2;  //make INT0 falling edge triggered
  
	EIMSK= (1<<INT0);  // enable external interrupt 0
	sei ();    // enable interrupt
   
	 
while (1)
	{        //waiting for interruption
	}
	}
	ISR (INT0_vect)  // ISR for external interrupt 0
{
	PORTB ^= (1<<4);   //toggle PORTB4
	_delay_ms(1250);   // 1.25s delay
}

