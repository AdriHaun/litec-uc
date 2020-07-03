#include <avr/io.h>
#include <avr/interrupt.h>
#include "Wait.h"
int main()
{

	DDRD &= ~(0x01 << 0);
	DDRB |= 0x01 << 7;
	PORTD |= 0x01 << 0;
	EICRA |= (0x01 << ISC01);
	EICRA |= (0x01 << ISC00);
	EIMSK |= (0x01 << 0);
	sei();
	while (1)
	{
		PORTB &= ~(0x01 << 7);
		WaitMs(1000);
	}
}
ISR(INT0_vect) 
{
	PORTB |= (0x01 << 7);
}