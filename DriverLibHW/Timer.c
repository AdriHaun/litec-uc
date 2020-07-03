/***************************************************************************//**
Implementation file for ATMEL AVR timer

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
/** @file Timer.c Main source file for Timer-Module. */
#include <avr/io.h>
#include "HWTimer.h"

/***************************************************************************//**
Function to enable timer
@param timer select one of the controllers timer (0 .. n see datasheet)
@param prescale defines the clk (depends on the CPU-clk, see HWTimer.h)
@param mode set timer mode (see datasheet and see HWTimer.h)
@retval - none
*******************************************************************************/
void TimerEnable(uint8_t timer, uint8_t prescale, uint8_t mode) {
  switch ( timer ) {
   case TIMER_0 :                             // Timer 0
     TCCR0A &= ~((1<<WGM01)|(1<<WGM00));
     TCCR0A |= (mode&0x03);             // set WGM00 and WGM01

     TCCR0B &= ~((1<<WGM02)|(1<<CS02)|(1<<CS01)|(1<<CS00));  // disable clock source
     TCCR0B |= (prescale & ((1<<CS02)|(1<<CS01)|(1<<CS00)));
     TCCR0B |= (mode&0x04) << 1;        // set WGM02
     break;
   case TIMER_1 :                             // Timer 1
     TCCR1A &= ~((1<<WGM11)|(1<<WGM10));
     TCCR1A |= (mode&0x03);             // set WGM10 and WGM11

     TCCR1B &= ~((1<<WGM13)|(1<<WGM12)|(1<<CS12)|(1<<CS11)|(1<<CS10));  // disable clock source
     TCCR1B |= (prescale & ((1<<CS12)|(1<<CS11)|(1<<CS10)));
     TCCR1B |= (mode&0x0C) << 1;        // set WGM12 and WGM13
     break;
   case TIMER_2 :                             // Timer 2
     TCCR2A &= ~((1<<WGM21)|(1<<WGM20));
     TCCR2A |= (mode&0x03);             // set WGM20 and WGM21

     TCCR2B &= ~((1<<WGM22)|(1<<CS22)|(1<<CS21)|(1<<CS20));  // disable clock source
     TCCR2B |= (prescale & ((1<<CS22)|(1<<CS21)|(1<<CS20)));
     TCCR2B |= (mode&0x04) << 1;        // set WGM22
     break;
   case TIMER_3 :                             // Timer 3
     TCCR3A &= ~((1<<WGM31)|(1<<WGM30));
     TCCR3A |= (mode&0x03);             // set WGM30 and WGM31

     TCCR3B &= ~((1<<WGM33)|(1<<WGM32)|(1<<CS32)|(1<<CS31)|(1<<CS30));  // disable clock source
     TCCR3B |= (prescale & ((1<<CS32)|(1<<CS31)|(1<<CS30)));
     TCCR3B |= (mode&0x0C) << 1;        // set WGM32 and WGM33
	 break;
   case TIMER_4 :                             // Timer 4
     TCCR4A &= ~((1<<WGM11)|(1<<WGM10));
     TCCR4A |= (mode&0x03);             // set WGM40 and WGM41

     TCCR4B &= ~((1<<WGM43)|(1<<WGM42)|(1<<CS42)|(1<<CS41)|(1<<CS40));  // disable clock source
     TCCR4B |= (prescale & ((1<<CS42)|(1<<CS41)|(1<<CS40)));
     TCCR4B |= (mode&0x0C) << 1;        // set WGM42 and WGM43
     break;
   case TIMER_5 :                             // Timer 5
     TCCR5A &= ~((1<<WGM51)|(1<<WGM50));
     TCCR5A |= (mode&0x03);             // set WGM50 and WGM51

     TCCR5B &= ~((1<<WGM53)|(1<<WGM52)|(1<<CS52)|(1<<CS51)|(1<<CS50));  // disable clock source
     TCCR5B |= (prescale & ((1<<CS52)|(1<<CS51)|(1<<CS50)));
     TCCR5B |= (mode&0x0C) << 1;        // set WGM12 and WGM13
     break;
   default:
     break;
  }
}

/***************************************************************************//**
Function to disable timer
@param timer select one of the controllers timer (0 .. n see datasheet)
@retval - none
*******************************************************************************/
void TimerStop(uint8_t timer) {

  switch ( timer ) {
   case TIMER_0 :                             // Timer 0
     TCCR0B &= ~0x07;                         // Prescale-Factor set null
     break;
   case TIMER_1 :                             // Timer 1
     TCCR1B &= ~0x07;                         // Prescale-Factor set null
     break;
   case TIMER_2 :                             // Timer 2
     TCCR2B &= ~0x07;                         // Prescale-Factor set null
     break;
   case TIMER_3 :                             // Timer 3
     TCCR3B &= ~0x07;                         // Prescale-Factor set null
	 break;
   case TIMER_4 :                             // Timer 4
     TCCR4B &= ~0x07;                         // Prescale-Factor set null
	 break;
   case TIMER_5 :                             // Timer 5
     TCCR5B &= ~0x07;                         // Prescale-Factor set null
	 break;
   default:                                   // Error
     break;                                   // Do nothing
  }
}

/***************************************************************************//**
Function to preload timer counter register
@param timer select one of the controllers timer (0 .. n see datasheet)
@param value value to preload selected timer
@retval - none
*******************************************************************************/
void TimerLoadValue(uint8_t timer, uint16_t value) {
  switch ( timer ) {
   case TIMER_0 :                             // Timer 0
     TCNT0 = value % 256;
     break;
   case TIMER_1 :                             // Timer 1
     TCNT1H = value / 256;
     TCNT1L = value % 256;
     break;
   case TIMER_2 :                             // Timer 2
     TCNT2 = value % 256;
     break;
   case TIMER_3 :                             // Timer 3
     TCNT3H = value / 256;
     TCNT3L = value % 256;
     break;
   case TIMER_4 :                             // Timer 4
     TCNT4H = value / 256;
     TCNT4L = value % 256;
     break;
   case TIMER_5 :                             // Timer 5
     TCNT5H = value / 256;
     TCNT5L = value % 256;
     break;
   default:                                   // Do nothing
     break;
  }
}
/***************************************************************************//**
Function to enable timer overflow interrupt
@param timer select one of the controllers timer (0 .. n see datasheet)
@retval - none
*******************************************************************************/
void TimerEnableOVFInt(uint8_t timer) {
  switch ( timer ) {
   case TIMER_0 :                             // Timer 0
     TIMSK0 |= 0x01;
     break;
   case TIMER_1 :                             // Timer 1
     TIMSK1 |= 0x01;
     break;
   case TIMER_2 :                             // Timer 2
     TIMSK2 |= 0x01;
     break;
   case TIMER_3 :                             // Timer 3
     TIMSK3 |= 0x01;
	 break;
   case TIMER_4 :                             // Timer 4
     TIMSK4 |= 0x01;
     break;
   case TIMER_5 :                             // Timer 5
     TIMSK5 |= 0x01;
     break;
   default:
     break;
  }
}
/**@}*/
