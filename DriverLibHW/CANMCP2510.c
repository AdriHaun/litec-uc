/***************************************************************************//**
Implementation file for the MCP2510 or MCP2515 CAN-Controller

@author LiTec/PAMG
@date 24.06.2007
@version 1.1

@param compiler switches: none
@param linker switches: none

@b History:
- 1.0 LiTec/PAMG 24.06.2007 initial version.
- 1.1 LiTec/PAMG 26.12.2016 8MHz support added for MCP2515, sample point modified
****************************************************************************/
/** @addtogroup CANMCP2510_api
@{*/
/** @file CANMCP2510.C Main source file for a MCP251x CAN-Controller. */
#include "CANMCP2510.h"
#include "Wait.h"

#define CANMCP2510_TIMEOUT_MS 50        // timeout in ms to wait for tx competed

uint8_t ctrl_reg = 0x06; // global copy of CNTRL-Register

/***************************************************************************//**
Function for setting the output-pin on the MCP2510
@param addr number of the output - 0 or 1
@param value value the output should adopt - 0 or 1
@retval - none
*******************************************************************************/
void CANMCP2510SetOutput ( uint8_t addr, uint8_t value ) {
  if ( addr > 1 ) return;
  if ( value ) SPIMCP2510RegBitModify( BFPCTRL, (1<<(2+addr)), (1<<(2+addr)));
  else         SPIMCP2510RegBitModify( BFPCTRL, (1<<(2+addr)), 0);
}

/***************************************************************************//**
Routine for reading the input-pin on the MCP2510
@param addr address of the input-pin - 0 up to 2
@retval readed value (an invalid input address always gives 0)
*******************************************************************************/
uint8_t CANMCP2510GetInput ( uint8_t addr ) {
  if ( addr > 2) return 0;
  return ((SPIMCP2510RegRead ( TXRTSCTRL ) & (1 << (addr + 3))) >> 3);
}

/***************************************************************************//**
Function for initialization of the MCP2510 CAN-Controller
@param baudrate baud rate --> for valid values see CANMCP2510.h
@param txint disable (0) or enable (1) TX-Interrupt
@param rxint disable (0) or enable (1) RX-Interrupt
@param errorint disable (0) or enable (1) ERROR-Interrupt
@retval - none
*******************************************************************************/
void CANMCP2510Init ( uint32_t baudrate, uint8_t txint,
                        uint8_t rxint, uint8_t errorint ) {
  uint8_t sjw, brp, prseg, phseg1, phseg2;
  uint8_t interrupts = 0;

  SPIMCP2510Reset ();                 // after reset CLKOUT = XTAL
  WaitMs (10);
  #if defined (CAN_MCP2515_8MHz)
// write CTRL-Register  CLKEN = 1 and prescaler set to fosc/2
//  7       6       5       4       3       2       1       0
//REQOP2  REQOP1  REQOP0   ABAT     -     CLKEN   CLKPRE1 CLKPRE0
//  0       0       0       0       U       1       0       1
  ctrl_reg = 0x06;
  #else
// write CTRL-Register  CLKEN = 1 and prescaler set to fosc/4
//  7       6       5       4       3       2       1       0
//REQOP2  REQOP1  REQOP0   ABAT     -     CLKEN   CLKPRE1 CLKPRE0
//  0       0       0       0       U       1       1       0
  ctrl_reg = 0x06;
  #endif
  SPIMCP2510RegWrite (CANCTRL, ctrl_reg | 0x80);  // write CTRL and config-mode

 /******************  Calculate Baudrate CAN-Bus****************************
 TQ = 2*(BRP+1)/fOSC
 Bit_Length = TQ*(SYNC+PRSEG+PHSEG1+PHSEG2)

 Baud =  fOSC/(2*(BRP+1)*(1+(PRSEG+1)+(PHSEG1+1)+(PHSEG2+1)))

 rules for synchronization
 PRSEG + PHSEG1 >= PHSEG2
 PHSEG2 >= SJW
 Sample-Point at 60-70% --> see datasheet
 set SJW = 2 for faster resynchronization.
 */
#if defined (CAN_MCP2515_8MHz)
  switch ( baudrate ) {
    case CAN_BAUD_10k : //TQ = 2*(19+1)/8MHz = 5us // not tested with MCP2551, ERROR with TJA1050 (TX-dominant-timeout!!)
     // Baudr. = 8MHz/(2*(19+1)*(1+(7+1)+(7+1)+(2+1))) = 8MHz/(2*20*20) = 8MHz/800 = 10kBps
     sjw = 0; brp = 19; prseg = 7; phseg1 = 7; phseg2 = 2;  // sum = 20 TQ sample at 85,0%
	  break;
    case CAN_BAUD_20k : //TQ = 2*(9+1)/8MHz = 2,5us --> tested with TJA1050+TEMINATION
      // Baudr. = 8MHz/(2*(9+1)*(1+(2+1)+(7+1)+(7+1))) = 8MHz/(2*10*20) = 8MHz/400 = 20kBps
      sjw = 1; brp = 9; prseg = 7; phseg1 = 7; phseg2 = 2;  // sum = 20 TQ sample at 85,0%
      break;
    case CAN_BAUD_50k : //TQ = 2*(3+1)/8MHz = 1us --> tested with TJA1050+TEMINATION
	  // Baudr. = 8MHz/(2*(3+1)*(1+(2+1)+(7+1)+(7+1))) = 8MHz/(2*4*20) = 8MHz/160 = 50kBps
     sjw = 1; brp = 3; prseg = 7; phseg1 = 7; phseg2 = 2;  // sum = 20 TQ sample at 85,0%
      break;
    case CAN_BAUD_100k : //TQ = 2*(1+1)/8MHz = 0,5us --> tested with TJA1050+TEMINATION
     // Baudr. = 8MHz/(2*(1+1)*(1+(7+1)+(7+1)+(2+1))) = 8MHz/(2*2*20) = 8MHz/80 = 100kBps
     sjw = 0; brp = 1; prseg = 7; phseg1 = 7; phseg2 = 2;  // sum = 20 TQ sample at 85,0%
	  break;
    case CAN_BAUD_125k : //TQ = 2*(1+1)/8MHz = 0,5us --> tested with TJA1050+TEMINATION
     // Baudr. = 8MHz/(2*(1+1)*(1+(4+1)+(7+1)+(1+1))) = 8MHz/(2*2*16) = 8MHz/64 = 125kBps
     sjw = 0; brp = 1; prseg = 4; phseg1 = 7; phseg2 = 1;  // sum = 16 TQ sample at 87,5%
	  break;
    case CAN_BAUD_250k : //TQ = 2*(0+1)/8MHz = 0,25us // works with TJA1050+TEMINATION
      // Baudr. = 16MHz/(2*(0+1)*(1+(4+1)+(7+1)+(1+1))) = 16MHz/(2*1*16) = 8MHz/32 = 250kBps
      sjw = 0; brp = 0; prseg = 4; phseg1 = 7; phseg2 = 1;  // sum = 16 TQ sample at 87,5%
      break;
    case CAN_BAUD_500k : //TQ = 2*(0+1)/8MHz = 0,25us // works with TJA1050+TEMINATION
    default:
      // Baudr. = 8MHz/(2*(0+1)*(1+(1+1)+(2+1)+(1+1))) = 8MHz/(2*1*8) = 8MHz/16 = 500kBps
      sjw = 1; brp = 0; prseg = 1; phseg1 = 2; phseg2 = 1;  // sum = 8 TQ sample at 75,0%
	   break;
  }
#else                                   // 16MHz
  switch ( baudrate ) {
    case CAN_BAUD_10k : //TQ = 2*(39+1)/8MHz = 5us // not tested with MCP2551, ERROR with TJA1050 (TX-dominant-timeout!!)
      // Baudr. = 16MHz/(2*(39+1)*(1+(7+1)+(7+1)+(2+1))) = 16MHz/(2*40*20) = 16MHz/1600= 10kBps
      sjw = 0; brp = 39; prseg = 7; phseg1 = 7; phseg2 = 2;  // sum = 20 TQ sample at 85,0%
      break;
    case CAN_BAUD_20k : //TQ = 2*(19+1)/16MHz = 2,5us // works with TJA1050
      // Baudr. = 16MHz/(2*(19+1)*(1+(7+1)+(7+1)+(2+1))) = 16MHz/(2*20*20) = 16MHz/800 = 20kBps
      sjw = 1; brp = 19; prseg = 7; phseg1 = 7; phseg2 = 2;  // sum = 20 TQ
      break;
    case CAN_BAUD_50k : //TQ = 2*(7+1)/16MHz = 1us --> tested with TJA1050+TEMINATION
      // Baudr. = 16MHz/(2*(7+1)*(1+(7+1)+(7+1)+(2+1))) = 16MHz/(2*8*20) = 16MHz/320 = 50kBps
      sjw = 1; brp = 7; prseg = 7; phseg1 = 7; phseg2 = 2;  // sum = 20 TQ sample at 85,0%
      break;
    case CAN_BAUD_100k : //TQ = 2*(3+1)/16MHz = 0,5us --> tested with TJA1050+TEMINATION
      // Baudr. = 16MHz/(2*(3+1)*(1+(7+1)+(7+1)+(2+1))) = 16MHz/(2*4*20) = 16MHz/160 = 100kBps
     sjw = 0; brp = 3; prseg = 7; phseg1 = 7; phseg2 = 2;  // sum = 20 TQ sample at 85,0%
	  break;
    case CAN_BAUD_125k : //TQ = 2*(3+1)/16MHz = 0,5us --> tested with TJA1050+TEMINATION
     // Baudr. = 16MHz/(2*(3+1)*(1+(4+1)+(7+1)+(1+1))) = 16MHz/(2*4*16) = 16MHz/128 = 125kBps
     sjw = 0; brp = 3; prseg = 4; phseg1 = 7; phseg2 = 1;  // sum = 16 TQ sample at 87,5%
	  break;
    case CAN_BAUD_250k : //TQ = 2*(1+1)/16MHz = 0,25us // works with TJA1050+TEMINATION
      // Baudr. = 16MHz/(2*(1+1)*(1+(0+1)+(7+1)+(5+1))) = 16MHz/(2*2*16) = 16MHz/64 = 250kBps
      sjw = 0; brp = 1; prseg = 4; phseg1 = 7; phseg2 = 1;  // sum = 16 TQ sample at 87,5%
      break;
    case CAN_BAUD_500k : //TQ = 2*(0+1)/16MHz = 0,125us // works with TJA1050+TEMINATION
      // Baudr. = 16MHz/(2*(0+1)*(1+(4+1)+(7+1)+(1+1))) = 16MHz/(2*1*16) = 16MHz/32 = 500kBps
      sjw = 1; brp = 0; prseg = 4; phseg1 = 7; phseg2 = 1;  // sum = 16 TQ sample at 87,5%
      break;
    case CAN_BAUD_1M :
    default: //TQ = 2*(0+1)/16MHz = 0,125us // works with TJA1050+TEMINATION
      // Baudr. = 16MHz/(2*(0+1)*(1+(1+1)+(2+1)+(1+1))) = 16MHz/(2*1*8) = 16MHz/16 = 1MBps
      sjw = 1; brp = 0; prseg = 1; phseg1 = 2; phseg2 = 1;  // sum = 8 TQ sample at 75%
      break;
   }
#endif

   SPIMCP2510RegWrite( CNF1, (sjw<<6) | brp );  // write SJW and BRP
   SPIMCP2510RegWrite( CNF2, 0x80|(phseg1<<3)|prseg );  // write BTLMODE = 1, PHSEG1 und PRSEG
   SPIMCP2510RegWrite( CNF3, 0x80 | phseg2 );  // write PHSEG2, wake-up filter disabled


   if ( txint    ) interrupts |= 0x1C; // enable tx-interrupt
   if ( rxint    ) interrupts |= 0x03; // enable rx-interrupt
   if ( errorint ) interrupts |= 0x20; // enable error-interrupt
   SPIMCP2510RegWrite( CANINTE, interrupts );

// define IO-lines: RX-ctrl-reg --> Pin as output
//  7       6       5       4       3       2       1       0
//  -       -     B1BFS   B0BFS   B1BFE   B0BFE   B1BFM   B0BFM
//  U       U       0       0       0       0       0       0
  SPIMCP2510RegWrite (BFPCTRL, 0x00);

// define IO-lines: TX-state-reg. --> Pin as input
//  7       6       5       4       3       2       1       0
//  -       -     B2RTS   B1RTS   B0RTS   B2RTSM  B1RTSM  B0RTSM
//  U       U       R       R       R       0       0       0
  SPIMCP2510RegWrite (TXRTSCTRL, 0x00);
  SPIMCP2510RegWrite (CANCTRL, ctrl_reg & (~0x80));  // set CTRL-reg normal mode
}

/***************************************************************************//**
Function for configuration of the RX-buffers
@param rx_buf_nr number of the RX buffer (0 or 1)
@param mask mask for configuration see datasheet
@retval - none
*******************************************************************************/
void CANMCP2510ConfigRxMask ( uint8_t rx_buf_nr, uint16_t mask ) {

  SPIMCP2510RegWrite (CANCTRL, ctrl_reg | 0x80); // write CTRL and config-mode

  // Akzeptanzfilter einstellen
  if ( rx_buf_nr ) {                    // buffer 1 receive all messages
    SPIMCP2510RegWrite( RXB1CTRL, 0x60 );
    SPIMCP2510RegWrite( RXM1SIDH, (uint8_t) ((mask & 0xFF00)>> 8) );
    SPIMCP2510RegWrite( RXM1SIDL, (uint8_t) (mask & 0x00FF) );
    SPIMCP2510RegWrite( RXM1EID8, 0x00 );
    SPIMCP2510RegWrite( RXM1EID0, 0x00 );
  } else {                              // buffer 0 receive all messages
    SPIMCP2510RegWrite( RXB0CTRL, 0x60 );
    SPIMCP2510RegWrite( RXM0SIDH, (uint8_t) ((mask & 0xFF00)>> 8) );
    SPIMCP2510RegWrite( RXM0SIDL, (uint8_t) (mask & 0x00FF) );
    SPIMCP2510RegWrite( RXM0EID8, 0x00 );
    SPIMCP2510RegWrite( RXM0EID0, 0x00 );
  }
  SPIMCP2510RegWrite (CANCTRL, ctrl_reg & (~0x80)); // set CTRL-reg normal mode
}

/***************************************************************************//**
Function for writing a message to the CAN-bus
@param msg_id standard CAN msg ID
@param tx_buf_nr number of the TX buffer - 0 up to 2
@param src pointer to the source of the msg
@param len length of the msg (without ID) == DLC
@retval - none
*******************************************************************************/
void CANMCP2510MsgWr ( uint16_t msg_id, uint8_t tx_buf_nr,
                          uint8_t *src, uint8_t len) {
  uint8_t buf_base_addr = TXB0SIDH;
  uint8_t wait_time_out = 0x00;
  uint8_t i;

  switch ( tx_buf_nr ) {
    case 1 :
      buf_base_addr = TXB1CTRL;
      break;
    case 2 :
      buf_base_addr = TXB2CTRL;
      break;
    default:
      buf_base_addr = TXB0CTRL;
      tx_buf_nr = 0;
      break;
  }
  SPIMCP2510Sync ();
  do {
    WaitMs (1);
    wait_time_out++;
  } while ( (SPIMCP2510RegRead (buf_base_addr) & 0x08) &&
            (wait_time_out < CANMCP2510_TIMEOUT_MS) );

  if (wait_time_out == CANMCP2510_TIMEOUT_MS) return;

  SPIMCP2510RegWrite (buf_base_addr+1, (uint8_t) (msg_id>>3));  // set ID
  SPIMCP2510RegWrite (buf_base_addr+2, (uint8_t) (msg_id<<5));  // set ID

  SPIMCP2510RegWrite (buf_base_addr+5, len);  // set data length

  if ( len > 8 ) len = 8;               // cut invalid lengths
  for ( i=0; i<len; i++, src++) {
    SPIMCP2510RegWrite (buf_base_addr+6+i, *src);  // copy message
  }

  SPIMCP2510RTS (tx_buf_nr);
}

/***************************************************************************//**
Function for reading a message from the RX-buffer
@param rx_buf_nr number of the RX buffer - 0 or 1
@param dest pointer to the destination where msg is copied to
@param dlc pointer to the length of the msg (without ID) == DLC
@retval - none
*******************************************************************************/
void CANMCP2510MsgRd (uint8_t rx_buf_nr, uint8_t *dest, uint8_t *dlc) {

  uint8_t buf_addr = RXB0SIDH;
  uint8_t i;

  if ( rx_buf_nr > 0) buf_addr = RXB1SIDH;

  dest[0] = SPIMCP2510RegRead(buf_addr);  // whole message (ID + DLC + Data)
  dest[1] = SPIMCP2510RegRead(buf_addr+1);
  dest[2] = SPIMCP2510RegRead(buf_addr+4);
  *dlc=(dest[2]&0x0F);   // Msg Cfg -> DLC
  if ( *dlc > 8 ) *dlc = 8;
  for ( i=0; i<*dlc; i++) {
    dest[3+i]=SPIMCP2510RegRead(buf_addr+5+i);   // read data bytes
  }
}

/***************************************************************************//**
Service routine to be called by an external ISR for servicing the interrupt
@param can_state_reg destination for saving the CAN status register
@param int_flag_reg destination for saving the interrupt flag register
@param error_flag_reg destination for saving the error flag register
@param msg pointer to the destination of the msg (ID+DLC+Data ID!!)
@param msg_len length of the msg (without ID) == DLC
@retval - none
*******************************************************************************/
 void CANMCP2510InterruptService (uint8_t* can_state_reg, uint8_t* int_flag_reg,
                            uint8_t* error_flag_reg, uint8_t* msg, uint8_t* msg_len) {

  *can_state_reg = SPIMCP2510RegRead (CANSTAT);  // read Status-Reg.
  *int_flag_reg =  SPIMCP2510RegRead (CANINTF);  // read Int-Flag lesen
  SPIMCP2510RegWrite (CANINTF, 0x00);            // quit. all Ints.

  *error_flag_reg = SPIMCP2510RegRead (EFLG);    // read Error-Flag

  // at RX-Buffer-Overflow quit errors:
  if ( (*error_flag_reg & 0xC0) > 0 ) SPIMCP2510RegWrite (EFLG, 0x00);

  // read message if an RX-Interrupt occured
  // read Buffer 0 with highest priority
  if ( *int_flag_reg & 0x01 )             CANMCP2510MsgRd (0, msg, msg_len);
  else if ( (*int_flag_reg & 0x02) >> 1 ) CANMCP2510MsgRd (1, msg, msg_len);
  else                                    *msg_len = 0;
}
/**@}*/
