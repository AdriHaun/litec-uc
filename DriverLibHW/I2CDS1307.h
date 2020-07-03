/***************************************************************************//**
Interface file for I2C-RTC DS1307 driver.
*******************************************************************************/
/** @addtogroup I2CDS1307_api
@{*/
/** @file I2CDS1307.h Interface file for I2C-RTC DS1307. */
#ifndef  I2CDS1307_H
#define  I2CDS1307_H

#include "I2CMaster.h"
#include "TimeDate.h"

// RAM Addresses
#define I2C_DS1307_RAM_BEGIN         0x08  // 1. Addresse in RAM
#define I2C_DS1307_RAM_END           0x3F  // last Addresse im RAM
#define I2C_DS1307_RAM_LEN    ( I2C_DS1307_RAM_END - I2C_DS1307_RAM_BEGIN + 1 )

// Set time and date
void I2CDS1307SetTimeDate ( uint8_t addr, TimeDateStruct time_date,
                                uint8_t control);
// Set date
void I2CDS1307SetDate ( uint8_t addr, uint8_t day, uint8_t date, uint8_t month,
                        uint16_t year, uint8_t control);

// Get time and date
uint8_t I2CDS1307GetTimeDate ( uint8_t addr, TimeDateStruct* time_date );


// Init RAM (len = 0 --> whole RAM will be cleared)
void I2CDS1307InitRAM ( uint8_t addr, uint8_t* init_data, uint8_t len);

// write RAM
void I2CDS1307WriteRAM ( uint8_t addr, uint8_t start, uint8_t* data, uint8_t len);

// read RAM
void I2CDS1307ReadRAM ( uint8_t addr, uint8_t start, uint8_t* data, uint8_t len);

#endif // I2CDS1307_H
/** @} */
