/***************************************************************************//**
Implementation file for the controller clk generator.

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
/** @file ControllerClk.c Main source file for a controller clk-generator. */
#include "ControllerClk.h"
#include <avr/interrupt.h>
#include <stdint.h>

volatile uint16_t ta = 0;               // controller periode
volatile uint16_t tim2_cnt = 0;         // counnt of timer 2 overflow int's

volatile function_to_call fun2call = 0;  // address of function to call

/***************************************************************************//**
Function for initialization of the Controller clk
@param ta_ms controller clk in msec
@param *call_function address of function to call ervery controller clk
@retval - none
*******************************************************************************/
void ControllerClockInit ( uint16_t ta_ms, function_to_call call_function ) {
// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 125,000 kHz
// Mode: Normal top=0xFF
// OC2A output: Disconnected
// OC2B output: Disconnected
// Timer Period: 1 ms
  ASSR=(0<<EXCLK) | (0<<AS2);
  TCCR2A=(0<<COM2A1) | (0<<COM2A0) | (0<<COM2B1) | (0<<COM2B0) | (0<<WGM21) | (0<<WGM20);
  TCCR2B=(0<<WGM22) | (1<<CS22) | (0<<CS21) | (1<<CS20);
  TCNT2=TIM2_PRELOAD;
  OCR2A=0x00;
  OCR2B=0x00;

  ta = ta_ms;
  tim2_cnt = 0;

  TIMSK2 = 0x01;

  fun2call = call_function;
}

// ISR (TIMER2_OVF_vect) --> generates controller clk
ISR (TIMER2_OVF_vect) { // signal handler for tcnt2 overflow interrupt
  TCNT2=TIM2_PRELOAD;

  tim2_cnt ++;
  if ( tim2_cnt > ta ) {
    tim2_cnt = 0;
    if (fun2call != 0)
     fun2call();                // call external function
  }
}

/**@}*/
