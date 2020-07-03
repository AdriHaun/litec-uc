/***************************************************************************//**
Driver for LC-Displays with Hitachi HD44780 Controller.
The display is controlled by a 4 BIT hardware interface (see LCDCfg.h).

@author LiTec/PAMG
@date 01.02.2010
@version 1.1

@param compiler switches: @b -OS size optimization
@param linker switches: none

@b History:
- 1.1 LiTec/PAMG 01.02.2010 routine for adding symbols implemented
                            -> LCDDefSymbol.
- 1.0 LiTec/PAMG 10.10.2009 initial version.
*******************************************************************************/
/** @addtogroup LCD_api
@{*/
/** @file LCD.c Main source file for LC-Displays with Hitachi HD44780 Controller. */

#include "LCD.h"
#include "Wait.h"

/***************************************************************************//**
Function for busy wait
@param - none
@retval - none
*******************************************************************************/
static void LCDBusy(void){
  LCD_OUTPORT |= EN;
  WaitMs (1);                      // keine HW-Zugriffe, hier nur 1m warten
  return;
}

/***************************************************************************//**
Function for writing a data-byte to the data-register in LCD
@param data data to be written to the data-register
@retval - none
*******************************************************************************/
void LCDData ( uint8_t data ) {
// schreibt HIGH Nibble der Daten
  LCDBusy ();
 // LCD_OUTPORT = (data&0xF0) | EN | RS | (LCD_OUTPORT & BACKLIGHT);    /* setzt EN-Bit   */
  LCD_OUTPORT = ((data&0xF0) & ~EN) | RS | (LCD_OUTPORT & BACKLIGHT);   /* loescht EN-Bit */
// schreibt LOW Nibble der Daten
  LCDBusy ();
 // LCD_OUTPORT = (data<<4) | EN | RS | (LCD_OUTPORT & BACKLIGHT);    /* setzt EN-Bit   */
  LCD_OUTPORT = ((data<<4) & ~EN) | RS | (LCD_OUTPORT & BACKLIGHT);   /* loescht EN-Bit */
}

/***************************************************************************//**
Function for writing the high nibble of ctrl to the control-register in LCD
@param ctrl data to be written to the control-register
@retval - none
*******************************************************************************/
void LCDCtrlHighNibble ( uint8_t ctrl ) {
  LCDBusy ();
 // LCD_OUTPORT = (((ctrl&0xF0) | EN) & ~RS) | (LCD_OUTPORT & BACKLIGHT);    /* setzt EN-Bit   */
  LCD_OUTPORT = (((ctrl&0xF0) & ~EN) & ~RS) | (LCD_OUTPORT & BACKLIGHT);   /* loescht EN-Bit */
}

/***************************************************************************//**
Function for writing a control-byte to the control-register in LCD
@param ctrl data to be written to the control-register
@retval - none
*******************************************************************************/
void LCDCtrl ( uint8_t ctrl ) {
//  LCDCtrlHighNibble ( ctrl );
//  LCDCtrlHighNibble ( ctrl << 4 );
// schreibt HIGH Nibble der Daten
  LCDBusy ();
 // LCD_OUTPORT = (((ctrl&0xF0) | EN) & ~RS) | (LCD_OUTPORT & BACKLIGHT);    /* setzt EN-Bit   */
  LCD_OUTPORT = (((ctrl&0xF0) & ~EN) & ~RS) | (LCD_OUTPORT & BACKLIGHT);   /* loescht EN-Bit */
// schreibt LOW Nibble der Daten
  LCDBusy ();
//  LCD_OUTPORT = (((ctrl<<4) | EN) & ~RS) | (LCD_OUTPORT & BACKLIGHT);    /* setzt EN-Bit   */
  LCD_OUTPORT = (((ctrl<<4) & ~EN) & ~RS) | (LCD_OUTPORT & BACKLIGHT);   /* loescht EN-Bit */
}

/***************************************************************************//**
Function for setting the address-pointer in the display
@param addr address to be set
@retval - none
*******************************************************************************/
void LCDSetAddr (uint8_t addr) {
  LCDCtrl ( addr |= 0x80 );
}

/***************************************************************************//**
Function for initializing the display
@param - none
@retval - none
*******************************************************************************/
void LCDInit ( void ) {
  LCD_OUTPORT_DDR = 0xFF;

  WaitMs (500);

  LCDCtrlHighNibble (0x30); /*func set: interface is 8 bit long*/
  WaitMs (5);
  LCDCtrlHighNibble (0x30); /*func set: interface is 8 bit long*/
  WaitMs (1);
  LCDCtrlHighNibble (0x30); /*func set: interface is 8 bit long*/
  WaitMs (1);
  LCDCtrlHighNibble (0x20); /*func set: interface is 4 bit long*/
  WaitMs (1);

  LCDCtrlHighNibble (0x20); /*func set: interface is 4 bit long*/
  WaitMs (1);
  LCDCtrlHighNibble (0x80); /* number of display lines is 2    */
  WaitMs (1);

  LCDCtrlHighNibble (0x00);
  LCDBusy ();
  LCDCtrlHighNibble (0x80);      /* display off;*/
  LCDBusy ();

  LCDCtrlHighNibble (0x00);
  LCDBusy ();
  LCDCtrlHighNibble (0x10);      /* display on; and Cursor without BLINK*/
  LCDBusy ();

  LCDCtrlHighNibble (0x00);
  LCDBusy ();
  LCDCtrlHighNibble (0x60); /* entry mode: increment, no shift */
  LCDBusy ();

  LCD_BACKLIGHT_OFF;                  // Backlight OFF
  }

/***************************************************************************//**
Function for clearing the display
@param - none
@retval - none
*******************************************************************************/
void LCDClear ( void ) {
//  LCDCtrl (0x01); /* clear display */
//  LCDCtrl (0x0C); /* Display ON, Cursor OFF, Blink OFF*/
  LCDCtrlHighNibble (0x00);
  LCDBusy ();

  LCDCtrlHighNibble (0x10);   /* clear display */
  LCDBusy ();

  LCDCtrlHighNibble (0x00);
  LCDBusy ();

  LCDCtrlHighNibble (0xC0); /* Display ON, Cursor OFF, Blink OFF*/
  LCDBusy ();
}

/***************************************************************************//**
Routine for clearing a line on the display
@param line number of line to be cleared @b (1 - NUM_ROWS)
@retval - none
*******************************************************************************/
void LCDClearLine (uint8_t line) {
  uint8_t i;
    for ( i=0; i<NUM_ROWS+1; i++) {
      LCDChar (line, i, ' ');
    }
}

/***************************************************************************//**
Function for writing a character to the display at position "line" and "row"
@param line Line where character is written \n
       - @b 1 to @b NUM_LINES.
@param row Row where character is written \n
       - @b 1 to @b NUM_ROWS.
@param ascii Character which is written.
@retval - none
@see NUM_LINES NUM_ROWS in LCDCfg.h
@note For more details see datasheet.
*******************************************************************************/
void LCDChar ( uint8_t line, uint8_t row, char ascii ) {
  if (line>0 && line<(NUM_LINES+1))
    if (row>0 && row<(NUM_ROWS+1)) {
      switch ( line ) {
        case 1 :
           LCDSetAddr (row-1 );
          break;
        case 2 :
           LCDSetAddr (row-1 + 64);
          break;
        case 3 :
           LCDSetAddr (row-1 + NUM_ROWS);
          break;
        case 4 :
           LCDSetAddr (row-1 + 64 + NUM_ROWS);
          break;
        default:
          break;
    }

      switch ( ascii ) {
         case 'ü':
         case 'Ü':
           ascii = (char)0xF5;
           break;
         case 'ä':
         case 'Ä':
           ascii = (char)0xE1;
           break;
         case 'ö':
         case 'Ö':
           ascii = (char)0xEF;
           break;
         case '°':
           ascii = (char)0xDF;
           break;
         default:
           break;
      }
      LCDData (ascii);
    }
}

/***************************************************************************//**
Function for writing a string to the display at position "line" and "row"
@param line Line where character is written \n
       - @b 1 to @b NUM_LINES.
@param row Row where character is written \n
       - @b 1 to @b NUM_ROWS.
@param *str reference to string that is written.
@retval - none
@see NUM_LINES NUM_ROWS LCDCfg.h
@note For more details see datasheet.
*******************************************************************************/
void LCDString ( uint8_t line, uint8_t row, char* str ) {
  uint8_t i = 0;
  while( str[i] != '\0') {    // Ausgabe eines Strings mit Abschlusszeichen \0
    LCDChar ( line, i+row, (int8_t)str[i] );  // Zeichenweise Ausgabe
    i++;
  }
}

/***************************************************************************//**
Function for writing data to CG-Ram
@param adr ram address in the CG-RAM\n
@param data databyte that is sotred in the RAM
@retval - none
*******************************************************************************/
void LCDWriteCgMem (uint8_t adr, uint8_t data) {
  if (adr <= 64) {              /* Gueltiger CG-Bereich ? */
    LCDCtrl ( adr | 0x40 );  // Befehl fuer Schreiben in CG-RAM
    LCDData ( data );
  }
}

/***************************************************************************//**
Function for setting user defined symbols in LCDs CG memory defined in LCDCfg.h
@see LCDCfg.h
@param - none
@retval - none
*******************************************************************************/
void LCDDefSymbol(void) {
/*** Symbol Nr. 0hex ***/
   LCDWriteCgMem ( 0, SYMBOL0_LINE0);
   LCDWriteCgMem ( 1, SYMBOL0_LINE1);
   LCDWriteCgMem ( 2, SYMBOL0_LINE2);
   LCDWriteCgMem ( 3, SYMBOL0_LINE3);
   LCDWriteCgMem ( 4, SYMBOL0_LINE4);
   LCDWriteCgMem ( 5, SYMBOL0_LINE5);
   LCDWriteCgMem ( 6, SYMBOL0_LINE6);
   LCDWriteCgMem ( 7, SYMBOL0_LINE7);
/*** Symbol Nr.1hex ***/
   LCDWriteCgMem ( 8, SYMBOL1_LINE0);
   LCDWriteCgMem ( 9, SYMBOL1_LINE1);
   LCDWriteCgMem (10, SYMBOL1_LINE2);
   LCDWriteCgMem (11, SYMBOL1_LINE3);
   LCDWriteCgMem (12, SYMBOL1_LINE4);
   LCDWriteCgMem (13, SYMBOL1_LINE5);
   LCDWriteCgMem (14, SYMBOL1_LINE6);
   LCDWriteCgMem (15, SYMBOL1_LINE7);
/*** Symbol Nr. 2hex ***/
   LCDWriteCgMem (16, SYMBOL2_LINE0);
   LCDWriteCgMem (17, SYMBOL2_LINE1);
   LCDWriteCgMem (18, SYMBOL2_LINE2);
   LCDWriteCgMem (19, SYMBOL2_LINE3);
   LCDWriteCgMem (20, SYMBOL2_LINE4);
   LCDWriteCgMem (21, SYMBOL2_LINE5);
   LCDWriteCgMem (22, SYMBOL2_LINE6);
   LCDWriteCgMem (23, SYMBOL2_LINE7);
/*** Symbol Nr. 3hex ***/
   LCDWriteCgMem (24, SYMBOL3_LINE0);
   LCDWriteCgMem (25, SYMBOL3_LINE1);
   LCDWriteCgMem (26, SYMBOL3_LINE2);
   LCDWriteCgMem (27, SYMBOL3_LINE3);
   LCDWriteCgMem (28, SYMBOL3_LINE4);
   LCDWriteCgMem (29, SYMBOL3_LINE5);
   LCDWriteCgMem (30, SYMBOL3_LINE6);
   LCDWriteCgMem (31, SYMBOL3_LINE7);
/*** Symbol Nr. 4hex ***/
   LCDWriteCgMem (32, SYMBOL4_LINE0);
   LCDWriteCgMem (33, SYMBOL4_LINE1);
   LCDWriteCgMem (34, SYMBOL4_LINE2);
   LCDWriteCgMem (35, SYMBOL4_LINE3);
   LCDWriteCgMem (36, SYMBOL4_LINE4);
   LCDWriteCgMem (37, SYMBOL4_LINE5);
   LCDWriteCgMem (38, SYMBOL4_LINE6);
   LCDWriteCgMem (39, SYMBOL4_LINE7);
/*** Symbol Nr. 5hex ***/
   LCDWriteCgMem (40, SYMBOL5_LINE0);
   LCDWriteCgMem (41, SYMBOL5_LINE1);
   LCDWriteCgMem (42, SYMBOL5_LINE2);
   LCDWriteCgMem (43, SYMBOL5_LINE3);
   LCDWriteCgMem (44, SYMBOL5_LINE4);
   LCDWriteCgMem (45, SYMBOL5_LINE5);
   LCDWriteCgMem (46, SYMBOL5_LINE6);
   LCDWriteCgMem (47, SYMBOL5_LINE7);
/*** Symbol Nr. 6hex ***/
   LCDWriteCgMem (48, SYMBOL6_LINE0);
   LCDWriteCgMem (49, SYMBOL6_LINE1);
   LCDWriteCgMem (50, SYMBOL6_LINE2);
   LCDWriteCgMem (51, SYMBOL6_LINE3);
   LCDWriteCgMem (52, SYMBOL6_LINE4);
   LCDWriteCgMem (53, SYMBOL6_LINE5);
   LCDWriteCgMem (54, SYMBOL6_LINE6);
   LCDWriteCgMem (55, SYMBOL6_LINE7);
/*** Symbol Nr. 7hex ***/
   LCDWriteCgMem (56, SYMBOL7_LINE0);
   LCDWriteCgMem (57, SYMBOL7_LINE1);
   LCDWriteCgMem (58, SYMBOL7_LINE2);
   LCDWriteCgMem (59, SYMBOL7_LINE3);
   LCDWriteCgMem (60, SYMBOL7_LINE4);
   LCDWriteCgMem (61, SYMBOL7_LINE5);
   LCDWriteCgMem (62, SYMBOL7_LINE6);
   LCDWriteCgMem (63, SYMBOL7_LINE7);
}
/** @}*/
