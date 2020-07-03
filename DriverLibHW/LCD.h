/***************************************************************************//**
Driver for LC-Displays with Hitachi HD44780 Controller.
The display is controlled by a 4 BIT hardware interface (see LCDCfg.h).
*******************************************************************************/
/** @addtogroup LCD_api
@{*/
/** @file LCD.h Interface file for LC-Displays with Hitachi HD44780 Controller. */

#ifndef _LCD_H
#define _LCD_H

//#ifdef __cplusplus
//extern "C" {
//#endif

#include <stdint.h>
#include "LCDCfg.h"


void LCDInit    ( void );        // initialization of the LCD
void LCDData    ( uint8_t dat );   // send data byte to LCD
void LCDCtrl    ( uint8_t ctrl );  // send controll byte to LCD
void LCDClear   ( void );        // clear LCD
void LCDClearLine (uint8_t line);  // clear a line on the display (1 - NUM_ROWS)

void LCDChar    ( uint8_t line, uint8_t row, char ascii );  // print character on LCD
void LCDString  ( uint8_t line, uint8_t row, char* str );   // print string on LCD
void LCDSetAddr ( uint8_t addr );  // set the pointer in the LCDs memory

void LCDWriteCgMem ( uint8_t adr, uint8_t data );  // write to CG-Memory in the LCD
void LCDDefSymbol  ( void );       // define new symbols (see LCDCfg.h)
//#ifdef __cplusplus
//} // extern "C"
//#endif
#endif
/** @}*/
