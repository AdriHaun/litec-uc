/***************************************************************************//**
Interface file for a MCP251x CAN-Controller.
*******************************************************************************/
/** @addtogroup CANMCP2510_api
@{*/
/** @file CANMCP2510.h Interface file for a MCP251x CAN-Controller. */
#ifndef CANMCP2510_H
#define CANMCP2510_H

#include <avr/io.h>
#include "CANMCP2510CFG.h"
#include "SPIMCP2510.h"               // SPI-Interface

#ifdef __cplusplus
extern "C"{
#endif

#define CANTYPE 2510

// Defines for valid baud rates
#define CAN_BAUD_10k   0
#define CAN_BAUD_20k   1
#define CAN_BAUD_50k   2
#define CAN_BAUD_100k  3
#define CAN_BAUD_125k  4
#define CAN_BAUD_250k  5
#define CAN_BAUD_500k  6
#define CAN_BAUD_1M    7

 void CANMCP2510SetOutput ( uint8_t addr, uint8_t value );

uint8_t CANMCP2510GetInput ( uint8_t addr );

 void CANMCP2510Init ( uint32_t baudrate, uint8_t txint,
                       uint8_t rxint, uint8_t errorint );

 void CANMCP2510ConfigRxMask ( uint8_t rx_buf_nr, uint16_t mask );
 void CANMCP2510MsgWr    ( uint16_t msg_id, uint8_t tx_buf_nr,  // 0-2 valid
                           uint8_t *src, uint8_t len);

 void CANMCP2510MsgRd    ( uint8_t rx_buf_nr,  // 0, 1 valid
                           uint8_t *dest, uint8_t *dlc);

 void CANMCP2510InterruptService ( uint8_t* can_state_reg,
                                   uint8_t* int_flag_reg,
                                   uint8_t* error_flag_reg,
                                   uint8_t* msg, uint8_t* msg_len);

#ifdef __cplusplus
} // extern "C"
#endif
								   
#endif // CANMCP2510_H
/**@}*/
