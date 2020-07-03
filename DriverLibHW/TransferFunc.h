/***************************************************************************//**
Interface file for transfer functions.

@author LiTec/PAMG
@date 04.04.2013
@version 1.0

@param compiler switches: none
@param linker switches: none

@b History:
- 1.0 LiTec/PAMG 10.10.2009 initial version.
*******************************************************************************/
/** @addtogroup Controller_api
@{*/
/** @file TransferFunc.h Interface file for transfer functions. */
#ifndef TRANSFER_FUNC_H
#define TRANSFER_FUNC_H

#include <stdint.h>

#define MAX_ORD 5

void TransferFuncInit ( void );
void TransferFuncParam ( uint8_t ord_num, uint8_t ord_den, float *a, float *b );
void TransferFuncCalc  ( uint8_t enable, float u, float* y );  // calc. transfer func.
void TransferFuncPrintDebug (void);
#endif // TRANSFER_FUNC_H
/**@}*/
