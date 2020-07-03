/***************************************************************************//**
Interface file for the I2C port expander PCF8574 driver
*******************************************************************************/
/** @addtogroup I2CPCF8574_api
@{*/
/** @file I2CPCF8574.h Interface file for the I2C-PCF8574 driver. */
#ifndef I2CPCF8574
#define I2CPCF8574

#include "I2CMaster.h"
#include "I2CPCF8574Cfg.h"

uint8_t I2CPCF8574WritePort (uint8_t addr, uint8_t byte);
uint8_t I2CPCF8574ReadPort  (uint8_t addr, uint8_t* byte);
#endif // I2CPCF8574
/**@}*/
