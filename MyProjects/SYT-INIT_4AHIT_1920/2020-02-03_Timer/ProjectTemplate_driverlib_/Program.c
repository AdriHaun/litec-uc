#include <avr/io.h>
#include <stdio.h>
#include "Wait.h"
#include "USART.h"
#include "SystemClock.h"

int main()
{
	initTimer0AsSystemClock(1);
	USARTInit(0, 9600, 1, 0, 1, 0);

	/* 1 */
	TCCR5A &= ~0x03;
	TCCR5B |= 0x06;			// Fallende Flanke: Bits CS5[2..0] = 110
	TCCR5B &= ~(0x01 << 3);
	TCCR5B &= ~(0x01 << 4);	// normal Mode: Bits WGM5[3..0] = 0000

	DDRL &= ~(0x01 << 2);
	PORTL |= (0x01 << 2);

	/*
	TCCR1A = 0b00;  //??????00
	TCCR1B = 0b101; //???00101
	*/

	while (1)
	{

		printf("%d\n", TCNT5);
		//printf("%d\n", TCNT1);
		delayMilliseconds(1000);

	}
}