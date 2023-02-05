/*
 * GccApplication4.c
 *
 * Created: 30-Jan-23 2:54:01 PM
 * Author : Mayesha
 */ 

#define F_CPU 1000000


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void uart_init()
{
	UCSRA = 0b00000010; //2x transmission
	UCSRB = 0b00011000; //tx,rx enabled
	UCSRC = 0b10000110; //URSEL = 1, UCSZ = 8bit (character size)
	
	UBRRH = 0;
	UBRRL = 12;   //UBBR = {clock rate/(8 x baud rate)} -1 [baud rate set 9600 in arduino. 8 as speed 2x]
}


void uart_send(unsigned char data){
	while ((UCSRA & (1<<UDRE)) == 0x00);
	UDR = data;
}


unsigned char uart_receive(void){
	while ((UCSRA & (1<<RXC)) == 0x00);
	return UDR;
}


ISR (INT1_vect){
	uart_send('a');
	_delay_ms(50);
}


int main(void)
{
	uart_init();
	_delay_ms(1000);
	DDRD &= ~(1<<PD3); //setting PD2 as input
	
	GICR = 1<<INT1;
	MCUCR = MCUCR | (1 << ISC11);  //falling edge
	MCUCR = MCUCR & (~(1 << ISC10)); //ISC01 = 1, ISC00 = 0
	sei();
	while(1);
}


