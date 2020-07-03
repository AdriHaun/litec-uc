// Modul zur Ansteuerung eines LCD-Displays mit dem Hitachi HD44780 Controller
// Ansteuerung mit einer 4 BIT-Datenschnittstelle
//
// Günther Pammer
// LITEC 2003
//
// Zielhardware: siehe Datei I2CLCDCfg.h
#ifndef _I2C_LCD_H
#define _I2C_LCD_H

#include "I2CMaster.h"
#include "I2CLCDCfg.h"

//void warte (int msec);

void I2CLCDInit    ( uint8_t i2c_adr );                        /* Initialisierung */
void I2CLCDData    ( uint8_t i2c_adr, uint8_t dat );                     /* Datenwort an LCD  */
void I2CLCDCtrl    ( uint8_t i2c_adr, uint8_t ctrl );                    /* Steuerwort an LCD */
void I2CLCDClear   ( uint8_t i2c_adr );                            /* Loesche LCD */
void I2CLCDClearLine (uint8_t i2c_adr, uint8_t zeile);
void I2CLCDChar    ( uint8_t i2c_adr, uint8_t zeile, uint8_t spalte, char ascii );   /* ASCII-Zeichen */
void I2CLCDString  ( uint8_t i2c_adr, uint8_t zeile, uint8_t spalte, char* str );  /* schreibt STRING */
void I2CLCDSetAdr ( uint8_t i2c_adr, uint8_t adr);

void I2CLCDBacklight (uint8_t on_off);
#endif
