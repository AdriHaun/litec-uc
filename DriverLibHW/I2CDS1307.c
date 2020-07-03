/***************************************************************************//**
Implementation file for I2C-RTC DS1307 driver.

@author LiTec/PAMG
@date 04.04.2008
@version 1.0

@param compiler switches: none
@param linker switches: none

@see I2CDS1307.h

@b History:
- 1.0 LiTec/PAMG 04.04.2008 initial version.
*******************************************************************************/
/** @addtogroup I2CDS1307_api
@{*/
/** @file I2CDS1307.c Main source file for I2C-RTC DS1307. */
#include "I2CDS1307.h"

#define DS1307_BASE 0xD0

/***************************************************************************//**
Function for writing time and date to the RTC
@param addr Addresse of the DS1307 (0 ... 7) on the bus
@param time_date for details see I2CDS1307.h
@param control Value for control register to write (see datasheet)
@retval - none
*******************************************************************************/
void I2CDS1307SetTimeDate ( uint8_t addr, TimeDateStruct time_date,
                            uint8_t control) {
  if ( addr > 7 ) return;

  I2CMasterStart ((DS1307_BASE | (addr<<1) )); // R/#W = 0
  I2CMasterWrite ( 0 );                      // Pointer = 0
  I2CMasterWrite ( ((time_date.time.sec/10)<<4) | (time_date.time.sec%10) );
  I2CMasterWrite ( ((time_date.time.min/10)<<4) | (time_date.time.min%10) );
  I2CMasterWrite ( ((time_date.time.hour/10)<<4) | (time_date.time.hour%10) );
  I2CMasterWrite ( time_date.date.weekday );
  I2CMasterWrite ( ((time_date.date.day/10)<<4) | (time_date.date.day%10) );
  I2CMasterWrite ( ((time_date.date.month/10)<<4) | (time_date.date.month%10) );
  I2CMasterWrite ( (((time_date.date.year-2000)/10)<<4) | ((time_date.date.year-2000)%10) );
  I2CMasterWrite ( control ); // set control register
  I2CMasterStop ();

//  I2CMasterStart ( DS1307_BASE | (addr<<1) ); // R/#W = 0
//  I2CMasterWrite ( I2C_DS1307_RAM_BEGIN );   // Pointer = 0
//  DateCalcCalweek ( &time_date.date );
//  I2CMasterWrite ( time_date.date.calweek );   // write data
//  I2CMasterStop ();
}

/***************************************************************************//**
Function for writing date to the RTC
@param addr Addresse of the DS1307 (0 ... 7) on the bus
@param day Value for day to write
@param date Value for date to write
@param month Value for month to write
@param year Value for year to write (ex. 2012)
@param control Value for control register to write (see datasheet)
@retval - none
*******************************************************************************/
void I2CDS1307SetDate ( uint8_t addr, uint8_t day,
                        uint8_t date, uint8_t month,
                        uint16_t year, uint8_t control ) {
  if ( addr > 7 ) return;

  I2CMasterStart ((DS1307_BASE | (addr<<1) )); // R/#W = 0
  I2CMasterWrite ( 3 );                      // Pointer = 3
  I2CMasterWrite ( day );                                             // set day
  I2CMasterWrite ( (uint8_t) ( ((date /10)<<4) | (date %10)) ); // set date
  I2CMasterWrite ( (uint8_t) ( ((month/10)<<4) | (month%10)) ); // set month
  I2CMasterWrite ( (uint8_t) ( ((year-2000 /10)<<4) | ((year-2000) %10)) ); // set year
  I2CMasterWrite ( control ); // set control register
  I2CMasterStop ();
}

/***************************************************************************//**
Function for reading date and time from the RTC
@param addr Addresse of the DS1307 (0 ... 7) on the bus
@param time_date Destination-address for struct with time and date information
@retval - none
*******************************************************************************/
uint8_t I2CDS1307GetTimeDate ( uint8_t addr, TimeDateStruct* time_date ) {
  uint8_t temp = 0x00;

  if ( addr > 7 ) return 1;
  if (I2CMasterStart (DS1307_BASE | (addr<<1) ) ) { // R/#W = 0
    I2CMasterStop ();
    return 2;
  }

  if (I2CMasterWrite ( 0 )) {                 // set pointer to 0
    I2CMasterStop ();
    return 3;
  }
  I2CMasterStop ();

  if (I2CMasterStart (DS1307_BASE | (addr<<1) | 0x01) ) { // R/#W = 1
    I2CMasterStop ();
    return 2;
  }

  temp = I2CMasterReadAck();
  time_date->time.sec   = ((temp & 0xF0)>>4)*10 + (temp & 0x0F);
  temp = I2CMasterReadAck();
  time_date->time.min   = ((temp & 0xF0)>>4)*10 + (temp & 0x0F);
  temp = I2CMasterReadAck();
  time_date->time.hour  = ((temp & 0xF0)>>4)*10 + (temp & 0x0F);
  time_date->date.weekday   = I2CMasterReadAck();
  temp = I2CMasterReadAck();
  time_date->date.day  = ((temp & 0xF0)>>4)*10 + (temp & 0x0F);
  temp = I2CMasterReadAck();
  time_date->date.month = ((temp & 0xF0)>>4)*10 + (temp & 0x0F);
  temp = I2CMasterReadNak();
  time_date->date.year  = ((temp & 0xF0)>>4)*10 + (temp & 0x0F)+2000;
  I2CMasterStop ();

  DateCalcCalweek ( &(time_date->date) );

//  I2CMasterStart (DS1307_BASE | (addr<<1) ); // R/#W = 0
//  I2CMasterWrite ( I2C_DS1307_RAM_BEGIN );  // set internal pointer to RAM-begin
//  I2CMasterStop ();

//  I2CMasterStart (DS1307_BASE | (addr<<1) | 0x01 ); // R/#W = 1
//  time_date->date.calweek = I2CMasterReadNak ( );
//  I2CMasterStop ();
  return 0;
}

/***************************************************************************//**
Function for initialization of internal RAM
@param addr Addresse of the DS1307 (0 ... 7) on the bus
@param init_data Pointer to source of data to be initialized (blank to RAM-End)
@param len Length of init_data to be written
@retval - none
*******************************************************************************/
void I2CDS1307InitRAM ( uint8_t addr, uint8_t* init_data, uint8_t len) {
  uint8_t i;

  if ( (addr > 7) || (len == 0) ) return; // invalid parameter
  if ( len > I2C_DS1307_RAM_LEN ) len = I2C_DS1307_RAM_LEN;  // correct len

  I2CMasterStart (DS1307_BASE | (addr<<1) ); // R/#W = 0
  I2CMasterWrite ( I2C_DS1307_RAM_BEGIN ); // Pointer = 0

  for ( i=0; i< len; i++, init_data++ ) I2CMasterWrite ( *init_data ); // write data
  for ( i=i; i<I2C_DS1307_RAM_LEN; i++) I2CMasterWrite ( 0x00 ); // blank RAM
  I2CMasterStop ();
}

/***************************************************************************//**
Function for writing bytes to the internal RAM
@param addr Addresse of the DS1307 (0 ... 7) on the bus
@param start Start-address for RAM-read (0 - 55)
@param data Pointer to source
@param len Length of data to be written
@retval - none
*******************************************************************************/
void I2CDS1307WriteRAM ( uint8_t addr, uint8_t start, uint8_t* data, uint8_t len) {
  uint8_t i;
  uint8_t write_len;

  if ( (addr > 7) || (len == 0) ||
       (start >= I2C_DS1307_RAM_LEN ) ) return;  // invalid parameter

  if ( start + len  > I2C_DS1307_RAM_LEN )
    write_len = I2C_DS1307_RAM_LEN - start;
  else
    write_len = len;

  I2CMasterStart (DS1307_BASE | (addr<<1) ); // R/#W = 0
  I2CMasterWrite ( I2C_DS1307_RAM_BEGIN + start );                    // Pointer = 0

  for ( i = 0; i< write_len; i++, data++ ) I2CMasterWrite ( *data );   // write data
  I2CMasterStop ();
}

/***************************************************************************//**
Function for reading bytes from internal RAM
@param addr Addresse of the DS1307 (0 ... 7) on the bus
@param start Start-address for RAM-read (0 - 55)
@param data Pointer to destination
@param len Length of data to be read
@retval - none
*******************************************************************************/
void I2CDS1307ReadRAM ( uint8_t addr, uint8_t start, uint8_t* data, uint8_t len) {
  uint8_t i;
  uint8_t read_len;

  if ( (addr > 7) || (len == 0) ||
       (start >= I2C_DS1307_RAM_LEN ) ) return;  // invalid parameter

  if ( start + len  > I2C_DS1307_RAM_LEN )
    read_len = I2C_DS1307_RAM_LEN - start;
  else
    read_len = len;

  I2CMasterStart (DS1307_BASE | (addr<<1) ); // R/#W = 0
  I2CMasterWrite ( I2C_DS1307_RAM_BEGIN + start );  // set internal pointer
  I2CMasterStop ();

  I2CMasterStart (DS1307_BASE | (addr<<1) | 0x01 ); // R/#W = 1

  for ( i = 0; i< read_len-1; i++, data++ ) *data = I2CMasterReadAck ( );

  *data = I2CMasterReadNak ( );
  I2CMasterStop ();
}
/** @} */
