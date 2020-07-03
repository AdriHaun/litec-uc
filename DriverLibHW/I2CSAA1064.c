/***************************************************************************//**
Implementation file the I2C driver for I2C 4-digit LED-Driver SAA1064

@author LiTec/PAMG
@date 27.08.2008
@version 1.0

@param compiler switches: none
@param linker switches: none

@b History:
- 1.0 LiTec/PAMG 27.08.2008 initial version.
*******************************************************************************/
/** @addtogroup I2CSAA1064_api
@{*/
/** @file I2CSAA1064.c Main source file for the I2C-SAA1064 driver. */
#include "I2CSAA1064.h"

/***************************************************************************//**
Function for writing a decimal value to the LED driver SAA1064
@param addr Address of I2C slave (0 - 7 ... see jumper on hardware)
@param word Word to be written to the slave
@param dpPosition Position of the decimal point (0 .. 3)
@retval 0 .. success
@retval 1 .. invalid addr
@retval 2 .. no answer from slave
@retval 3 .. data write error (no ACK from slave)
*******************************************************************************/
uint8_t I2CSAA1064WritePortDec (uint8_t addr, uint16_t word, uint8_t dpPosition) {
  uint16_t hex_word = 0x0000;

  hex_word = word / 1000 << 12;
  hex_word |= (word / 100 % 10) << 8;
  hex_word |= (word / 10 % 10)  << 4;
  hex_word |= (word % 10);
  return I2CSAA1064WritePortHex (addr, hex_word, dpPosition);
}

/***************************************************************************//**
Function for writing a hex value to the LED driver SAA1064
@param addr Address of I2C slave (0 - 7 ... see jumper on hardware)
@param word Word to be written to the slave
@param dpPosition Position of the decimal point (0 .. 3)
@retval 0 .. success
@retval 1 .. invalid addr
@retval 2 .. no answer from slave
@retval 3 .. data write error (no ACK from slave)
*******************************************************************************/
uint8_t I2CSAA1064WritePortHex (uint8_t addr, uint16_t word, uint8_t dpPosition) {
  int8_t i;
  uint8_t digit;

  if (addr > 3) return 1;

  if (I2CMasterStart (SAA1064_ID | ((addr & 0x07) << 1))) return 2;
  if (I2CMasterWrite (0x00 ))                             return 3;
  if (I2CMasterWrite (0x47))                              return 3;

  for (i = 3; i >= 0; i--) {
    digit = segm[(word & (0xF000 >> ((3 - i) * 4))) >> (i * 4)];
    if (dpPosition == i) {
      digit |= 0x80;
	}
    if (I2CMasterWrite (digit))                           return 3;
  }
  I2CMasterStop ();
  return 0;
}

/***************************************************************************//**
Function for reading state from slaves
@param addr Address of I2C slave (0 - 7 ... see jumper on hardware)
@param *state Pointer to state read from the status register of the SAA1064
@retval 0 .. success
@retval 1 .. invalid addr
@retval 2 .. no answer from slave
*******************************************************************************/
uint8_t I2CSAA1064ReadState (uint8_t addr, uint8_t* state) {
  if (addr > 7) return 1;               // invalid addr
  if (I2CMasterStart ( SAA1064_ID | ((addr & 0x07) << 1) | 0x01)) return 2;
  *state = I2CMasterReadAck ();
  I2CMasterStop ();
  return 0;                             // success
}
/**@}*/
