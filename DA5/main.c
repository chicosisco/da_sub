/*
 * DA5.c
 *
 * Created: 4/26/2019 10:31:52 PM
 * Author : Francisco Mata
 */ 


//	Set clock frequency
#ifndef F_CPU
#define F_CPU 16000000UL
#endif


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//	Set up UART for printf();
#ifndef BAUD
#define BAUD 9600
#endif
#include "inc\STDIO_UART.c"  

//	Include nRF24L01+ library
#include "inc\nrf24l01.c" 
#include "inc\nrf24l01-mnemonics.h"
#include "inc\spi.c"    
void print_config(void);

//	Used in IRQ ISR
volatile bool message_received = false;
volatile bool status = false;

void ADC_init (void);
volatile unsigned char ADC_temp_val[5];
volatile uint8_t ADC_val_num;    



int main(void)
{
	

	ADC_init();
	
	
	
	//	Set cliche message to send (message cannot exceed 32 characters)
	char tx_message[32];				// Define string array
	strcpy(tx_message,"Hello World!");	// Copy string into array
	
	//	Initialize UART
	uart_init();
	
	//	Initialize nRF24L01+ and print configuration info
	nrf24_init();
	print_config();
	
	//	Start listening to incoming messages
	nrf24_start_listening();
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	strcpy(tx_message,"Hello World!");	// Copying string to array
	nrf24_send_message(tx_message);
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	
	while (1)
	{
		if (message_received)
		{
			//	Message received, print it
			message_received = false;
			printf("Received message: %s\n",nrf24_read_message());
			//	Send message as response
			_delay_ms(500);
			status = nrf24_send_message(ADC_temp_val);
			if (status == true) printf("Message sent successfully\n");
		}
	}
}

//	Interrupt on IRQ pin
ISR(INT0_vect)
{
	message_received = true;
}

void print_config(void)
{
	uint8_t data;
	printf("Startup successful\n\n nRF24L01+ configured as:\n");
	printf("-------------------------------------------\n");
	nrf24_read(CONFIG,&data,1);
	printf("CONFIG		0x%x\n",data);
	nrf24_read(EN_AA,&data,1);
	printf("EN_AA			0x%x\n",data);
	nrf24_read(EN_RXADDR,&data,1);
	printf("EN_RXADDR		0x%x\n",data);
	nrf24_read(SETUP_RETR,&data,1);
	printf("SETUP_RETR		0x%x\n",data);
	nrf24_read(RF_CH,&data,1);
	printf("RF_CH			0x%x\n",data);
	nrf24_read(RF_SETUP,&data,1);
	printf("RF_SETUP		0x%x\n",data);
	nrf24_read(STATUS,&data,1);
	printf("STATUS		0x%x\n",data);
	nrf24_read(FEATURE,&data,1);
	printf("FEATURE		0x%x\n",data);
	printf("-------------------------------------------\n\n");
}


//  Interrupt used to follow instructions below when conversion is done
ISR(ADC_vect)
{
	
	volatile unsigned int i=0;   // from characters to string
	char temp[4];
	
	ADC_val_num = (ADCH << 1);		 // Shifts the value left to one place
	
	itoa(ADC_val_num, temp, 10);	 // Converts integers to string
	// Takes ADCvalue, turns it into an ASCII representation
	// the ASCII representation will be stored under 'temp'
	// '10' represents the buffer
	
	while (i<4)					 // Transfers the temp string from itoa() to ADCtemp
	{
		ADC_temp_val[i] = temp[i];
		i++;
	}
}

void ADC_init (void)
{
	// AVcc with external capacitor at AREF pin
	// ADC left adjust
	ADMUX |= (1<<REFS0)|(1<<ADLAR);
	
	//ADC enable
	// ADC Start Conversion
	// ADC Auto Trigger Enable
	// ADC Interrupt Enable
	// 128 prescaler=128
	ADCSRA |=(1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADIE)|(1<<ADPS2)|(ADPS1)|(ADPS0); 
}
