/***************************************************************************//**
Implementation file for I2C-EEPROM driver.

@author LiTec/PAMG
@date 04.08.2014
@version 1.0

@param compiler switches: none
@param linker switches: none

@see I2CEEPROM24Cxx.h

@b History:
- 1.0 LiTec/PAMG 04.08.2014 initial version.
*******************************************************************************/
/** @addtogroup I2CEEPROM24Cxx_api
@{*/
/** @file I2CEEPROM24Cxx.c Main source file for I2C-EEPROM 24Cxx. */
#include "I2CEEPROM24Cxx.h"
#include "Wait.h"

#define I2C_EEPROM_24Cxx_BASE 0xA0

/***************************************************************************//**
Function for writing one byte to I2C-EEPROM (page write 32 Byte-pages not impl.)
@param addr Addresse of the 24Cxx (0 ... 7) on the bus
@param start Start-address for EEPROM-write (0 -> I2C_24Cxx_DATA_LEN - 1)
@param data Pointer to source
@param len Length of data to be written
@retval - none
*******************************************************************************/
void I2CEEPROM24CxxWriteByte ( uint8_t addr, uint16_t start, uint8_t* data) {
  if ( (addr > 7) || (start >= I2C_24Cxx_DATA_LEN) ) return;  // invalid parameter

  // ACKNOWLEDGE POLLING is not implemented!!!!!
  WaitMs (10); // wait until last write is finished (tWR see Datasheet)

  I2CMasterStart (I2C_EEPROM_24Cxx_BASE | (addr<<1) ); // R/#W = 0
  I2CMasterWrite ( (uint8_t)((start & 0x0F00)>>8) ); // H-Byte of start-addr
  I2CMasterWrite ( (uint8_t)(start & 0x00FF) );      // L-Byte of start-addr

  I2CMasterWrite ( *data );   // write data
  I2CMasterStop ();
}

/***************************************************************************//**
Function for writing data to I2C-EEPROM optimized for page write
@param addr Addresse of the 24Cxx (0 ... 7) on the bus
@param start Start-address for EEPROM-write (0 -> I2C_24Cxx_DATA_LEN - 1)
@param data Pointer to source
@param len Length of data to be written
@retval - none
*******************************************************************************/
void I2CEEPROM24CxxWriteData ( uint8_t addr, uint16_t start, uint8_t* data, uint16_t len) {
  uint8_t i;
  uint8_t write_len;

  if ( (addr > 7) || (start >= I2C_24Cxx_DATA_LEN) || (len == 0)) return;  // invalid parameter

  if ( start + len  > I2C_24Cxx_DATA_LEN - 1)
    write_len = I2C_24Cxx_DATA_LEN - start;
  else
    write_len = len;

  I2CMasterStart (I2C_EEPROM_24Cxx_BASE | (addr<<1) ); // R/#W = 0
  I2CMasterWrite ( (uint8_t)((start & 0x0F00)>>8) ); // H-Byte of start-addr
  I2CMasterWrite ( (uint8_t)(start & 0x00FF) );      // L-Byte of start-addr

  for ( i = 0; i< write_len; i++, data++ ) {
    WaitMs (10);
    I2CMasterWrite ( *data );   // write data
  }
  WaitMs (10);
  I2CMasterStop ();
}

/***************************************************************************//**
Function for reading bytes from I2C-EEPROM
@param addr Addresse of the 24Cxx (0 ... 7) on the bus
@param start Start-address for EEPROM-read (0 -> I2C_24Cxx_DATA_LEN - 1)
@param data Pointer to destination
@param len Length of data to be read
@retval - none
*******************************************************************************/
void I2CEEPROM24CxxReadData ( uint8_t addr, uint16_t start, uint8_t* data, uint16_t len) {
  uint8_t i;
  uint8_t read_len;

  if ( (addr > 7) || (len == 0) ) return;  // invalid parameter

  if ( start + len  > I2C_24Cxx_DATA_LEN - 1)
    read_len = I2C_24Cxx_DATA_LEN - start;
  else
    read_len = len;

  // dummy write
  I2CMasterStart (I2C_EEPROM_24Cxx_BASE | (addr<<1) ); // R/#W = 0
  I2CMasterWrite ( (uint8_t)((start & 0x0F00)>>8) ); // H-Byte of start-addr
  I2CMasterWrite ( (uint8_t)(start & 0x00FF) );      // L-Byte of start-addr
//  I2CMasterStop ();
  // read from local addr
  I2CMasterStart (I2C_EEPROM_24Cxx_BASE | (addr<<1) | 0x01 ); // R/#W = 1

  for ( i = 0; i< read_len-1; i++, data++ ) *data = I2CMasterReadAck ( );

  *data = I2CMasterReadNak ( );
  I2CMasterStop ();
}
/** @} */
