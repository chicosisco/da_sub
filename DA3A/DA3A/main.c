/*
 * DA3A.c
 *
 * Created: 3/28/2019 2:24:27 AM
 * Author : Francisco Mata carlos
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL)))-1)

//Function declarations
volatile int Count;
void USART_init( unsigned int ubrr );
void USART_TX_string(char *data);
char outs[30];
int x_num;										//creates variable for random number
float due_date;									//creates variable for decimal point
char str[] = "July_4th_1776";		//creates string
char empty[] = " ";									//creates space

int main(void)
{
	Count = 0;
	TIMSK0 |= (1<<TOIE0);							//sets interrupt when overflow occurs
	sei ();								            //set global overflow
	TCCR0A = 0;										//normal mode
	TCCR0B |= (1<<CS02)|(1<<CS00);					//prescaler = 1024
	USART_init(BAUD_PRESCALLER);					//baud prescaler
	USART_TX_string("connection_successful\r\n"); 			//prints the word connection successful when connected and running
	while (1);
}
// USART (RS-232)
void USART_init( unsigned int ubrr ){
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << TXEN0);
	UCSR0C = (3 << UCSZ00);
}
//sending string to TEH RS-232
void USART_TX_string(char *data) {
	while (*data != '\0') {
		while (!(UCSR0A & (1<<UDRE0)));
		UDR0 = *data;
		data++;
	}
}
ISR (TIMER0_OVF_vect){								//timer0 overflow interrupt call
	while (Count < 61){
		if ((TIFR0 & 0x01) == 1){					//checks for overflow flag
			TIFR0 = 0X01;							//reset overflow
			Count++;
		}
	}
	if (Count > 60){
		USART_TX_string(str);				//prints string
		USART_TX_string(empty);				//prints space
		
		x_num = rand();						// random number
		due_date = 327.19;					//creates floating value; due date of assignment
		
		snprintf(outs, sizeof(outs), "%3d\r\n", x_num);
		USART_TX_string(outs);
		USART_TX_string(empty);
		
		sprintf(outs, "%f", due_date);
		USART_TX_string(outs);
		USART_TX_string(empty);
		Count = 0;
	}
}