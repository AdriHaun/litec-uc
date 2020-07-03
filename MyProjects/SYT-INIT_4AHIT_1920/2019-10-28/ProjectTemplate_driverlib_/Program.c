#include <avr/io.h>
#include "USART.h"
#include "SystemClock.h"


int main()
{
	USARTInit(0, 9600, 1, 0, 1, 0);
	printf("Program Starting");
	initTimer0AsSystemClock(0);

	int actualPattern = 0;
	int direction = +1; //changes between +1 an -1

    while (1)
    {
		PORTB = 0xFF;
		PORTB &= ~((0x01 << (3 - actualPattern)) || (0x01 << (4 + actualPattern)));
		actualPattern += direction;
		if (actualPattern == 3 || actualPattern == 0) direction *= -1;

		delayMicroseconds(200);
    }
}