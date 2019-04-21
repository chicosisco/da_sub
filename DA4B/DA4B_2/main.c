/*
 * DA4B_2.c
 *
 * Created: 4/20/2019 12:36:51 AM
 * Author : Francisco Mata
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// Function Prototypes
void initial(void);   // function setting Timer/Counter control Register 0
void adc_init(void);  // function declared for ADC set up


int main(void)
{
	
    while (1) 
    {
		initial();      // calling function to initialize the setting Timer/Counter control Register 0
		adc_init();     // calling function for ADC set up
		ICR1=4999;
		DDRB|=(1<<PB1);	
		OCR1A=ADC;      // reading from potentiometer to control servo angle
		_delay_ms(10);
    }
}

// Clear OC1A/OC1B on compare match (set output to low leverl)
// Mode = 14, Fast PWM
//pre-scaler = 64
void initial(void)
{
	TCCR1A |= (1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);
	TCCR1B |= (1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10);
}
	

// function to initialize ADC set up
void adc_init(void)
{
	ADCSRA |= ((1<<ADEN)|(1<<ADSC)|(0<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
	ADMUX |= (1<<REFS0);
}
