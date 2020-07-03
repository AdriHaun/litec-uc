#include <avr/io.h>
#include "SystemClock.h"
#include <avr/interrupt.h>
#include "USART.h"
volatile long startTime = -1;
volatile long endTime = -1;
volatile int starting = 1;
volatile int finished = 0;
int main()
{
	USARTInit(0, 9600, 1, 0, 1, 0);
	//  USARTInit(0, 115200, 1, 0, 1, 0);
	DDRH |= (0x01 << 6);
	DDRD &= ~(0x01 << 0);
	PORTD |= (0x01 << 0);
	initTimer0AsSystemClock(1);
	EICRA |= (0x01 << ISC00);
	EICRA &= ~(0x01 << ISC01);
	EIMSK |= (0x01 << 0);
	long distance;
	sei();
	while (1)
	{
		PORTH |= (0x01 << 6);
		delayMicroseconds(12);
		PORTH &= ~(0x01 << 6);
		if (finished) {
			finished = 0;
			distance = (endTime - startTime) / 59;
			printf("%lu cm\n", distance);
		}
		delayMilliseconds(1000);
	}

}
ISR(INT0_vect) {

	if (starting) {
		startTime = micros();
		starting = 0;
	}
	else {
		//end
		endTime = micros();
		starting = 1;
		finished = 1;
	}
}