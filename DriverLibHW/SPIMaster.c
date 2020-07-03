/***************************************************************************//**
Driver for SPI-Master-Module

@author LiTec/PAMG
@date 10.10.2009
@version 1.0

@param compiler switches: none
@param linker switches: none
@see SPIMasterCfg.h

@b History:
- 1.0 LiTec/PAMG 10.10.2009 initial version.
*******************************************************************************/
/** @addtogroup SPIMaster_api
@{ */
/** @file SPIMaster.c Main source file for SPI master module. */

#include "SPIMaster.h"

/***************************************************************************//**
Routine to initialize SPI-Bus
@brief initialization routine for parameterization of the SPI-interface
@param clk_division division factor fSPI = XTAL / clk_division
@retval - none
*******************************************************************************/
void SPIMasterInit ( uint8_t clk_division ) {  /* initialization */
  /* DDR MOSI, SCK and SS# as OUTPUT where ports get initialized! */
  /* Enable SPI, Master, set clock rate */
  SPCR = (1<<SPE)|(1<<MSTR);
  switch ( clk_division ) {
    case 8 :
    case 16 :
      SPCR |= 0x01;
      break;
    case 32 :
    case 64 :
      SPCR |= 0x02;
      break;
    case 128 :
      SPCR |= 0x03;
      break;
    default:           // 2, 4 or illegal value
      break;
   }

   switch ( clk_division ) {
      case   4 :
      case  16 :
      case  64 :
      case 128 :
        SPSR &= ~(1<<SPI2X);
        break;
      default:
        SPSR |= (1<<SPI2X);
        break;
   }
}

/***************************************************************************//**
Routine to transmit a character, the return value contains a received character
@param data data to send
@retval - received byte
*******************************************************************************/
uint8_t SPIMasterTransmitChar ( uint8_t data ) {
  SPDR = data;
  // Wait for transmission complete
  while ( !(SPSR & (1<<SPIF))) {;}
  return SPDR;
}

/***************************************************************************//**
Routine for reading a character from SPI-Bus (slave)
@brief read character from the SPI data register
@param *data Target address of the read data byte
@retval - none
*******************************************************************************/
void SPIMasterReadChar ( uint8_t* data ) {
  *data = SPIMasterTransmitChar ( 0x00 );     // send dummy-data and read one byte
}


/***************************************************************************//**
Routine for writing a character to SPI-Bus
@param data data to send (1 Byte)
@retval - none
*******************************************************************************/
void SPIMasterWriteChar ( uint8_t data ) {
  SPIMasterTransmitChar ( data );
}


/***************************************************************************//**
Routine for sending an array of char with length (len) to the SPI-Bus
@param *data reference to data that are sent
@param *received reference to destination where received datas ar stored
@param len number of bytes to send to and to receive from slave
@retval - none
*******************************************************************************/
void SPIMasterTransmit ( uint8_t* data, uint8_t* received, uint8_t len ) {
  int16_t i;

  if ( len < 1 ) return;

  for ( i=len-1; i>=0; i--) {
    *(received+i) = SPIMasterTransmitChar (*(data+i));  // MSB first!
  }
}
/**@}*/
