/***************************************************************************//**
Implementation file for a matrix keyboard driver.
For key-codes see MatrixKeyboardCfg.h

@author LiTec/PAMG
@date 10.10.2009
@version 1.1

@param compiler switches: none
@param linker switches: none

@b History:
- 1.0 LiTec/PAMG 10.10.2009 initial version.
*******************************************************************************/
/** @addtogroup MatrixKeyboard_api
@{*/
/** @file MatrixKeyboard.c Main source file for matrix keyboard driver. */
#include "MatrixKeyboard.h"
#include "LITECShieldDefinitions.h" // for S0, S1 and 7-Segment-Display

/***************************************************************************//**
Function for scanning the matrix keyboard. (rows are scanned first)
@retval keycode ( 0 - MATRIX_KEYBOARD_NR_ROWS x MATRIX_KEYBOARD_NR_LINES)
@retval 0xFF no key pressed
*******************************************************************************/
inline uint8_t ScanMatrixKeyboard (void) {
  uint8_t rows = 0;
  uint8_t column = 0;

  KEY_PORT_DIR;
  KEY_PORT_OUT = 0xFF;

  for (rows = 0; rows < MATRIX_KEYBOARD_NR_ROWS; rows++) {
    KEY_PORT_OUT |= 0x0F;
    KEY_PORT_OUT &= ~(0x01 << rows);   // clear output bit
    for (column = 0; column < MATRIX_KEYBOARD_NR_COLUMNS; column++ ) {
      if ( (KEY_PORT_IN & (0x10 << column)) == 0 )
        return (rows*MATRIX_KEYBOARD_NR_COLUMNS+column);
	}
  }
  return 0xFF;                          // no key pressed
}
/** @}*/
