/***************************************************************************//**
Interface file for the external interrupt routines.
*******************************************************************************/
/** @addtogroup ExtInt_api
@{*/
/** @file ExtInt.h Interface file for the external interrupt routines. */
#ifndef __ExtInt_H__
#define __ExtInt_H__

#include <stdint.h>

#define EXT_INT_0 0
#define EXT_INT_1 1
#define EXT_INT_2 2
#define EXT_INT_3 3
#define EXT_INT_4 4
#define EXT_INT_5 5
#define EXT_INT_6 6
#define EXT_INT_7 7

#define EXT_INT_MODE_LOW_LEVEL    0x00
#define EXT_INT_MODE_ANY_EDGE     0x01
#define EXT_INT_MODE_FALLING_EDGE 0x02
#define EXT_INT_MODE_RISING_EDGE  0x03

void ExtIntInit( uint8_t int_nr, uint8_t mode ); // set mode of ext. int_nr
void ExtIntEnable( uint8_t int_nr ); // enables external int_nr
void ExtIntDisable( uint8_t int_nr ); // disables external int_nr

#endif // __ExtInt_H__
/**@}*/
