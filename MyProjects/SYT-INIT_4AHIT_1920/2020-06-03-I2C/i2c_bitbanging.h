#ifndef _I2C_BITBANGING
#define _I2C_BITBANGING

#include <stdint.h>

// API-Level
void initI2C();
uint8_t i2cSendBuffer(uint8_t slaveAddress, uint8_t* buffer, uint8_t bytesToSend);
uint8_t i2cReadBuffer(uint8_t slaveAddress, uint8_t* buffer, uint8_t bytesToRead);

// Low-Level
void setSdaDominant();
void setSdaRecessive();
uint8_t readSdaLevel();

void setSclDominant();
void setSclRecessive();

// Mid-Level
void sendStartCondition();
void sendStopCondition();
void sendHighBit();
void sendLowBit();
uint8_t readBit();

// Byte-Level
uint8_t sendByte(uint8_t send);
uint8_t readByte(uint8_t confirmWithACK);

#endif
