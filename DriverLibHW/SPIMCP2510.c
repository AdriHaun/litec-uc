/***************************************************************************//**
Implementation file for the MCP2510 and MCP2515 CAN-Controller driver

@author LiTec/PAMG
@date 24.06.2007
@version 1.0

@param compiler switches: none
@param linker switches: none

@b History:
- 1.0 LiTec/PAMG 24.06.2007 initial version.
*******************************************************************************/
/** @addtogroup SPIMCP2510_api
@{*/
/** @file SPIMCP2510.c Main source file for the MCP251x - CAN - Controller. */
#include "SPIMCP2510.h"
#include "SPIMCP2510Cfg.h"

/***************************************************************************//**
Function for reseting the CAN-Controller
@param - none
@retval - none
*******************************************************************************/
void SPIMCP2510Reset ( void ) {
  SPIMCP2510_SS_ENABLE;
  SPIMasterWriteChar ( SPIMCP251X_RESET );
  SPIMCP2510_SS_DISABLE;
}

/***************************************************************************//**
Function for synchronization with CAN-Controller
@param - none
@retval - none
*******************************************************************************/
void SPIMCP2510Sync (void) {
  int i;

  SPIMCP2510_SS_ENABLE;
  SPIMasterWriteChar ( 0xFF );             // addess first
  SPIMasterWriteChar ( SPIMCP251X_READ | 0x0F );

  for ( i=0; i<14; i++) {              // 15x 0xFF
     SPIMasterWriteChar ( 0xFF );
  }
  SPIMCP2510_SS_DISABLE;
}

/***************************************************************************//**
Function to read one byte from a can controller register
@param addr Address of the register to be read
@retval byte read from can controller register
*******************************************************************************/
uint8_t SPIMCP2510RegRead ( uint8_t addr ) {
  uint8_t data;

  SPIMCP2510_SS_ENABLE;
  SPIMasterWriteChar ( SPIMCP251X_READ );
  SPIMasterWriteChar ( addr );
  SPIMasterReadChar ( &data );
  SPIMCP2510_SS_DISABLE;
  return data;
}

/***************************************************************************//**
Function to write one byte to a can controller register selected by addr
@param addr Address of the register to be written
@param data Data to be written to selected register
@retval - none
*******************************************************************************/
void SPIMCP2510RegWrite ( uint8_t addr, uint8_t data ) {
  SPIMCP2510_SS_ENABLE;
  SPIMasterWriteChar ( SPIMCP251X_WRITE );
  SPIMasterWriteChar ( addr );
  SPIMasterWriteChar ( data );
  SPIMCP2510_SS_DISABLE;
}

/***************************************************************************//**
Function to modigy one bit of a register in the can controller selected by addr
@param addr Address of the register to be modified
@param mask Mask to select bits (see datasheet)
@param data Data to modify register (see datasheet)
@retval - none
*******************************************************************************/
void SPIMCP2510RegBitModify (uint8_t addr, uint8_t mask, uint8_t data) {
  SPIMCP2510_SS_ENABLE;
  SPIMasterWriteChar ( SPIMCP251X_BIT_MODIFY );
  SPIMasterWriteChar ( addr );
  SPIMasterWriteChar ( mask ); // mask-Bit = 1 --> corresponds to that the register bit is manipulated
  SPIMasterWriteChar ( data );
  SPIMCP2510_SS_DISABLE;
}

/***************************************************************************//**
Function to signal READY TO SEND (RTS) for one of the tx-buffers
@param tx_buf_nr (0..2) number of rx-buffer used for sending data on CAN-bus
@retval - none
*******************************************************************************/
void SPIMCP2510RTS ( uint8_t tx_buf_nr ) {
  if ( tx_buf_nr > 2 ) return;
  SPIMCP2510_SS_ENABLE;
  SPIMasterWriteChar (SPIMCP251X_RTS | (0x01 << tx_buf_nr) );  // send message to bus
  SPIMCP2510_SS_DISABLE;
}
/**@}*/
