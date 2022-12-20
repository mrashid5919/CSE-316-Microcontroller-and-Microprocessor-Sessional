/*
 * GccApplication1.c
 *
 * Created: 12-Dec-22 3:02:17 PM
 * Author : Mayesha
 */ 
#define F_CPU 1000000
#include<util/delay.h>
#include <avr/io.h>


int main(void)
{
	DDRA=0b00110000; //1 if output, otherwise 0
	PORTA=0b00000000; //initially set 0 
    /* Replace with your application code */
    while (1) 
    {
		//_delay_ms(1000);
		PORTA=0b00010000;
		_delay_ms(1000);
		PORTA=0b00100000;
		_delay_ms(1000);
    }
}

