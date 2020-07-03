/***************************************************************************//**
Definitions for the LITEC- Arduino Shield
*******************************************************************************/
/** @file LITECShieldDefinitions.h Definition file for
          7-Segment displays and keys S0, S1. */

#include <stdint.h>
#if defined (__SAM3X8E__)
  #include "asf.h"
#endif

#define SEGMA 0
#define SEGMB 1
#define SEGMC 2
#define SEGMD 3
#define SEGME 4
#define SEGMF 5
#define SEGMG 6
#define SEGMDP 7


// static declaration of display segments
__attribute__((unused)) static uint8_t segm_inv [16] =
/* 0,    1,    2,    3,    4,     5,    6,    7,    8,    9,    A,    b,    C     d     E     F */
{0xC0, 0xF9, 0xA4, 0xB0, 0x99,  0x92, 0x82, 0xF8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};

__attribute__((unused)) static uint8_t segm [16] =
/* 0,    1,    2,    3,    4,     5,    6,    7,    8,    9,    A,    b,    C     d     E     F */
{0x3F, 0x06, 0x5B, 0x4F, 0x66,  0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

__attribute__((unused)) static uint8_t segmS_inv = (1<<SEGMB) | (1<<SEGME) | (1<<SEGMDP);
__attribute__((unused)) static uint8_t segmE_inv = (1<<SEGMB) | (1<<SEGMC) | (1<<SEGMDP);

#if defined (__AVR_ATmega2560__)
  #define INIT_KEYS DDRD &= ~0x0C; PORTD |= 0x0C;
  #define S0 ((~PIND & 0x04) >> 2)
  #define S1 ((~PIND & 0x08) >> 3)
//  #define S2 ((~PIND & 0x04) >> 2)
//  #define S3 ((~PIND & 0x08) >> 3)

#elif defined (__SAM3X8E__)
  #define S0 ((~PINCOMM & 0x04) >> 2)
  #define S1 ((~PINCOMM & 0x08) >> 3)

  #define MAX_PORT_NR 5

  /* Registers and associated bit numbers */
  #define PINx7   7
  #define PINx6   6
  #define PINx5   5
  #define PINx4   4
  #define PINx3   3
  #define PINx2   2
  #define PINx1   1
  #define PINx0   0

  #define DDRB( val ) DDRx ( 0, (val))
  #define DDRA( val ) DDRx ( 1, (val))
  #define DDRL( val ) DDRx ( 2, (val))
  #define DDRC( val ) DDRx ( 3, (val))
  #define DDRCOMM( val ) DDRx ( 4, (val))

  #define PINB    PINx (0)
  #define PINA    PINx (1)
  #define PINL    PINx (2)
  #define PINC    PINx (3)
  #define PINCOMM PINx (4)

  #define PORTB( val )    PORTx_set ( 0, (val))
  #define PORTA( val )    PORTx_set ( 1, (val))
  #define PORTL( val )    PORTx_set ( 2, (val))
  #define PORTC( val )    PORTx_set ( 3, (val))
  #define PORTCOMM( val ) PORTx_set ( 4, (val))

  static uint8_t port_map_tab [5][8] =
  {{PIO_PB14_IDX, PIO_PB21_IDX, PIO_PC12_IDX, PIO_PC13_IDX, PIO_PC29_IDX, PIO_PD7_IDX, PIO_PD8_IDX, PIO_PB27_IDX},
  {PIO_PB26_IDX, PIO_PA14_IDX, PIO_PA15_IDX, PIO_PD0_IDX, PIO_PD1_IDX, PIO_PD2_IDX, PIO_PD3_IDX, PIO_PD6_IDX},
  {PIO_PC14_IDX, PIO_PC15_IDX, PIO_PC16_IDX, PIO_PC17_IDX, PIO_PC18_IDX, PIO_PC19_IDX, PIO_PA20_IDX, PIO_PA19_IDX},
  {PIO_PC5_IDX, PIO_PC4_IDX, PIO_PC3_IDX, PIO_PC2_IDX, PIO_PC1_IDX, PIO_PD10_IDX, PIO_PA7_IDX, PIO_PD9_IDX},
  {PIO_PD5_IDX, PIO_PD4_IDX, PIO_PA10_IDX, PIO_PA11_IDX, PIO_PB25_IDX, PIO_PC28_IDX, PIO_PB13_IDX, PIO_PB12_IDX}};

// static declaration of display segments
__attribute__((unused)) static uint8_t ddr_copy [5] = {0x00, 0x00, 0x00, 0x00, 0x00};

  void PORTx_set (uint8_t pnr, uint8_t val) {
    uint8_t i;

    if ( pnr > MAX_PORT_NR ) return;

    for ( i=0; i<8; i++) {
      if ((val)&(1<<i)) gpio_set_pin_high (port_map_tab[pnr][i]);
      else              gpio_set_pin_low  (port_map_tab[pnr][i]);
    }
  }
  uint8_t PORTx_state (uint8_t pnr) {
    uint8_t i;
    uint8_t value = 0;

    if ( pnr > MAX_PORT_NR ) return 0;

    for ( i=0; i<8; i++) {
     value |= (uint8_t)(gpio_pin_is_high(port_map_tab[pnr][i]))<<i;
    }
	return value;
  }

  void DDRx (uint8_t pnr, uint8_t val) {
    uint8_t i;

    if ( pnr > MAX_PORT_NR ) return;

    for ( i=0; i<8; i++) {
      if ((val)&(1<<i)) gpio_configure_pin(port_map_tab[pnr][i], (PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT));
      else              gpio_configure_pin(port_map_tab[pnr][i], (PIO_TYPE_PIO_INPUT | PIO_PULLUP));
    }
  ddr_copy [pnr] = val;
  }

  uint8_t PINx (uint8_t pnr) {
    uint8_t i;
    uint8_t value = 0;

    if ( pnr > MAX_PORT_NR ) return 0;

    for ( i=0; i<8; i++) {
     value |= (uint8_t)(gpio_pin_is_high(port_map_tab[pnr][i]))<<i;
    }
	return value;
  }
#endif
