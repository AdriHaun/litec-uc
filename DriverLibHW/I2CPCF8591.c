/***************************************************************************//**
Implementation file for the I2C-8Bit-D/A and A/D Converter PCF8591 driver

@author LiTec/PAMG
@date 27.08.2008
@version 1.0

@param compiler switches: none
@param linker switches: none

@b History:
- 1.0 LiTec/PAMG 27.08.2008 initial version.
*******************************************************************************/
/** @addtogroup I2CPCF8591_api
@{*/
/** @file I2CPCF8591.c Main source file for the I2C-PCF8591 driver. */
#include "I2CPCF8591.h"

static uint8_t ctrl_byte [7];

/***************************************************************************//**
Function to set the control register of the PCF8591
@param addr Address of I2C slave (0 - 7 ... see jumper on hardware)
@param ctrl Byte to be written to the control register
@retval 0 .. success
@retval 1 .. invalid addr
@retval 2 .. no answer from slave
@retval 3 .. data write error (no ACK from slave)
*******************************************************************************/
uint8_t I2CPCF8591SetCtrl (uint8_t addr, uint8_t ctrl) {
  if ( addr > 7 ) return 1;
  if (I2CMasterStart (( PCF8591_ID | ((addr & 0x07) << 1) )))       return 2;
  if (I2CMasterWrite ( ctrl ) ) return 3;
  ctrl_byte [addr] = ctrl & 0xF8;       // store a local copy
  I2CMasterStop ();
  return 0;
}

/***************************************************************************//**
Function for writing data to the DAC of the PCF8591
@param addr Address of I2C slave (0 - 7 ... see jumper on hardware)
@param byte Byte to be written to the DAC
@retval 0 .. success
@retval 1 .. invalid addr
@retval 2 .. no answer from slave
@retval 3 .. data write error (no ACK from slave)
*******************************************************************************/
uint8_t I2CPCF8591SetDAC (uint8_t addr, uint8_t byte) {
  if ( addr > 7 ) return 1;
  if (I2CMasterStart (( PCF8591_ID | ((addr & 0x07) << 1) ))) return 2;
  if (I2CMasterWrite ( 0x40 ) ) return 3;
  ctrl_byte [addr] = 0x40;
  if (I2CMasterWrite ( byte ) ) return 3;
  I2CMasterStop ();
  return 0;
}

/***************************************************************************//**
Function for reading data from ADC-channel of the PCF8591
@note See datasheet for details to the A/D conversion sequence
@param addr Address of I2C slave (0 - 7 ... see jumper on hardware)
@param channel ADC-Channel (0..3)
@param *byte Pointer to data read from the ADC-channel
@retval 0 .. success
@retval 1 .. invalid addr or channel
@retval 2 .. no answer from slave
@retval 3 .. data write error (no ACK from slave)
*******************************************************************************/
uint8_t I2CPCF8591GetADC (uint8_t addr, uint8_t channel, uint8_t* byte ) {
  if ( (addr > 7) || channel > 3 ) return 1;
  if (I2CMasterStart (( PCF8591_ID | ((addr & 0x07) << 1) ))) return 2;
  if (I2CMasterWrite ( ctrl_byte [addr] | channel ) ) return 3;
  I2CMasterStop ();

  if (I2CMasterStart ( PCF8591_ID | ((addr & 0x07) << 1) | 0x01)) return 2;
  *byte = I2CMasterReadAck ( );         // dummy read (see datasheet) send ack
  *byte = I2CMasterReadNak ( );         // send nak and stop to slave
  return 0;
}
/**@}*/
