/***************************************************************************//**
Implementation file the I2C driver for temperature sensor LM75

@author LiTec/PAMG
@date 24.06.2007
@version 1.0

@param compiler switches: none
@param linker switches: none

@b History:
- 1.0 LiTec/PAMG 10.10.2009 initial version.
*******************************************************************************/
/** @addtogroup I2CLM75_api
@{*/
/** @file I2CLM75.c Main source file for the I2C-LM75 driver. */
#include "I2CLM75.h"

#define LM75_ID 0x90

/***************************************************************************//**
Function for initialization of the I2C temperature sensor LM75
@param addr Address of I2C slave (0 - 7 ... see jumper on hardware)
@param int_enabled 0 .. comparator-mode, 1 .. interrupt-mode
@retval - none
*******************************************************************************/
void I2CLM75Init ( uint8_t addr, uint8_t int_enabled ) {
  if ( addr > 7 ) return;

  I2CMasterStart (LM75_ID | ((addr & 0x07) << 1) ); // R/#W = 0
  I2CMasterWrite ( (uint8_t) I2C_LM75_POINTER_TO_CFG);
  if ( int_enabled ) I2CMasterWrite ( (uint8_t) I2C_LM75_INT_MODE );
  else               I2CMasterWrite ( (uint8_t) I2C_LM75_COMP_MODE );
  I2CMasterStop ();
}

/***************************************************************************//**
Function set the internal hysterese
@param addr Address of I2C slave (0 - 7 ... see jumper on hardware)
@param hyst Hysterese in degree
@retval - none
*******************************************************************************/
void I2CLM75SetHyst ( uint8_t addr, int hyst ) {
  if ( addr > 7 ) return;
  I2CMasterStart (LM75_ID | ((addr & 0x07) << 1) ); // R/#W = 0
  I2CMasterWrite ( (uint8_t) I2C_LM75_POINTER_TO_HYST);  // select hysterese
  I2CMasterWrite ( (uint8_t) (((hyst*2) & 0x01FE) >> 1) );
  I2CMasterWrite ( (uint8_t) (((hyst*2) & 0x0001) << 7) );
  I2CMasterStop ();
}

/***************************************************************************//**
Function set the overtemperature shutdown
@param addr Address of I2C slave (0 - 7 ... see jumper on hardware)
@param overtemp Shut down temperature in degree
@retval - none
*******************************************************************************/
void I2CLM75SetOs ( uint8_t addr, int16_t overtemp ) {
  if ( addr > 7 ) return;
  I2CMasterStart (LM75_ID | ((addr & 0x07) << 1) ); // R/#W = 0
  I2CMasterWrite ( (uint8_t) I2C_LM75_POINTER_TO_OS);  // select os-register
  I2CMasterWrite ( (uint8_t) (((overtemp*2) & 0x01FE) >> 1) );
  I2CMasterWrite ( (uint8_t) (((overtemp*2) & 0x0001) << 7) );
  I2CMasterStop ();
}

/***************************************************************************//**
Function to read the actual temperature from LM75
@note Divide returnvalue by 2. The sensor has a resolution of 0.5deg.
@param addr Address of I2C slave (0 - 7 ... see jumper on hardware)
@retval actual temperature*2 (divide value by 2 to get temperature in degree!!)
*******************************************************************************/
int16_t I2CLM75GetTemp ( uint8_t addr ) {
  int16_t temp;
  if ( addr > 7 ) return 0;             // return 0deg

  if (I2CMasterStart (LM75_ID | ((addr & 0x07) << 1) )) { // R/#W = 0
    I2CMasterStop ();
    return 0;                           // return 0deg --> error
  }

  if (I2CMasterWrite ( (uint8_t) I2C_LM75_POINTER_TO_TEMP)) {  // select register
    I2CMasterStop ();
    return 0;                           // return 0deg --> error
  }

  if (I2CMasterStart ((LM75_ID | ((addr & 0x07) << 1) ) | 0x01) ) { // R/#W = 1
    I2CMasterStop ();
    return 0;                           // return 0deg --> error
  }

  temp = (((uint16_t)I2CMasterReadAck()   << 8) |
           (uint16_t)I2CMasterReadNak() ) >> 7;  // see datasheet

  I2CMasterStop ();

  if ( (temp & 0x0100) != 0 ) temp |= 0xFE00;  // sign extension
  return temp;
}
/**@}*/
