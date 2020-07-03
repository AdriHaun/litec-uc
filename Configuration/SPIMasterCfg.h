/***************************************************************************//**
Driver for SPI-Master-Routines

@note Copy the file SPICfg.h to your local project folder and edit
      the configuration
*******************************************************************************/
/** @addtogroup SPI_api
@{*/
/** @file SPICfg.h Configuration file for SPI master module. */

#ifndef _SPICFG_H
#define _SPICFG_H

#include <avr/io.h>
#include <stdint.h>

#if defined (__AVR_ATmega2560__)
  #define SPI_PORT PORTB
  #define SPI_SS 0x01                       // PB0
  #define SPI_SCK 0x02                      // PB1
#elif defined (__AVR_ATmega32__) || defined (__AVR_ATmega16__)
  #define SPI_PORT PORTB
  #define SPI_SS 0x10                       // PB4
  #define SPI_SCK 0x80                      // PB7
#elif defined (__AVR_ATmega8__)
  #define SPI_PORT PORTB
  #define SPI_SS 0x04                       // PB2
  #define SPI_SCK 0x20                      // PB5
#else
  #error "device type not defined"
#endif

#define SPI_SS_ENABLE   SPI_PORT &= ~SPI_SS
#define SPI_SS_DISABLE  SPI_PORT |=  SPI_SS

#define SPI_SCK_OFF     SPI_PORT &= ~SPI_SCK
#define SPI_SCK_ON      SPI_PORT |=  SPI_SCK

#endif /* _SPICFG_H  */
/**@}*/
