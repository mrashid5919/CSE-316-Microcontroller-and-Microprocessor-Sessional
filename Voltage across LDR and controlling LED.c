/*
 * GccApplication3.c
 *
 * Created: 16-Jan-23 2:41:25 PM
 * Author : Mayesha
 */

#ifndef F_CPU
#define F_CPU 1000000UL // 1 MHz clock speed
#endif


#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "lcd.h"


int main(void)
{
	DDRB = 0b00000001;
	PORTB = 0b00000000;
	DDRD = 0xFF;
	DDRC = 0xFF;

	ADMUX = 0b01000000;		// AREF				: 01
	// right-Justified	: 0
	// ADC0 for ADC		: 00000

	ADCSRA = 0b10000010;	// Enable ADC : 1
	// Do not start ADC : 0
	// No Trigger : 0
	// No Interrupt Flag : 0
	// No Interrupt : 0
	// ADC Clock : 010 -> 1MHz/4 = 250kHz

	Lcd4_Init();			// Initialize LCD in 4 bit mode

	unsigned int value = 0;
	while(1)
	{
		ADCSRA |= (1 << ADSC);			// Start ADC Conversion
		while(ADCSRA & (1 << ADSC)){;}	// Wait to finish ADC Conversion

		//ADC;
		int adcl = ADCL;
		int adch = ADCH;

		value = (adcl)|(adch<<8);	// XXXXXXDD | DDDDDDDD

		// Lcd4_Clear();

		Lcd4_Set_Cursor(1,1);	// Cursor in (row, column) = (1, 1)


		float voltage = (value * 5) / 1024.0;

		if(voltage>4.5){
			PORTB=0b00000001;
		}
		else{
			PORTB=0b00000000;
		}

		Lcd4_Set_Cursor(1,1);

		char result[8];
		dtostrf(voltage, 3, 2, result);	// double-to-string-format width = 3, precision = 2

		Lcd4_Write_String(result);

		//_delay_ms(1000);
	}
	return 0;
}



