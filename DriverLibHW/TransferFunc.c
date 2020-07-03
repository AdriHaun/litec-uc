/***************************************************************************//**
Implementation file for transfer functions.

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
/** @file TransferFunc.c Main source file for transfer functions. */
#include "TransferFunc.h"
#include <avr/interrupt.h>
#include <stdio.h>  // for printf ()

float u [MAX_ORD];
float y [MAX_ORD];
float a [MAX_ORD];
float b [MAX_ORD];
uint8_t den_ord = MAX_ORD;
uint8_t num_ord = MAX_ORD;

void TransferFuncInit ( void ) {
  uint8_t i;
  for ( i=0; i<MAX_ORD; i++ ) {
    u[i] = y[i] = 0.0;
  }
}

void TransferFuncParam ( uint8_t ord_num, uint8_t ord_den, float *b_vect, float *a_vect ) {
  uint8_t i;

  if ( (ord_num > MAX_ORD) || (ord_den > MAX_ORD) || (ord_num > ord_den) ) return;

  den_ord = ord_den;
  num_ord = ord_num;

  for ( i=0; i<ord_num+1; i++,b_vect++ ) {
    b[i] = *b_vect;
  }
  for ( ; i<ord_den+1; i++ ) {
    b[i] = 0.0;                         // init unused coeffizients with 0.0
  }
  for ( i=0; i<ord_den+1; i++,a_vect++ ) {
    a[i] = *a_vect;
  }
}

void TransferFuncCalc  ( uint8_t enable, float un, float *yn ) {  // calc. Controller
  uint8_t i = 0;
  float y_temp = 0.0;
  
  if (enable) {
    for ( i = 0; i<=den_ord-1; i++ ) {
      y_temp = y_temp + ( b[i]*u[den_ord-i-1] - a[i]*y[den_ord-i-1] );
    }

    *yn = (y_temp + un*b[den_ord]) / a[den_ord];

    for ( i= 0; i<den_ord; i++ ) {    // move data within storage field
      u[den_ord-i] = u[den_ord-i-1];
      y[den_ord-i] = y[den_ord-i-1];
    }

    u[0] = un;
    y[0] = *yn;
  } else {
    
  }
}

void TransferFuncPrintDebug (void) {
  uint8_t i;

  printf ("\nOrd: num=%d den=%d",num_ord, den_ord);

  printf ("\nb: ");
  for (i=0; i<MAX_ORD; i++) {
    printf ("%f ", (double)b[i]);
  }
  printf ("\na: ");
  for (i=0; i<MAX_ORD; i++) {
   printf ("%f ", (double)a[i]);
  }
  printf ("\nu: ");

  for (i=0; i<MAX_ORD; i++) {
    printf ("%f ", (double)u[i]);
  }
  printf ("\ny: ");

  for (i=0; i<MAX_ORD; i++) {
    printf ("%f ", (double)y[i]);
  }
  printf ("\n");
}
/**@}*/
