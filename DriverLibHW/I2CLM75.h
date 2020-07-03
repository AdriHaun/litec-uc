/***************************************************************************//**
Interface file the I2C driver for temperature sensor LM75
*******************************************************************************/
/** @addtogroup I2CLM75_api
@{*/
/** @file I2CLM75.h Interface file for the I2C-LM75 driver. */

#ifndef  I2CLM75_H
#define  I2CLM75_H

#include "I2CMaster.h"

#define I2C_LM75_MAX_MSG_LEN         4  // max. message length on bus

// LM75 Pointers
#define I2C_LM75_POINTER_TO_TEMP     0x00
#define I2C_LM75_POINTER_TO_CFG      0x01
#define I2C_LM75_POINTER_TO_HYST     0x02
#define I2C_LM75_POINTER_TO_OS       0x03

// LM75 Interrupt-Mode or Comparator-Mode
#define I2C_LM75_INT_MODE            0x02
#define I2C_LM75_COMP_MODE           0x00

void   I2CLM75Init    ( uint8_t addr, uint8_t int_enabled );
void   I2CLM75SetHyst ( uint8_t addr, int16_t hyst );
void   I2CLM75SetOs   ( uint8_t addr, int16_t overtemp );
int16_t I2CLM75GetTemp ( uint8_t addr );
#endif // I2CLM75_H
/**@}*/
