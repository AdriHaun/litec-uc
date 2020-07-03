/***************************************************************************//**
Interface file for the I2C-8Bit-D/A and A/D Converter PCF8591 driver
*******************************************************************************/
/** @addtogroup I2CPCF8591_api
@{*/
/** @file I2CPCF8591.h Interface file for the I2C-PCF8591 driver. */
#ifndef I2CPCF8591
#define I2CPCF8591

#include "I2CMaster.h"

#define PCF8591_ID  0x90

uint8_t I2CPCF8591SetCtrl (uint8_t addr, uint8_t ctrl);
uint8_t I2CPCF8591SetDAC  (uint8_t addr, uint8_t byte);
uint8_t I2CPCF8591GetADC  (uint8_t addr, uint8_t channel,  uint8_t* byte );
#endif // I2CPCF8591
/**@}*/
