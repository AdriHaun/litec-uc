/***************************************************************************//**
Interface file for the I2C master library using hardware TWI interface.
*******************************************************************************/
/** @addtogroup I2CMaster_api
@{*/
/** @file I2CMaster.h Interface file for the I2C master library using hardware TWI interface. */

#ifndef _I2C_MASTER_H
#define _I2C_MASTER_H   1

#include <avr/io.h>
#include <stdint.h>

/** defines the data direction (reading from I2C device) in I2C_Master_start(),I2C_Master_rep_start() */
#define I2C_READ    1

/** defines the data direction (writing to I2C device) in I2C_Master_start(),I2C_Master_rep_start() */
#define I2C_WRITE   0

extern void I2CMasterInit ( uint32_t scl_clk );
extern void I2CMasterStop ( void );
extern uint8_t I2CMasterStart ( uint8_t addr );
extern uint8_t I2CMasterRepStart ( uint8_t addr );
extern void I2CMasterStartWait ( uint8_t addr );
extern uint8_t I2CMasterWrite ( uint8_t data );
extern uint8_t I2CMasterReadAck ( void );
extern uint8_t I2CMasterReadNak ( void );

extern uint8_t I2CMasterRead ( uint8_t ack );
#define I2CMasterRead(ack)  (ack) ? I2CMasterReadAck() : I2CMasterReadNak();

void I2CMasterEnable ( void );
void I2CMasterDisable ( void );

#endif
/**@}*/
