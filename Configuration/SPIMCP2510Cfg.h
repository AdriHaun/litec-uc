/***************************************************************************//**
Driver for MCP251x - CAN - Controller.
*******************************************************************************/
/** @addtogroup SPIMCP2510_api
@{*/
/** @file SPIMCP2510Cfg.h Configuration file for MCP251x - CAN - Controller. */

#ifndef _SPIMCP2510Cfg_H
#define _SPIMCP2510Cfg_H

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "SPIMasterCfg.h"

#ifndef NOP
  #define NOP asm("nop")
#endif

#define SPIMCP2510_PORT SPI_PORT
#define SPIMCP2510_SS   SPI_SS
#define SPIMCP2510_SCK  SPI_SCK

#define SPIMCP2510_SS_ENABLE   SPIMCP2510_PORT &= ~SPIMCP2510_SS; _delay_us (100);
#define SPIMCP2510_SS_DISABLE  _delay_us (100); SPIMCP2510_PORT |=  SPIMCP2510_SS;

//#define SPIMCP2510_SCK_OFF     SPISCK_OFF_PORT &= ~SPI_SCK
//#define SPIMCP2510_SCK_ON      SPISCK_OFF_PORT |=  SPI_SCK

#endif /* _SPIMCP2510Cfg_H  */
/**@}*/
