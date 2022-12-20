/*
 * GccApplication2.c
 *
 * Created: 19-Dec-22 3:11:17 PM
 * Author : Mayesha
 */ 
#define F_CPU 10000000UL
#include <avr/io.h>
#include <util/delay.h>
#include<avr/interrupt.h>
#include <stdio.h>

unsigned char col[]={	0b11100000,
						0b11010011,
						0b10110011,
						0b00110011,
						0b00110011,
						0b10110011,
						0b11010011,
						0b11100000};

int main(void)
{
    /* Replace with your application code */
	DDRA=0xFF;
	DDRD=0xFF;
    while (1) 
    {
		
		//for(int count=0;count<10;count++)
		//{
			for(int i=0;i<8;i++)
			{
				PORTA=(1<<i);
				PORTD=col[i];
				_delay_ms(0.1);
				/*for(int j=0;j<10;j++)
				{
					_delay_ms(5);
				}*/
			}
			
			delay 1s
		//}
		
		for(int i=0;i<8;i++)
		{
			if((col[i] & 0b10000000)==0b10000000)
			col[i]=(col[i]<<1)+0b00000001;
			else
			col[i]=(col[i]<<1);
		}
		
		
		
		
		
		/*for(int i=0;i<8;i++)
		{
			if((col[i] & 0b10000000)==0b10000000)
				col[i]=
		}*/
		//PORTA=0b11111111;
		//PORTD=0b00000000;
		/*for(int i=0;i<8;i++)
		{
			PORTA=(1<<i);
			PORTB=~col[i];
			_delay_ms(5);
		}*/
    }
}

