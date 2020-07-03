/***************************************************************************//**
Interface file for ATMEL AVR timer

@author LiTec/PAMG
@date 02.01.2012
@version 1.0

@param compiler switches: none
@param linker switches: none

@b History:
- 1.0 LiTec/PAMG 02.01.2012 initial version.
*******************************************************************************/
/** @addtogroup TIMER_api
@{*/
/** @file Timer.h Interface file for Timer-Module. */
#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>

//*****************************************************************************
// Prototypes for the APIs.
//*****************************************************************************
void TimerEnable       (uint8_t timer, uint8_t prescale, uint8_t mode);
void TimerStop         (uint8_t timer);
void TimerLoadValue    (uint8_t timer, uint16_t value);
void TimerEnableOVFInt (uint8_t timer);

#endif // __TIMER_H__
/**@}*/
