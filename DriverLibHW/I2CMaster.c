/***************************************************************************//**
Implementation file for the I2C master library using hardware TWI interface.

@author Peter Fleury <pfleury@gmx.ch>  http://jump.to/fleury  (modified by PAMG)
@date 2.7.2005
@version 1.3

@param compiler switches: none
@param linker switches: none

@note Target: any AVR device with hardware TWI

@b History:
- no history available.
*******************************************************************************/
/** @addtogroup I2CMaster_api
@{*/
/** @file I2CMaster.c Main source file for the I2C master library using hardware TWI interface. */

#include <util/twi.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "I2CMaster.h"

/***************************************************************************//**
Function to initialize the I2C bus interace. Need to be called only once
@param scl_clk clock
@retval - none
*******************************************************************************/
void I2CMasterInit ( uint32_t scl_clk ) {
  switch ( F_CPU ) {
    case 4000000L :
      if (scl_clk >= 10000) {
      /* initialize TWI clock: TWPS = 0 => prescaler = 1 */
          TWSR = 0;                            /* no prescaler*/
          TWBR = ((F_CPU/scl_clk)-16)/2;  /* must be > 10 for stable operation */
      } else if ( scl_clk >= 2000) {
          TWSR = 1;                            /* prescaler set to 4 */
          TWBR = ((F_CPU/scl_clk)-16)/2/4;  /* must be > 10 for stable operation */
      } else if ( scl_clk >= 500 ) {
          TWSR = 2;                            /* prescaler set to 16 */
          TWBR = ((F_CPU/scl_clk)-16)/2/16;  /* must be > 10 for stable operation */
      } else {
          TWSR = 3;                            /* prescaler set to 64 */
          TWBR = ((F_CPU/scl_clk)-16)/2/256;  /* must be > 10 for stable operation */
      }
      break;
   case 16000000L :
      if (scl_clk >= 40000) {
      /* initialize TWI clock: TWPS = 0 => prescaler = 1 */
          TWSR &= ~0x03;                     /* no prescaler*/
          TWBR = ((F_CPU/scl_clk)-16)/2;  /* must be > 10 for stable operation */
      } else if ( scl_clk >= 8000) {
          TWSR &= ~0x03; TWSR |= 0x01;            /* prescaler set to 4 */
          TWBR = ((F_CPU/scl_clk)-16)/2/4;  /* must be > 10 for stable operation */
      } else if ( scl_clk >= 2000 ) {
          TWSR &= ~0x03; TWSR |= 0x02;          /* prescaler set to 16 */
          TWBR = ((F_CPU/scl_clk)-16)/2/16;  /* must be > 10 for stable operation */
      } else if ( scl_clk >= 500 ){
          TWSR |= 0x03;                         /* prescaler set to 64 */
          TWBR = ((F_CPU/scl_clk)-16)/2/256;  /* must be > 10 for stable operation */
      } else {
          TWSR |= 0x03;                        /* prescaler set to 64 */
          TWBR = 255;                     /* min. possible baud rate (490 Bps)*/
      }
     break;
   default:                             // not implemented
     break;
  } // switch ( F_CPU )
}/* I2CMasterinit */

/***************************************************************************//**
Function to enable I2C-(TWI)-Interface
@retval - none
*******************************************************************************/
void I2CMasterEnable ( void ) {
   TWCR |= (1 << TWEN);                        // set TWEN
}

/***************************************************************************//**
Function to disable I2C-(TWI)-Interface
@retval - none
*******************************************************************************/
void I2CMasterDisable ( void ) {
   TWCR &= ~(1 << TWEN);                       // clear TWEN
}

/***************************************************************************//**
Function to issue a start condition and to send address and transfer direction
@param address address and transfer direction of I2C device
@retval 0 device accessible
@retval 1 failed to access device
*******************************************************************************/
uint8_t I2CMasterStart ( uint8_t address ) {
  uint8_t twst;
  uint8_t cnt = 0;

  // send START condition
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) ;

  // wait until transmission completed
  while ((!(TWCR & (1<<TWINT))) && (cnt < 10)) {_delay_us (100); cnt++;}

	// check value of TWI Status Register. Mask prescaler bits.
  twst = TW_STATUS & 0xF8;
  if ((twst != TW_START) && (twst != TW_REP_START)) return 1;

  // send device address
  TWDR = address;
  TWCR = (1<<TWINT) | (1<<TWEN);

  // wail until transmission completed and ACK/NACK has been received
  while ((!(TWCR & (1<<TWINT))) && (cnt < 10)) {_delay_us (100); cnt++;}

  // check value of TWI Status Register. Mask prescaler bits.
  twst = TW_STATUS & 0xF8;
  if ((twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK)) return 1;
  return 0;
}/* I2CMasterStart */

/***************************************************************************//**
Function to issue a start condition and to send address and transfer direction,
if device is busy, use ack polling to wait until device is ready.

@param address address and transfer direction of I2C device
@retval - none
*******************************************************************************/
void I2CMasterStartWait ( uint8_t address ) {
  uint8_t twst;
  uint8_t cnt = 0;

  while ( 1 ) {
    // send START condition
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

    // wait until transmission completed
    while ((!(TWCR & (1<<TWINT))) && (cnt < 10)) {_delay_us (100); cnt++;}

    // check value of TWI Status Register. Mask prescaler bits.
    twst = TW_STATUS & 0xF8;
    if ((twst != TW_START) && (twst != TW_REP_START)) continue;

    // send device address
    TWDR = address;
    TWCR = (1<<TWINT) | (1<<TWEN);

    // wail until transmission completed
    while ((!(TWCR & (1<<TWINT))) && (cnt < 10)) {_delay_us (100); cnt++;}

    // check value of TWI Status Register. Mask prescaler bits.
    twst = TW_STATUS & 0xF8;
    if ((twst == TW_MT_SLA_NACK) || (twst ==TW_MR_DATA_NACK)) {
      /* device busy, send stop condition to terminate write operation */
      TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);

      // wait until stop condition is executed and bus released
      while ((TWCR & (1<<TWSTO)) && (cnt < 10)) {_delay_us (100); cnt++;}

      continue;
    }
    //if( twst != TW_MT_SLA_ACK) return 1;
    break;
  }
}/* I2CMasterStartWait */

/***************************************************************************//**
Function to issue a repeated start condition (see I2CMasterStart)
@param address address and transfer direction of I2C device
@retval 0 device accessible
@retval 1 failed to access device
*******************************************************************************/
uint8_t I2CMasterRepStart ( uint8_t address ) {
  return I2CMasterStart (address);
}/* I2CMasterRepStart */

/***************************************************************************//**
Function to terminate a data transfer and to release the I2C bus
@retval - none
*******************************************************************************/
void I2CMasterStop ( void ) {
  uint8_t cnt = 0;
   /* send stop condition */
  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
  // wait until stop condition is executed and bus released
  while ((TWCR & (1<<TWSTO)) && (cnt < 10)) {_delay_us (100); cnt++;}
}/* I2CMasterStop */

/***************************************************************************//**
Function to send one byte to I2C device
@param data data byte to be transferred
@retval 0 write successful
@retval 1 write failed
*******************************************************************************/
uint8_t I2CMasterWrite ( uint8_t data ) {
  uint8_t cnt = 0;

  TWDR = data; // send data to the previously addressed device
  TWCR = (1<<TWINT) | (1<<TWEN);
  // wait until transmission completed
  while( (!(TWCR & (1<<TWINT))) && (cnt < 10)) {_delay_us (100); cnt++;}
  // check value of TWI Status Register. Mask prescaler bits
  if( (TW_STATUS & 0xF8) != TW_MT_DATA_ACK) return 1;
  return 0;
}/* I2CMasterWrite */

/***************************************************************************//**
Function to read one byte from the I2C device, to request more data from device
@retval byte read from I2C device
*******************************************************************************/
uint8_t I2CMasterReadAck ( void ) {
  uint8_t cnt = 0;

  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
  while ((!(TWCR & (1<<TWINT))) && (cnt < 10)) {_delay_us (100); cnt++;}
  return TWDR;
}/* I2CMasterReadAck */

/***************************************************************************//**
Function to read one byte from the I2C device, reading is followed by a stop condition
@retval byte read from I2C device
*******************************************************************************/
uint8_t I2CMasterReadNak ( void ) {
  uint8_t cnt = 0;

  TWCR = (1<<TWINT) | (1<<TWEN);
  while ((!(TWCR & (1<<TWINT))) && (cnt < 10)) {_delay_us (100); cnt++;}
  return TWDR;
}/* I2CMasterReadNak */

//======================= TWI Interrupt ==============================
inline ISR ( TWI_vect )  {} /* signal handler for TWI Int. */
/**@}*/
