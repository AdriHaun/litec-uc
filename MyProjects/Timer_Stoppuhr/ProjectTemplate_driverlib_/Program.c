#include<avr/io.h>
#include <stdio.h>
#include "USART.h"
#include "SystemClock.h"
#include <avr/interrupt.h>

volatile uint8_t count = 0;
uint8_t isStarted = 0;

int main()
{
	initTimer0AsSystemClock(1);
	USARTInit(0, 9600, 1, 0, 1, 0);

	DDRF &= ~(0x01 << 0 | 0x01 << 1 | 0x01 << 2);
	PORTF |= (0x01 << 0 | 0x01 << 1 | 0x01 << 2);

	TCCR1A &= ~(0x01 << WGM10);
	TCCR1A &= ~(0x01 << WGM11);

	TCCR1B |= (0x01 << WGM12);
	TCCR1B &= ~(0x01 << WGM13);
	TCCR1B |= ((0x01 << CS11) | (0x01 << CS10)); //prescaler = 64
	TCCR1B &= ~(0x01 << CS12);

	OCR1A = 24999;

	TIMSK1 |= (0x01 << OCIE1A);

	sei();


	while (1)
	{
		if ((PINF & (0x01 << 0)) == 0)
		{
			isStarted = 1;
		}
		else if ((PINF & (0x01 << 1)) == 0)
		{
			isStarted = 0;
		}
		else if ((PINF & (0x01 << 2)) == 0)
		{
			count = 0;
		}


		printf("%02d:%02d.%1d\r", (count / 600), ((count / 10) % 60), (count % 10));

		delayMilliseconds(1000);

	}
}

ISR(TIMER1_COMPA_vect)
{
	if (isStarted == 1)
		count++;
}

ISR(TIMER1_COMPB_vect)
{
}