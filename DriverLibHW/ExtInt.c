/***************************************************************************//**
Implementation file for the external interrupt routines.

@author LiTec/PAMG
@date 10.05.2012
@version 1.0

@param compiler switches: none
@param linker switches: none

@b History:
- 1.0 LiTec/PAMG 10.05.2012 initial version.
*******************************************************************************/
/** @addtogroup ExtInt_api
@{*/
/** @file ExtInt.c Main source file for the external interrupt routines. */
#include <avr/interrupt.h>
#include "ExtInt.h"

/***************************************************************************//**
Function for initialization of an external interrupts
@param int_nr number of the external interrupt to init.
@param mode mode to set for the external interrupt (int_nr)
@retval - none
*******************************************************************************/
void ExtIntInit(uint8_t int_nr, uint8_t mode) {
#if defined (__AVR_ATmega2560__)
  if ( (int_nr > 7) || (mode > 3) ) return;  // invalid parameter

  if ( int_nr < 4 ) {
    EICRA &= ~(0x03 << (int_nr*2));     // clear Interrupt Sense Control Bits
    EICRA |= mode << (int_nr*2);        // set   Interrupt Sense Control Bits
  } else {
    EICRB &= ~(0x03 << ((int_nr-4)*2));     // clear Interrupt Sense Control Bits
    EICRB |= mode << ((int_nr-4)*2);        // set   Interrupt Sense Control Bits
  }
#endif
}

/***************************************************************************//**
Function to disable an external interrupt
@param int_nr number of the external interrupt to disable.
@retval - none
*******************************************************************************/
void ExtIntDisable( uint8_t int_nr ) {
#if defined (__AVR_ATmega2560__)
  if ( int_nr > 7 ) return; // ATMEGA2560 has 8 external interrupts
  EIMSK &= ~(1<<int_nr);
#endif
}

/***************************************************************************//**
Function to enable an external interrupt
@param int_nr number of the external interrupt to enable.
@retval - none
*******************************************************************************/
void ExtIntEnable( uint8_t int_nr ) {
#if defined (__AVR_ATmega2560__)
  if ( int_nr > 7 ) return; // ATMEGA2560 has 8 external interrupts
  EIMSK |= (1<<int_nr);
#endif
}
/**@}*/
