/***************************************************************************//**
Implementation file for the ADC module for the AVR-ATMEGA controller (10 bit).

@author LiTec/PAMG
@date 24.06.2007
@version 1.0

@param compiler switches: none
@param linker switches: none

@b History:
- 1.0 LiTec/PAMG 10.10.2009 initial version.
*******************************************************************************/
/** @addtogroup ADC_api
@{*/
/** @file ADC.c Main source file for ATMELs 10Bit ADC. */
#include "ADC.h"
#include <avr/interrupt.h>

uint8_t ADC_VREF_TYPE = ADC_VREF_TYPE_EXTERNAL_AVCC;

/***************************************************************************//**
Function for initialization of the ADC
@param vref register adjustment for reference voltage (see header)
@retval - none
*******************************************************************************/
void ADCInit ( uint8_t vref ) {
  ADC_VREF_TYPE = vref & ADC_VREF_TYPE_MASK;
}

/***************************************************************************//**
Function for reading an ADC-channel
@param channel channel, from which is read - (0 up to 7) or (0 up to 15), respectively
@retval average of 4 measurements without sign! (0-5V --> 0x0000-0x03FF)
*******************************************************************************/
uint16_t ADCReadChannel ( uint8_t channel ) {
  uint8_t i;
  uint16_t result = 0;

  ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS0);    // frequency prescaler
                               // set to 32 (1) and activate ADC (1)
  ADMUX = ADC_VREF_TYPE | (channel & 0x07); // use ref. voltage set by ADCInit
#if defined (__AVR_ATmega2560__)
  if (channel > 7) ADCSRB |=   1 << MUX5;
  else             ADCSRB &= ~(1 << MUX5);
#endif
   // choose channel
  /* after activation of the ADC the "Dummy-Readout" is recommended
     -> a value is read and discarded to let the ADC "warm up" */
  /* the actual measurement - average of 4 consecutive conversions */
  cli ();
  for (i=0; i<5; i++)  {
    ADCSRA |= (1<<ADSC);           // a "single conversion"
    while (!(ADCSRA & (1<<ADIF))); // wait for completion of the conversion
                                   // (ADIF bit)
   if (i > 0) {
     result += ADC;                // add up the conversion results
   }
   ADCSRA |= (1<<ADIF); // delete ADIF (see DB, is done otherwise by the ISR),
  }                     // because the loop in the next iteration isn't waiting
                        // until the conversion is completed otherwise
  sei ();
  ADCSRA &= (uint8_t)~(1<<ADEN);  // deactivate ADC
  return (result / 4);          // divide sum by 4 = arithmetic mean
}
/**@}*/
