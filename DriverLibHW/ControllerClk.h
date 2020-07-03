/***************************************************************************//**
Interface file for the PIDT1 module for the AVR-ATMEGA controller (10 bit ADC)
*******************************************************************************/
/** @addtogroup Controller_api
@{*/
/** @file ControllerClk.h Interface file for a controller clk-generator. */
#ifndef CONTROLLERCLK_H
#define CONTROLLERCLK_H

#include <stdint.h>

#define TIM2_PRELOAD 0x83 // for 1ms-clk at 125kHz

typedef void (*function_to_call)(void);  // address of function to call


void ControllerClockInit ( uint16_t ta_ms, function_to_call call_function );

#endif // CONTROLLERCLK_H
/**@}*/
