/***************************************************************************//**
Interface file for the PIDT1 module for the AVR-ATMEGA controller (10 bit ADC)
*******************************************************************************/
/** @addtogroup Controller_api
@{*/
/** @file PIDT1.h Interface file for a PIDT1-controller using 10Bit ADC. */
#ifndef PIDT1_H
#define PIDT1_H

#include <avr/io.h>
#include <stdint.h>


   void PIDT1Init  ( uint16_t w_start, uint16_t x_start, uint16_t u_start );
   void PIDT1Param ( uint8_t kr, uint16_t tn_ms, uint16_t tv_ms, uint16_t t1_ms, int16_t u_max, int16_t u_min );
int16_t PIDT1Calc  ( uint8_t enable, uint16_t w, uint16_t x );  // calc. Controller

#endif // PIDT1_H
/**@}*/
