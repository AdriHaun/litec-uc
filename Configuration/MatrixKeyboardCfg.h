/***************************************************************************//**
Configuration file for a matrix keyboard driver.

@note Copy the file MatrixKeyboardCfg.h to your local project folder and edit
      the configuration

The following table shows the calculation of the hex-key-code at a 4x4 keyboard.

 key-code | column 1 | column 2 | column 3 | column 4
----------|----------|----------|----------|---------
row 1     |    0     |    1     |    2     |    3
row 2     |    4     |    5     |    6     |    7
row 3     |    8     |    9     |    A     |    B
row 4     |    C     |    D     |    E     |    F
*******************************************************************************/
/** @addtogroup MatrixKeyboard_api
@{*/
/** @file MatrixKeyboardCfg.h Configuration file for matrix keyboard driver. */

#ifndef _MatrixKeyboardCfg_H
#define _MatrixKeyboardCfg_H

#define MATRIX_KEYBOARD_NR_ROWS     4
#define MATRIX_KEYBOARD_NR_COLUMNS  4

#if defined (HW_8051)
  #include <reg51.h>
  #define KEY_PORT_OUT P2
  #define KEY_PORT_IN  P2
  #define KEY_PORT_DIR ;
#elif defined (__AVR_ATmega2560__)
  #include <avr/io.h>
  #define KEY_PORT_OUT PORTC
  #define KEY_PORT_IN  PINC
  #define KEY_PORT_DIR DDRC  = 0x0F;    // row: OUTPUT, column: INPUT
#endif

#endif // _MatrixKeyboard_H
/** @}*/
