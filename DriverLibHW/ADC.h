/***************************************************************************//**
Interface file for the ADC module for the AVR-ATMEGA controller (10 bit)
*******************************************************************************/
/** @addtogroup ADC_api
@{*/
/** @file ADC.h Interface file for ATMELs 10Bit ADC. */
#ifndef ADC_H
#define ADC_H

#include <avr/io.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

#if defined (__AVR_ATmega2560__)
  // ADC voltage reference: internal 1.1V, AREF disconnected
  #define ADC_VREF_TYPE_INTERNAL_AREF_1_1 0x80
#endif

#define ADC_VREF_TYPE_EXTERNAL_AVCC 0x40  // ADC voltage reference: AVCC pin
#define ADC_VREF_TYPE_EXTERNAL_AREF 0x00  // ADC voltage reference: AREF pin
#define ADC_VREF_TYPE_INTERNAL_AREF 0xC0  // ADC voltage ref. int., AREF discon.

#define ADC_VREF_TYPE_MASK          0xC0

void   ADCInit        ( uint8_t vref );     // set reference voltage source
uint16_t ADCReadChannel ( uint8_t channel );  // read specified channel

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ADC_H
/**@}*/
