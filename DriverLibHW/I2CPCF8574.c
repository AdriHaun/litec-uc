/***************************************************************************//**
Implementation file for the I2C port expander PCF8574 driver

@author LiTec/PAMG
@date 27.08.2008
@version 1.0

@param compiler switches: none
@param linker switches: none

@b History:
- 1.0 LiTec/PAMG 27.08.2008 initial version.
*******************************************************************************/
/** @addtogroup I2CPCF8574_api
@{*/
/** @file I2CPCF8574.c Main source file for the I2C-PCF8574 driver. */
#include "I2CPCF8574.h"

/***************************************************************************//**
Function for writing data to slaves port
@param addr Address of I2C slave (0 - 7 ... see jumper on hardware)
@param byte Byte to be written to the slaves port
@retval 0 .. success
@retval 1 .. invalid addr
@retval 2 .. no answer from slave
@retval 3 .. data write error (no ACK from slave)
*******************************************************************************/
uint8_t I2CPCF8574WritePort (uint8_t addr, uint8_t byte) {
  if ( addr > 7 ) return 1;
  if (I2CMasterStart (( PCF8574_ID | ((addr & 0x07) << 1) ))) return 2;
  if (I2CMasterWrite ( byte ) ) return 3;
  I2CMasterStop ();
  return 0;
}

/***************************************************************************//**
Function for reading from slaves port
@param addr Address of I2C slave (0 - 7 ... see jumper on hardware)
@param *byte Pointer to data read from the slaves port
@retval 0 .. success
@retval 1 .. invalid addr
@retval 2 .. no answer from slave
*******************************************************************************/
uint8_t I2CPCF8574ReadPort (uint8_t addr, uint8_t* byte) {
  if ( addr > 7 ) return 1;
  if (I2CMasterStart ( PCF8574_ID | ((addr & 0x07) << 1) | 0x01)) return 2;
  *byte = I2CMasterReadNak ( );         // send nak and stop to slave
  return 0;
}
/**@}*/
