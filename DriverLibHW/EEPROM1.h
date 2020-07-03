/***************************************************************************//**
Interface file for the EEPROM module for AVR-ATMEGA controller
*******************************************************************************/
/** @addtogroup EEPROM_api
@{*/
/** @file EEPROM.h Interface file for ATMELs EEPROM. */
#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>
#ifdef __cplusplus
extern "C"{
#endif

//==================== EEPROM Leseroutine fuer ein Byte ========================
uint8_t EEPROMReadByte( uint16_t addr );
//==================== EEPROM Leseroutine fuer Datenfeld =======================
void EEPROMRead ( uint16_t addr, uint8_t* dst, uint16_t len );

//==================== EEPROM Schreibroutine fuer ein Byte =====================
void EEPROMWriteByte( uint16_t addr, uint8_t byte );
//==================== EEPROM Schreibroutine fuer Datenfeld ====================
void EEPROMWrite ( uint16_t addr, uint8_t* src, uint16_t len );

#ifdef __cplusplus
} // extern "C"
#endif

#endif // EEPROM_H
/**@}*/
