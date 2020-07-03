// Modul zur Ansteuerung eines LCD-Displays mit dem Hitachi HD44780 Controller
// Ansteuerung mit einer 4 BIT-Datenschnittstelle ueber I2C-Bus
//
// Günther Pammer
// LITEC 2003
//
// Schnittstellenbeschreibung siehe LCD.H

#include <util/delay.h>
#include "I2CLCD.h"
#include "I2CPCF8574.h"
#include "Wait.h"

/*=============== WARTE - Funktion ====================*/

uint8_t backlight = BACKLIGHT;         // gilt fuer alle Anzeigen !!!!!!!!!1

void warte( int msec ) {
  WaitMs(msec);

}
void busy_lcd(void){
  WaitMs (1);
  return;
}

// schreibt ein Datenwort an das LCD-Display
void I2CLCDData ( uint8_t i2c_adr,  uint8_t dat ) {
// schreibt HIGH Nibble der Daten
  busy_lcd ();
  I2CPCF8574WritePort (i2c_adr, ((dat&0xF0) | EN | RS | backlight));    /* setzt EN-Bit   */
  I2CPCF8574WritePort (i2c_adr, (((dat&0xF0) & ~EN) | RS | backlight));   /* loescht EN-Bit */
// schreibt LOW Nibble der Daten
  busy_lcd ();
  I2CPCF8574WritePort (i2c_adr, ((dat<<4) | EN | RS | backlight));    /* setzt EN-Bit   */
  I2CPCF8574WritePort (i2c_adr, (((dat<<4) & ~EN) | RS | backlight));   /* loescht EN-Bit */
}
// schreibt ein Steuerwort an das LCD-Display
void I2CLCDCtrl ( uint8_t i2c_adr, uint8_t ctrl ) {
// schreibt HIGH Nibble der Daten
  busy_lcd ();
  I2CPCF8574WritePort (i2c_adr, ((((ctrl&0xF0) | EN) & ~RS) | backlight));    /* setzt EN-Bit   */
  I2CPCF8574WritePort (i2c_adr, ((((ctrl&0xF0) & ~EN) & ~RS) | backlight));   /* loescht EN-Bit */
// schreibt LOW Nibble der Daten
  busy_lcd ();
  I2CPCF8574WritePort (i2c_adr, ((((ctrl<<4) | EN) & ~RS) | backlight));    /* setzt EN-Bit   */
  I2CPCF8574WritePort (i2c_adr, ((((ctrl<<4) & ~EN) & ~RS) | backlight));   /* loescht EN-Bit */
}
void I2CLCDctrl_high_nibble ( uint8_t i2c_adr, uint8_t ctrl ) {
// schreibt HIGH Nibble der Daten
  I2CPCF8574WritePort (i2c_adr, ((((ctrl&0xF0) | EN) & ~RS) | backlight));    /* setzt EN-Bit   */
  I2CPCF8574WritePort (i2c_adr, ((((ctrl&0xF0) & ~EN) & ~RS) | backlight));   /* loescht EN-Bit */
}
// schreibt ein Steuerwort an das LCD-Display zur Cursorpositionierung
void I2CLCDSetAdr (uint8_t i2c_adr, uint8_t adr) {
  I2CLCDCtrl ( i2c_adr, adr |= 0x80 );
}

void I2CLCDClearLine (uint8_t i2c_adr, uint8_t zeile) {
  uint8_t i;
    for ( i=0; i<NUM_ROWS+1; i++) {
      I2CLCDChar (i2c_adr, zeile, i, ' ');
    }
}


void I2CLCDInit ( uint8_t i2c_adr ) {
  WaitMs (500);

  I2CLCDctrl_high_nibble (i2c_adr, 0x30); /*func set: interface is 8 bit long*/
  WaitMs (5);
  I2CLCDctrl_high_nibble (i2c_adr, 0x30); /*func set: interface is 8 bit long*/
  WaitMs (1);
  I2CLCDctrl_high_nibble (i2c_adr, 0x30); /*func set: interface is 8 bit long*/
  WaitMs (1);
  I2CLCDctrl_high_nibble (i2c_adr, 0x20); /*func set: interface is 4 bit long*/
  WaitMs (1);

  I2CLCDctrl_high_nibble (i2c_adr, 0x20); /*func set: interface is 4 bit long*/
  WaitMs (1);
  I2CLCDctrl_high_nibble (i2c_adr, 0x80); /* number of display lines is 2    */
  WaitMs (1);

  I2CLCDctrl_high_nibble (i2c_adr, 0x00);
  busy_lcd ();
  I2CLCDctrl_high_nibble (i2c_adr, 0x80);      /* display off;*/
  busy_lcd ();

  I2CLCDctrl_high_nibble (i2c_adr, 0x00);
  busy_lcd ();
  I2CLCDctrl_high_nibble (i2c_adr, 0x10);      /* display on; and Cursor without BLINK*/
  busy_lcd ();

  I2CLCDctrl_high_nibble (i2c_adr, 0x00);
  busy_lcd ();
  I2CLCDctrl_high_nibble (i2c_adr, 0x60); /* entry mode: increment, no shift */
  busy_lcd ();

  I2CLCDBacklight (0);                  // Backlight OFF
  }
  
  void I2CLCDBacklight (uint8_t on_off) {
    if (on_off == 0) backlight = 0x00;
    else             backlight = BACKLIGHT;
  }

// loescht das LCD-Display
void I2CLCDClear ( uint8_t i2c_adr ) {
  I2CLCDctrl_high_nibble (i2c_adr, 0x00);
  busy_lcd ();

  I2CLCDctrl_high_nibble (i2c_adr, 0x10); /* clear Display */
  busy_lcd ();

  I2CLCDctrl_high_nibble (i2c_adr, 0x00);
  busy_lcd ();

  I2CLCDctrl_high_nibble (i2c_adr, 0xC0); /* Display ON, Cursor OFF, Blink OFF*/
  busy_lcd ();
}

 // schreibt ein ASCII-Zeichen an eine durch "zeile" und "spalte"
// festgelegte Position am LCD-Display
void I2CLCDChar ( uint8_t i2c_adr, uint8_t zeile, uint8_t spalte,
                    char ascii ) {
  if (zeile>0 && zeile<(NUM_LINES+1))
    if (spalte>0 && spalte<(NUM_ROWS+1)) {
		switch ( zeile ) {
			case 1 :
           I2CLCDSetAdr (i2c_adr, spalte-1 );
			  break;
			case 2 :
           I2CLCDSetAdr (i2c_adr, spalte-1 + 64);
			  break;
			case 3 :
           I2CLCDSetAdr (i2c_adr, spalte-1 + NUM_ROWS);
			  break;
			case 4 :
           I2CLCDSetAdr (i2c_adr, spalte-1 + 64 + NUM_ROWS);
			  break;
			default:
			  break;
		}
      switch ( ascii ) {
        case 'ü':
        case 'Ü':
          ascii = 0xF5;
          break;
        case 'ä':
        case 'Ä':
          ascii = 0xE1;
          break;
        case 'ö':
        case 'Ö':
          ascii = 0xEF;
          break;
        case '°':
          ascii = 0xDF;
          break;
        default:
          break;
      }

      I2CLCDData (i2c_adr, ascii);
    }
}

// schreibt einen STRING ab eine durch "zeile" und "spalte"
// festgelegte Position am LCD-Display
void I2CLCDString ( uint8_t i2c_adr, uint8_t zeile, uint8_t spalte,
                      char* str ) {
  int i = 0;
  while( (str[i] != '\0') && (spalte+i < NUM_ROWS+1)) {   // Ausgabe eines Strings mit Abschlusszeichen \0
                                                     // aber nur SPALTEN-Anzahl!
    I2CLCDChar ( i2c_adr, zeile, i+spalte, (char)str[i] );  // Zeichenweise Ausgabe
    i++;
  }
}



