/***************************************************************************//**
Interface file the I2C driver for I2C 4-digit LED-Driver SAA1064
*******************************************************************************/
/** @addtogroup I2CSAA1064_api
@{*/
/** @file I2CSAA1064.h Interface file for the I2C-SAA1064 driver. */
#ifndef I2CSAA1064
#define I2CSAA1064

#include "I2CMaster.h"
#include "LITECShieldDefinitions.h" // for S0, S1 and 7-Segment-Display

#define SAA1064_ID  0x70

uint8_t I2CSAA1064WritePortHex (uint8_t addr, uint16_t word, uint8_t dpPosition);
uint8_t I2CSAA1064WritePortDec (uint8_t addr, uint16_t word, uint8_t dpPosition);
uint8_t I2CSAA1064ReadState    (uint8_t addr, uint8_t* state);

#endif
/**@}*/
