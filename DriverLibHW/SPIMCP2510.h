/***************************************************************************//**
Interface file for the MCP2510 and MCP2515 CAN-Controller driver
*******************************************************************************/
/** @addtogroup SPIMCP2510_api
@{*/
/** @file SPIMCP2510.h Interface file for the MCP251x - CAN - Controller. */

#ifndef  SPIMCP2510_H
#define  SPIMCP2510_H

#include "SPIMaster.h"
#include "SPIMCP2510Cfg.h"

#ifdef __cplusplus
  extern "C"{
#endif

// SPI commands
#define  SPIMCP251X_RESET       0xC0
#define  SPIMCP251X_READ        0x03
#define  SPIMCP251X_READ_RX     0x90           // only available on MCP2515
#define  SPIMCP251X_WRITE       0x02
#define  SPIMCP251X_WRITE_TX    0x40           // only available on MCP2515
#define  SPIMCP251X_RTS         0x80
#define  SPIMCP251X_READ_STATUS 0xA0
#define  SPIMCP251X_RX_STATUS   0xB0           // only available on MCP2515
#define  SPIMCP251X_BIT_MODIFY  0x05

void SPIMCP2510Reset ( void ); // reset of the CAN controller
void SPIMCP2510Sync ( void ); // synchronisation with the CAN controller

// read register of the CAN controller
uint8_t SPIMCP2510RegRead ( uint8_t addr );

// write register of the CAN controller
void SPIMCP2510RegWrite ( uint8_t addr, uint8_t data );

// bit manipulation in a register of the CAN controller
void SPIMCP2510RegBitModify ( uint8_t addr, uint8_t mask, uint8_t data );

// enable tx-buffer to send data (tx_buf_nr = 0 .. 2)
void SPIMCP2510RTS ( uint8_t tx_buf_nr );

#ifdef __cplusplus
} // extern "C"
#endif

#endif   // SPIMCP2515_H
/**@}*/
