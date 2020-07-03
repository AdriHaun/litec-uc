#include <avr/io.h>
#include "i2c_bitbanging.h"
#include <util/delay.h>

//  ---------------------------------------------------------------------------
//	LOW-Level Functions
//	---------------------------------------------------------------------------

// SDA-Funktionen
void setSdaDominant()
{
	DDRD |= (0x01 << 1); // Bit Nr. 1 auf 1 setzen --> Ausgang
}

void setSdaRecessive()
{
	DDRD &= ~(0x01 << 1); // Bit Nr. 1 auf 0 setzen --> Eingang
}

uint8_t readSdaLevel()
{
	DDRD &= ~(0x01 << 1); // Zum Eingang machen

	// Bit 1 Testen: 1 -> High, 0 -> Low	
	return (PIND & (0x01 << 1)) ? 1 : 0;
}

// SCL-Funktionen
void setSclDominant()
{
	DDRD |= (0x01 << 0); // Bit Nr. 0 auf 1 setzen --> Ausgang
}

void setSclRecessive()
{
	DDRD &= ~(0x01 << 0); // Bit Nr. 0 aud 0 setzen --> Eingang
}

//	---------------------------------------------------------------------------
//	MID-Level Functions
//	---------------------------------------------------------------------------

void sendStartCondition()
{
	// Assumption: Before calling this function, I2C-Bus is idle
	// (SDA and SCL are recessive).
	_delay_us(1000);
	setSdaDominant();
	_delay_us(1000);
	setSclDominant();
	_delay_us(1000);
}


void sendStopCondition()
{
	setSdaDominant();
	_delay_us(1000);
	setSclRecessive();
	_delay_us(1000);
	setSdaRecessive();
	_delay_us(1000);
}

void sendHighBit()
{
	setSdaRecessive();
	_delay_us(10);
	setSclRecessive();
	_delay_us(20);
	setSclDominant();
	_delay_us(10);
}

void sendLowBit()
{
	setSdaDominant();
	_delay_us(10);
	setSclRecessive();
	_delay_us(20);
	setSclDominant();
	_delay_us(10);
}

uint8_t readBit()
{
	uint8_t bit;
	setSdaRecessive();
	_delay_us(10);
	setSclRecessive();
	_delay_us(10);
	bit = readSdaLevel();
	_delay_us(10);
	setSclDominant();
	_delay_us(10);
	return bit;
}

//	---------------------------------------------------------------------------
//	HIGH-Level Functions
//	---------------------------------------------------------------------------

// Acknowledge
// 1 falls ACK vom Slave
// 0 falls kein ACK vom Slave
uint8_t sendByte(uint8_t send)
{
	for (int i = 7; i >= 0; i--)
	{
		if ((send >> i) & 0x01)
			sendHighBit();
		else
			sendLowBit();
	}
	return readBit();
}

uint8_t readByte(uint8_t confirmWithACK)
{
	uint8_t received = 0x00;

	for (int i = 7; i >= 0; i--) {
		received |= readBit() << i;
	}

	if (confirmWithACK) sendLowBit();
	else sendHighBit();

	return received;
}

//	---------------------------------------------------------------------------
//	API-Level Functions
//	---------------------------------------------------------------------------

void initI2C()
{
	DDRD &= ~(0x01 << 0);
	PORTD &= ~(0x01 << 0);

	DDRD &= ~(0x01 << 1);
	PORTD &= ~(0x01 << 1);
}

uint8_t i2cSendBuffer(uint8_t slaveAddress, uint8_t* buffer, uint8_t bytesToSend)
{
	uint8_t successful = 1;

	sendStartCondition();

	sendByte(slaveAddress << 1);
	if (readBit()) successful = 0;

	for (uint8_t i = 0; i < bytesToSend; i++)
	{
		sendByte(buffer[i]);
		if (readBit()) successful = 0;
	}

	sendStopCondition();
	return successful;
}

uint8_t i2cReadBuffer(uint8_t slaveAddress, uint8_t* buffer, uint8_t bytesToRead)
{
	uint8_t successful = 1;
	sendStartCondition();

	sendByte(slaveAddress << 1);
	if (readBit()) successful = 0;

	for (uint8_t i = 0; i < bytesToRead; i++)
	{
		buffer[i] = readByte(1);
		if (readBit()) successful = 0;
	}

	sendStopCondition();
	return successful;
}