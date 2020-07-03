#include <avr/io.h>
#include "wait.h"


int main()
{
	DDRB = 0xff;

    while (1)
    {
		PORTB = 0xAA;
		WaitMs(100);
		PORTB = 0x55;
		WaitMs(100);
    }
}