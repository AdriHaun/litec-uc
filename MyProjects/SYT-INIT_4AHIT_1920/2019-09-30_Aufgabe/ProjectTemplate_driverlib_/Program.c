#include <avr/io.h>
#include "Wait.h"
#include "USART.h"
#include "SystemClock.h"

int main()
{
	// 2
	DDRF = 0xFF; //Macht alle 8 Pins zu ausgängen

	// 3
	DDRF = 0x00;

	// 5
	//DDRB = 0x01 << 3;
	//PORTB = 0x01 << 3;

	//6
	//DDRB = 0x70;
	//PORTB = 0x00;
	//USARTInit(0, 9600, 1, 0, 1, 0);

	//8
	DDRD = 0x00;
	PORTD = 0xFF;
	DDRB = 0xFF;

	int actualPattern = 0;

	uint8_t PortPatterns[6];
	PortPatterns[0] = ~0x10;
	PortPatterns[1] = ~0x20;
	PortPatterns[2] = ~0x20;
	PortPatterns[3] = ~0x40;
	PortPatterns[4] = ~0x70;
	PortPatterns[5] = ~0x00;

	initTimer0AsSystemClock(0);

	while (1)
	{
		/* Lösung 2A
		PORTF = 0x80;
		WaitMs(3000);
		PORTF = 0x7F;
		WaitMs(500);
		*/
		//Lösung 2B
		/*
		PORTF = 0x7F;
		WaitMs(3000);
		PORTF = 0x80;
		WaitMs(500);
		*/

		//Lösung 3a
		/*
		if ((PINF&0x01) == 0x01) {
			printf("Der Taster ist gedrückt\n");
		}
		else {
			printf("Der Taster ist nicht gedrückt\n");
		}
		WaitMs(1000);
		*/

		//Lösung 3b
		/*
		if ((~PINF & 0x01) == 0x01) {
			printf("Der Taster ist gedrückt\n");
		}
		else {
			printf("Der Taster ist nicht gedrückt\n");
		}
		WaitMs(1000);
		*/

		//Lösung 3c
		/*
		PORTF = 0x01;
		if ((~PINF & 0x01) == 0x01) {
			printf("Der Taster ist gedrückt\n");
		}
		else {
			printf("Der Taster ist nicht gedrückt\n");
		}
		WaitMs(1000);
		*/

		//Lösung 5
		/*
		if ((PINB & (0x01 << 3)) == 0) {
			PORTB |= (0x01<<4)|(0x01<<5)|(0x01<<6);
		}
		else {
			PORTB = 0x01 << 3;
		}
		WaitMs(100);
		*/

		//Lösung 6
		/*
		for (uint8_t i = 0; i <= 7; i++) {
			WaitMs(2000);
			PORTB = ((~i) << 4) & 0x70;
		}
		WaitMs(2000);
		*/
		
		//Lösung 8
		actualPattern++;
		if (actualPattern > 1) { actualPattern = 0; }
		PORTB = PortPatterns[actualPattern + getKeys() * 2];
		delayMicroseconds(200);
	}
}
void showLedPattern(uint8_t pattern) {
	PORTB = ((pattern) << 4) & 0x70;
}

int getKeys() {
	int ret = 0;
	if ((~PIND & (0x01 << 2)) && (~PIND & (0x01 << 3))) { 
		ret = 2; 
	}
	else if ((~PIND & (0x01 << 2)) || (~PIND & (0x01 << 3))) {
		ret = 1;
	}
	else {
		ret = 0;
	}
	return ret;
}