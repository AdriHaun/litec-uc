#include <avr/io.h>
#include <stdio.h>
#include "USART.h"
#include "SystemClock.h"
#include <avr/interrupt.h>

volatile uint8_t count = 0;

uint8_t pwm[4] = { 10, 80, 150, 220 };

uint8_t isStarted = 0;

int main()
{
	//initTimer0AsSystemClock(1);
	//USARTInit(0, 9600, 1, 0, 1, 0);
	
	/* 1
	TCCR5A &= ~0x03;
	TCCR5B |= 0x06;			// Fallende Flanke: Bits CS5[2..0] = 110
	TCCR5B &= ~(0x01 << 3);
	TCCR5B &= ~(0x01 << 4);	// normal Mode: Bits WGM5[3..0] = 0000

	DDRL &= ~(0x01 << 2);
	PORTL |= (0x01 << 2);
	*/

	/* 2
	TCCR1A = 0x00;  //??????00
	TCCR1B = 0x05;	//???00101
	*/

	/* 3
	DDRB |= (0x01 << 7);
	PORTB &= ~(0x01 << 7);

	TCCR1A = 0x00;
	TCCR1B = 0x0D;

	OCR1A = 16999;
	OCR1B = 1699;

	TIMSK1 = 0x06;
	*/
	
	/* 4
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
	*/

	/* 5 */

	DDRB |= ((0x01 << 0) | (0x01 << 1) | (0x01 << 2) | (0x01 << 3));

	TCCR1A &= ~(0x01 << WGM10);
	TCCR1A &= ~(0x01 << WGM11);
	TCCR1B |= (0x01 << WGM12);
	TCCR1A &= ~(0x01 << WGM11);

	TCCR1B |= (0x01 << CS11); // Prescaler = 8
	TCCR1B &= ~(0x01 << CS10);
	TCCR1B &= ~(0x01 << CS12);

	OCR1A = 80; // Prescaler 8 -> 80 = 40 µS

	TIMSK1 |= (0x01 << OCIE1A);

	sei();
	
    while (1)
    {
    	
		//printf("%d\n", TCNT5);
		//printf("%d\n", TCNT1);
		//printf("%d\n", count); -- 4
		/*if((PINF & (0x01<<0)) == 0)
		{
			isStarted = 1;
		} else if ((PINF & (0x01 << 1)) == 0)
		{
			isStarted = 0;
		} else if ((PINF & (0x01 << 2)) == 0)
		{
			count = 0;
		}


		printf("%02d:%02d.%1d\r", (count/600), ((count/10)%60), (count%10));
    	
		delayMilliseconds(1000);
		*/
    }
}

ISR(TIMER1_COMPA_vect)
{
	//PORTB |= (0x01 << 7);
	//if(isStarted == 1)
	//	count++;

	count++;
	
	if (count < pwm[0])
		PORTB |= (0x01 << 0);
	else PORTB &= ~(0x01 << 0);

	if (count < pwm[1])
		PORTB |= (0x01 << 1);
	else PORTB &= ~(0x01 << 1);

	if (count < pwm[2])
		PORTB |= (0x01 << 2);
	else PORTB &= ~(0x01 << 2);

	if (count < pwm[3])
		PORTB |= (0x01 << 3);
	else PORTB &= ~(0x01 << 3);
}

ISR(TIMER1_COMPB_vect)
{
	//PORTB &= ~(0x01 << 7);
}