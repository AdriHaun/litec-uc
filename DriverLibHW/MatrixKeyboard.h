/***************************************************************************//**
Interface file for a matrix keyboard driver.
For key-codes see MatrixKeyboardCfg.h
*******************************************************************************/
/** @addtogroup MatrixKeyboard_api
@{*/
/** @file MatrixKeyboard.h Interface file for matrix keyboard driver. */
#ifndef _MatrixKeyboard_H
#define _MatrixKeyboard_H

#include "MatrixKeyboardCfg.h"
#include <stdint.h>

uint8_t ScanMatrixKeyboard (void); // returns scanned key-code

#endif // _MatrixKeyboard_H
/** @}*/
