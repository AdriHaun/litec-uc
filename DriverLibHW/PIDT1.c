/***************************************************************************//**
Implementation file for the PIDT1 module for the AVR-ATMEGA controller (10 bit).

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
/** @file ADC.c Main source file for a PIDT1-controller using 10Bit ADC. */
#include "PIDT1.h"
#include <avr/interrupt.h>

#define TIM2_PRELOAD 0x83 // for 1ms-clk at 125kHz

// times scaled to ms other values scaled to 10Bit-ADC-values
         uint16_t ci = 0;
         uint16_t cd = 0;
         uint16_t kpr = 0;

         int16_t  e_old  = 0;
         int32_t  ui_old = 0;
         int32_t  ud_old = 0;

         int16_t  u_limit_max = 0;
         int16_t  u_limit_min = 0;

         uint16_t t1 = 0;
volatile uint16_t ta_pidt1 = 0;
volatile uint16_t tim2_cnt_pidt1 = 0;

volatile uint8_t  calc_controller = 0;

void PIDT1TimerInit ( uint8_t ta_ms ) {
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

  ta_pidt1 = ta_ms;
  tim2_cnt_pidt1 = 0;

  TIMSK2 = 0x01;
}

/***************************************************************************//**
Function for initialization of PIDT1
@param w_start start value
@param x_start start value
@param u_start start value
@retval - none
*******************************************************************************/
void PIDT1Init ( uint16_t w_start, uint16_t x_start, uint16_t u_start ) {
  ui_old = u_start;
  e_old = w_start - x_start;
}

void PIDT1Param ( uint8_t kr, uint16_t tn_ms, uint16_t tv_ms, uint16_t t1_ms, int16_t u_max, int16_t u_min ) {
  cd = tv_ms / ta_pidt1;         // calculate cd

  if (tn_ms >= 1)          // calculate ci
    ci = ta_pidt1 / tn_ms;
  else
    ci = 0;
  kpr = kr;
  t1 = t1_ms;

  if (u_max >= u_min ) {
    u_limit_max = u_max;
    u_limit_min = u_min;
  } else {
    u_limit_max = 1023;
    u_limit_min = -1023; // 10Bit-value
  }
}

/***************************************************************************//**
Function for calculating PIDT1 controller
@param
@retval u
*******************************************************************************/
int16_t PIDT1Calc  ( uint8_t enable, uint16_t w, uint16_t x ) {  // calc. Controller
  int16_t e;
  int16_t u;
  int32_t ui = 0;
  int32_t ud = 0;

  e=w-x;      // calculate control error

  if (enable == 0 ) {    // controller disabled --> return
    ui_old = 0;
    ud_old= 0;
    return 0;
  }

  ui = ci*e + ui_old;         // Integratorstellgroesse berechnen

  ud = 0;

  u = kpr*(e + ui + ud);       // Summenstellgroesse berechnen

  ud_old = ud;                 // Werte f. naechsten Takt speichern
  ui_old = ui;
  e_old  = e;
  if (u > u_limit_max ) {
    u = u_limit_max; // limit and ui_old unchanged -> Anti Windup hold
  } else {
   ui_old = ui;                         // anti windup
  }

  if (u < u_limit_min ) {
    u = u_limit_min; // limit and ui_old unchanged -> Anti Windup hold
  } else {
   ui_old = ui;                         // anti windup
  }

  return u;
}

// ISR (TIMER2_OVF_vect)
ISR (TIMER2_OVF_vect) {       // signal handler for tcnt2 overflow interrupt
  TCNT2=TIM2_PRELOAD;

  tim2_cnt_pidt1 ++;
  if ( tim2_cnt_pidt1 > ta_pidt1 ) {
  tim2_cnt_pidt1 = 0;
  //   calculate controller;
  }
}

/**@}*/
