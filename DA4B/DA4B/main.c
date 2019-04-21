/*
 * DA4B.c
 *
 * Created: 4/19/2019 7:43:28 PM
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
	int period;    // integer used to set the period
	
    while (1) 
    {
		initial();      // calling function to initialize the setting Timer/Counter control Register 0
		adc_init();     // calling function for ADC set up
		DDRB=0x0F;
		OCR0A = ADC;  
		  // setting the period to a value of 2, fast frequency
		if ((OCR0A>=0)&&(OCR0A<=20))
		{
		period =2 ;
		PORTB = 0x09;
		_delay_ms(period);
		PORTB = 0x03;
		_delay_ms(period);
		PORTB = 0x06;
		_delay_ms(period);
		PORTB = 0x0c;
		_delay_ms(period);
		}
		// setting the period to a value of 10
		else if((OCR0A>20)&&(OCR0A<=40))
		{
			period=10;
			PORTB = 0x09;
			_delay_ms(period);
			PORTB = 0x03;
			_delay_ms(period);
			PORTB = 0x06;
			_delay_ms(period);
			PORTB = 0x0c;
			_delay_ms(period);	
		}
		// setting the period to a value of 20
		else if((OCR0A>40)&&(OCR0A<=80))
		{
			period=20;
			PORTB = 0x09;
			_delay_ms(period);
			PORTB = 0x03;
			_delay_ms(period);
			PORTB = 0x06;
			_delay_ms(period);
			PORTB = 0x0c;
			_delay_ms(period);	
		}
		// setting the period to a value of 30
		else if((OCR0A>80)&&(OCR0A<=120))
		{
			period=30;
			PORTB = 0x09;
			_delay_ms(period);
			PORTB = 0x03;
			_delay_ms(period);
			PORTB = 0x06;
			_delay_ms(period);
			PORTB = 0x0c;
			_delay_ms(period);	
		}
		
	else if((OCR0A>120)&&(OCR0A<=150))
		{
			period=40;
			PORTB = 0x09;
			_delay_ms(period);
			PORTB = 0x03;
			_delay_ms(period);
			PORTB = 0x06;
			_delay_ms(period);
			PORTB = 0x0c;
			_delay_ms(period);
		  }
		// setiting the period to a value of 50, fast frequency  
	else if((OCR0A>150)&&(OCR0A<=225))
		{
			period=50;
			PORTB = 0x09;
			_delay_ms(period);
			PORTB = 0x03;
			_delay_ms(period);
			PORTB = 0x06;
			_delay_ms(period);
			PORTB = 0x0c;
			_delay_ms(period);
		  }
			
			else if(OCR0A>225)
			{
				PORTB=0;
			}
    }
}

void initial(void)
{
	//clear on compare for OCOA
	//CTC mode
	//pre-scaler = 256
	TCCR0A |= (1<<COM0A1)|(0<<COM0A0)|(0<<COM0B1)|(0<<COM0B0)|(1<<WGM01)|(0<<WGM00);
	TCCR0B |= (1<<CS02)|(0<<CS01)|(0<<CS00);
	
	
}

// function to initialize ADC set up
void adc_init(void)
{
	ADCSRA |= ((1<<ADEN)|(1<<ADSC)|(0<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
	ADMUX |= (1<<REFS0);
}
