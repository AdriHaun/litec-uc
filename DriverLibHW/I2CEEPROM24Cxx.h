/***************************************************************************//**
Interface file for I2C-EEPROM driver (24Cxx).
*******************************************************************************/
/** @addtogroup I2CEEPROM24Cxx_api
@{*/
/** @file I2CEEPROM24Cxx.h Interface file for I2C-EEPROM-24Cxx. */
#ifndef  I2CEEPROM24Cxx_H
#define  I2CEEPROM24Cxx_H

#include "I2CMaster.h"

// EEPROM Addresses
#define I2C_24Cxx_DATA_LEN  0x1000  // data length of 24C32 (4096 Bytes, 32kBit)
//#define I2C_24Cxx_DATA_LEN  0x2000  // data length of 24C64 (8192 Bytes, 64kBit)

// write byte
void I2CEEPROM24CxxWriteByte ( uint8_t addr, uint16_t start, uint8_t* data);

// write data (page write optimized)
void I2CEEPROM24CxxWriteData ( uint8_t addr, uint16_t start, uint8_t* data, uint16_t len);

// read data
void I2CEEPROM24CxxReadData ( uint8_t addr, uint16_t start, uint8_t* data, uint16_t len);

#endif // I2CEEPROM24Cxx_H
/** @} */
