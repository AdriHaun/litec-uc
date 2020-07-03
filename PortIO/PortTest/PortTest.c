/***************************************************************************//**
Implementation of a port test program for ATMEL AVR-Controller

@note An den Ports PORTA, PORTB, PORTC und PORTL werden Bitmuster ausgegeben.
Durch Verbindung der einzelnen Ports nacheinander mit
der Wannenstiftleiste SV8 (Px) am Print koennen die Bitmuster
entsprechend der Jumperstellung (JP1) visualisiert werden:
JP1 rechts:  7-Segmentanzeige
JP1 links:   LED-Balken

@author LiTec/PAMG
@date 12.05.2012
@version 1.0

@param compiler switches: none
@param linker switches: none

@b History:
- 1.0 LiTec/PAMG 12.05.2012 initial version.
*******************************************************************************/
/** @addtogroup PortTest_Application
@{*/
/** @file PortTest.c Main source file for the port test application. */

#include <avr/io.h>         // for ports
#include <stdint.h>
#include "Wait.h"


int16_t main (void) {
  uint8_t i;
  uint8_t x;

  // Port A
  DDRA  = 0xFF; // all pins are OUTPUTS
  PORTA = 0x00; // set initial value to 0

  // Port B
  DDRB  = 0xFF; // all pins are OUTPUTS
  PORTB = 0x00; // set initial value to 0

  // Port C
  DDRC  = 0xFF; // all pins are OUTPUTS
  PORTC = 0x00; // set initial value to 0

  // Port L
  DDRL  = 0xFF; // all pins are OUTPUTS
  PORTL = 0x00; // set initial value to 0

  // Port F  (ADC)
  DDRF  = 0xFF; // all pins are OUTPUTS
  PORTF = 0x00; // set initial value to 0

  // Port K  (ADC)
  DDRK  = 0xFF; // all pins are OUTPUTS
  PORTK = 0x00; // set initial value to 0

  // Configuration of the extended port (connector SV5)
  DDRJ = 0x03;  // PORTJ.0 and PORTJ.1 as Output
  DDRD = 0x0F;  // PORTD.0 - PORTD.3 as Output
  DDRE = 0x30;  // PORTE.4 and PORTE.4 as Output

  while (1) {
    for (i=0; i<2; i++) { // all  LEDs flash
      PORTA=PORTB=PORTC=PORTL=PORTF=PORTK=0xFF;
      PORTJ = 0x03;
      PORTD = 0x0F;
      PORTE = 0x30;
      WaitMs (500);
      PORTA=PORTB=PORTC=PORTL=PORTF=PORTK=PORTJ=PORTD=PORTE=0x00;
      WaitMs (500);
    } // for

    x = 0x01;
    PORTA=PORTB=PORTC=PORTL=PORTF=PORTK=~x;
    PORTJ = ~x & 0x03;
    PORTD = 0x0F;
    PORTE = 0x30;

    WaitMs (500);
    for (i=0; i<8; i++) { // turn LEDs on
      x=x<<1;
      PORTA=PORTB=PORTC=PORTL=PORTF=PORTK=~x;
      PORTJ = ~(x & 0x03) & 0x03;
      PORTD = (~(x & 0x0c) & 0x0C) | (~((x & 0xC0)>>6) & 0x03);
      PORTE = ~(x & 0x30) & 0x30;

      WaitMs (500);
    } // for
  } // while (1)
} // main
/**@}*/
