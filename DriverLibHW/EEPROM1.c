/***************************************************************************//**
Implementation file for the EEPROM module for AVR-ATMEGA controller
*******************************************************************************/
/** @addtogroup EEPROM_api
@{*/
/** @file EEPROM.c Implementation file for ATMELs EEPROM. */

#include <avr/io.h>

#include "EEPROM1.h"

//==================== EEPROM Leseroutine fuer ein Byte ========================
uint8_t EEPROMReadByte ( uint16_t addr ) {
  do {} while( EECR & (1<<EEPE) ); // Wait for completion of previous write.
  EEAR = addr; // Set EEPROM address register.
  EECR = (1<<EERE); // Start EEPROM read operation.
  return EEDR; // Return the byte read from EEPROM.
}
//==================== EEPROM Leseroutine fuer Datenfeld =======================
void EEPROMRead ( uint16_t addr, uint8_t* dst, uint16_t len ) {
  uint16_t i;
  for ( i=0; i<len; i++) {
    *dst = EEPROMReadByte ( addr+i );
    dst++;
  }
}

//==================== EEPROM Schreibroutine fuer ein Byte =====================
void EEPROMWriteByte ( uint16_t addr, uint8_t byte ) {
  do {} while( EECR & (1<<EEPE) ); // Wait for completion of previous write.
  EEAR = addr; // Set EEPROM address register.
  EEDR = byte;
  EECR = (1<<EEMPE); // Set Write Enable bit...
  EECR |= (1<<EEPE);  // Start Erase+Write operation.
}
//==================== EEPROM Schreibroutine fuer Datenfeld ====================
void EEPROMWrite ( uint16_t addr, uint8_t* src, uint16_t len ) {
  uint16_t i;
  for ( i=0; i<len; i++) {
    EEPROMWriteByte ( addr+i, *src );
    src++;
  }
}
/**@}*/
