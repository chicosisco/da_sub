/*This C code generates a waveform with a period of 0.725s; 60% duty cycle. It sets the PB2 with a 1 value which causes the led to turn off.
 * This is due to the reason that VDD is connected to the LED and then a resistor, which is connected to pin B2. Thus, when PB2 is high the 
 * voltage drop across the resistor and LED is minimum, and the LED turns off. But if PB2 is low then there's a voltage drop across the LED 
 * resistor which causes to turn it on. To make a 60% duty cycle, a 435ms on time is given to the PB2 and then an off time of 290ms.
 *
 * DA2A.c
 *
 * Created: 3/2/2019 1:15:16 PM
 * Author : Francisco Mata Carlos
 */ 


#define F_CPU 16000000UL			/* clock runs at 16 MHz*/

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 0x04;       /* sets PORTB as output */
	
	while(1)
	{
		PORTB = (1 << 2);		/* sets PB2 high */
		_delay_ms(435);				/* time that the led is  (60% DC with 0.725s period) */
		PORTB = ~(1 << 2);		/* displays output */
		_delay_ms(290);				/* time that the led is on (40% DC with 0.725s period) */
	}
	return 0;
}
