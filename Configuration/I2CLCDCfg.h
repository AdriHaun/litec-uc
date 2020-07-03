/***************************************************************************//**
Configuration file to config. driver for I2C-LCD with Hitachi HD44780 Controller
4 BIT hardware interface and connected via I2C-PCF8574

@note Copy the file I2CLCDCfg.h to your local project folder and edit the
      configuration

LCD-Pin | LCD-Name | Port-pin | Description
--------|----------|----------|----------------------
      1 |   GND    | 9        | GND
      2 |  +5V     |10        | VCC (+5V)
      3 |   VLC    |          | LCD contrast control voltage 0..1V
      4 |   RS     | 1        | Px.0
      5 |   RD     | 2        | Px.1
      - |    -     | 3        | Px.2  -->  Backlight or key (see hardware)
      6 |   EN     | 4        | Px.3
     11 |   D4     | 5        | Px.4
     12 |   D5     | 6        | Px.5
     13 |   D6     | 7        | Px.6
     14 |   D7     | 8        | Px.7
*******************************************************************************/
/** @addtogroup LCD_api
@{*/
/** @file I2CLCDCfg.h Configuration file for LCD connected by I2C.*/

#ifndef _I2CLCDCfg_H
#define _I2CLCDCfg_H

#if defined (HW_8051)
  #include <reg51.h>    // HW-Def. for 8051
#elif defined (__AVR_ATmega2560__)
  #include <avr/io.h>   // HW-Def. for AVR-Controller
#else
  #error "device type not defined"
#endif

#define NUM_LINES 4      // number of lines
#define NUM_ROWS 20      // number of rows
#define RS        0x01
#define RW        0x02
#define EN        0x04

#define BACKLIGHT 0x08

#if defined (HW_8051)
#elif defined (__AVR_ATmega2560__)
#else
  #error "device type not defined"
#endif

// User defined Symbols (symbol 0 up to 7)
/*** Symbol Nr. 0hex ***/
#define SYMBOL0_LINE0 0x1F      /*   * * * * *   */
#define SYMBOL0_LINE1 0x00      /*   . . . . .   */
#define SYMBOL0_LINE2 0x00      /*   . . . . .   */
#define SYMBOL0_LINE3 0x00      /*   . . . . .   */
#define SYMBOL0_LINE4 0x00      /*   . . . . .   */
#define SYMBOL0_LINE5 0x00      /*   . . . . .   */
#define SYMBOL0_LINE6 0x00      /*   . . . . .   */
#define SYMBOL0_LINE7 0x1F      /*   * * * * *   */
/*** Symbol Nr.1hex ***/
#define SYMBOL1_LINE0 0x1F      /*   * * * * *   */
#define SYMBOL1_LINE1 0x10      /*   * . . . .   */
#define SYMBOL1_LINE2 0x10      /*   * . . . .   */
#define SYMBOL1_LINE3 0x10      /*   * . . . .   */
#define SYMBOL1_LINE4 0x10      /*   * . . . .   */
#define SYMBOL1_LINE5 0x10      /*   * . . . .   */
#define SYMBOL1_LINE6 0x10      /*   * . . . .   */
#define SYMBOL1_LINE7 0x1F      /*   * * * * *   */
/*** Symbol Nr. 2hex ***/
#define SYMBOL2_LINE0 0x1F      /*   * * * * *   */
#define SYMBOL2_LINE1 0x18      /*   * * . . .   */
#define SYMBOL2_LINE2 0x18      /*   * * . . .   */
#define SYMBOL2_LINE3 0x18      /*   * * . . .   */
#define SYMBOL2_LINE4 0x18      /*   * * . . .   */
#define SYMBOL2_LINE5 0x18      /*   * * . . .   */
#define SYMBOL2_LINE6 0x18      /*   * * . . .   */
#define SYMBOL2_LINE7 0x1F      /*   * * * * *   */
/*** Symbol Nr. 3hex ***/
#define SYMBOL3_LINE0 0x1F      /*   * * * * *   */
#define SYMBOL3_LINE1 0x1C      /*   * * * . .   */
#define SYMBOL3_LINE2 0x1C      /*   * * * . .   */
#define SYMBOL3_LINE3 0x1C      /*   * * * . .   */
#define SYMBOL3_LINE4 0x1C      /*   * * * . .   */
#define SYMBOL3_LINE5 0x1C      /*   * * * . .   */
#define SYMBOL3_LINE6 0x1C      /*   * * * . .   */
#define SYMBOL3_LINE7 0x1F      /*   * * * * *   */
/*** Symbol Nr. 4hex ***/
#define SYMBOL4_LINE0 0x1F      /*   * * * * *   */
#define SYMBOL4_LINE1 0x1E      /*   * * * * .   */
#define SYMBOL4_LINE2 0x1E      /*   * * * * .   */
#define SYMBOL4_LINE3 0x1E      /*   * * * * .   */
#define SYMBOL4_LINE4 0x1E      /*   * * * * .   */
#define SYMBOL4_LINE5 0x1E      /*   * * * * .   */
#define SYMBOL4_LINE6 0x1E      /*   * * * * .   */
#define SYMBOL4_LINE7 0x1F      /*   * * * * *   */
/*** Symbol Nr. 5hex ***/
#define SYMBOL5_LINE0 0x10      /*   * . . . .   */
#define SYMBOL5_LINE1 0x10      /*   * . . . .   */
#define SYMBOL5_LINE2 0x10      /*   * . . . .   */
#define SYMBOL5_LINE3 0x10      /*   * . . . .   */
#define SYMBOL5_LINE4 0x10      /*   * . . . .   */
#define SYMBOL5_LINE5 0x10      /*   * . . . .   */
#define SYMBOL5_LINE6 0x10      /*   * . . . .   */
#define SYMBOL5_LINE7 0x10      /*   * . . . .   */
/*** Symbol Nr. 6hex ***/
#define SYMBOL6_LINE0 0x01      /*   . . . . *   */
#define SYMBOL6_LINE1 0x01      /*   . . . . *   */
#define SYMBOL6_LINE2 0x01      /*   . . . . *   */
#define SYMBOL6_LINE3 0x01      /*   . . . . *   */
#define SYMBOL6_LINE4 0x01      /*   . . . . *   */
#define SYMBOL6_LINE5 0x01      /*   . . . . *   */
#define SYMBOL6_LINE6 0x01      /*   . . . . *   */
#define SYMBOL6_LINE7 0x01      /*   . . . . *   */
/*** Symbol Nr. 7hex ***/
#define SYMBOL7_LINE0 0x04      /*   . . * . .   */
#define SYMBOL7_LINE1 0x0E      /*   . * * * .   */
#define SYMBOL7_LINE2 0x1F      /*   * * * * *   */
#define SYMBOL7_LINE3 0x04      /*   . . * . .   */
#define SYMBOL7_LINE4 0x04      /*   . . * . .   */
#define SYMBOL7_LINE5 0x1F      /*   * * * * *   */
#define SYMBOL7_LINE6 0x0E      /*   . * * * .   */
#define SYMBOL7_LINE7 0x04      /*   . . * . .   */

#endif /* _I2CLCDCfg_H  */
/**@}*/
