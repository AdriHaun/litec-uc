/***************************************************************************//**
Driver for SPI-Master-Module
*******************************************************************************/
/** @addtogroup SPIMaster_api
@{*/
/** @file SPIMaster.h Interface file for SPI master module. */

#ifndef _SPIMaster_H
#define _SPIMaster_H

#include "SPIMasterCfg.h"

#ifdef __cplusplus
  extern "C"{
#endif


void SPIMasterInit ( uint8_t clk_division  );  /* initialization */
// void SPIMasterSync ( void );              /* synchronisation with slave */

void SPIMasterReadChar ( uint8_t* data ); /* data word from slave  */
void SPIMasterWriteChar ( uint8_t data );  /* data word to slave  */

uint8_t SPIMasterTransmitChar ( uint8_t data );   /* write and read one byte from slave */
void  SPIMasterTransmit ( uint8_t* data, uint8_t* received, uint8_t len );
                        /* write data to slave and read received data */

void SPIMasterRead ( uint8_t* data, uint8_t len );   /* data stream to slave */
void SPIMasterWrite ( uint8_t* data, uint8_t len );   /* data stream from slave */

#ifdef __cplusplus
} // extern "C"
#endif

#endif  //_SPIMaster_H
/**
@}
*/
