/***************************************************************************//**
Configuration file for a MCP251x CAN-Controller.

@note Copy the file CANMCP2510Cfg.h to your local project folder and edit
      the configuration
*******************************************************************************/
/** @addtogroup CANMCP2510_api
@{*/
/** @file CANMCP2510Cfg.h Configuration file for a MCP251x CAN-Controller. */
#ifndef  CANMCP2510CFG_H

// defines for can-controller registers
#define CANCTRL  0x0F                   // Ctrl Register
#define CANSTAT  0x0E                   // State Register

#define TXRTSCTRL 0x0D                  // TX Pin Control and Status Register
#define BFPCTRL   0x0C                  // RX Pin Control and Status Register

#define CNF3      0x28                  // Configuration Register 3
#define CNF2      0x29                  // Configuration Register 2
#define CNF1      0x2A                  // Configuration Register 1
#define CANINTE   0x2B                  // Interrupt Enable Register
#define CANINTF   0x2C                  // Interrupt Flag Register
#define EFLG      0x2D                  // Error Flag Register
#define TEC       0x1C                  // Transmitter Error Counter
#define REC       0x1D                  // Receiver Error Counter

// TX-Buffer 0
#define TXB0CTRL  0x30                  // TX-Buffer 0 Control and Status
#define TXB0SIDH  0x31                  // TX-Buffer 0 Std. Identifier High
#define TXB0SIDL  0x32                  // TX-Buffer 0 Std. Identifier Low
#define TXB0EID8  0x33                  // TX-Buffer 0 Ext. Identifier High
#define TXB0EID0  0x34                  // TX-Buffer 0 Ext. Identifier Low
#define TXB0DLC   0x35                  // TX-Buffer 0 Data Length Code
#define TXB0D0    0x36                  // TX-Buffer 0 Data Field Byte 0
#define TXB0D1		0x37
#define TXB0D2		0x38
#define TXB0D3    0x39                  // ......
#define TXB0D4		0x3A
#define TXB0D5		0x3B
#define TXB0D6		0x3C
#define TXB0D7    0x3D                  // TX-Buffer 0 Data Field Byte 7

// TX-Buffer 1
#define TXB1CTRL  0x40                  // TX-Buffer 1 Control and Status
#define TXB1SIDH  0x41                  // TX-Buffer 1 Std. Identifier High
#define TXB1SIDL  0x42                  // TX-Buffer 1 Std. Identifier Low
#define TXB1EID8  0x43                  // TX-Buffer 1 Ext. Identifier High
#define TXB1EID0  0x44                  // TX-Buffer 1 Ext. Identifier Low
#define TXB1DLC   0x45                  // TX-Buffer 1 Data Length Code
#define TXB1D0    0x46                  // TX-Buffer 1 Data Field Byte 0
#define TXB1D1		0x47
#define TXB1D2		0x48
#define TXB1D3    0x49                  // ......
#define TXB1D4		0x4A
#define TXB1D5		0x4B
#define TXB1D6		0x4C
#define TXB1D7    0x4D                  // TX-Buffer 1 Data Field Byte 7

// TX-Buffer 2
#define TXB2CTRL  0x50                  // TX-Buffer 2 Control and Status
#define TXB2SIDH  0x51                  // TX-Buffer 2 Std. Identifier High
#define TXB2SIDL  0x52                  // TX-Buffer 2 Std. Identifier Low
#define TXB2EID8  0x53                  // TX-Buffer 2 Ext. Identifier High
#define TXB2EID0  0x54                  // TX-Buffer 2 Ext. Identifier Low
#define TXB2DLC   0x55                  // TX-Buffer 2 Data Length Code
#define TXB2D0    0x56                  // TX-Buffer 2 Data Field Byte 0
#define TXB2D1		0x57
#define TXB2D2		0x58
#define TXB2D3    0x59                  // ......
#define TXB2D4		0x5A
#define TXB2D5		0x5B
#define TXB2D6		0x5C
#define TXB2D7    0x5D                  // TX-Buffer 2 Data Field Byte 7

// RX-Buffer 0
#define RXB0CTRL  0x60                  // RX-Buffer 0 Control and Status
#define RXB0SIDH  0x61                  // RX-Buffer 0 Std. Identifier High
#define RXB0SIDL  0x62                  // RX-Buffer 0 Std. Identifier Low
#define RXB0EID8  0x63                  // RX-Buffer 0 Ext. Identifier High
#define RXB0EID0  0x64                  // RX-Buffer 0 Ext. Identifier Low
#define RXB0DLC   0x65                  // RX-Buffer 0 Data Length Code
#define RXB0D0    0x66                  // RX-Buffer 0 Data Field Byte 0
#define RXB0D1		0x67
#define RXB0D2		0x68
#define RXB0D3    0x69                  // ......
#define RXB0D4		0x6A
#define RXB0D5		0x6B
#define RXB0D6		0x6C
#define RXB0D7    0x6D                  // RX-Buffer 0 Data Field Byte 7

// RX-Buffer 1
#define RXB1CTRL  0x70                  // RX-Buffer 1 Control and Status
#define RXB1SIDH  0x71                  // RX-Buffer 1 Std. Identifier High
#define RXB1SIDL  0x72                  // RX-Buffer 1 Std. Identifier Low
#define RXB1EID8  0x73                  // RX-Buffer 1 Ext. Identifier High
#define RXB1EID0  0x74                  // RX-Buffer 1 Ext. Identifier Low
#define RXB1DLC   0x75                  // RX-Buffer 1 Data Length Code
#define RXB1D0    0x76                  // RX-Buffer 1 Data Field Byte 0
#define RXB1D1		0x77
#define RXB1D2		0x78
#define RXB1D3    0x79                  // ......
#define RXB1D4		0x7A
#define RXB1D5		0x7B
#define RXB1D6		0x7C
#define RXB1D7    0x7D                  // RX-Buffer 1 Data Field Byte 7

// Acceptance Filters
#define RXF0SIDH  0x00                  // Acceptance Filter 0 Std. ID. High
#define RXF0SIDL  0x01                  // Acceptance Filter 0 Std. ID. Low
#define RXF0EID8  0x02                  // Acceptance Filter 0 Ext. ID. High
#define RXF0EID0  0x03                  // Acceptance Filter 0 Ext. ID. Low
#define RXF1SIDH  0x04                  // Acceptance Filter 1 Std. ID. High
#define RXF1SIDL  0x05                  // Acceptance Filter 1 Std. ID. Low
#define RXF1EID8  0x06                  // Acceptance Filter 1 Ext. ID. High
#define RXF1EID0  0x07                  // Acceptance Filter 1 Ext. ID. Low
#define RXF2SIDH  0x08                  // Acceptance Filter 2 Std. ID. High
#define RXF2SIDL  0x09                  // Acceptance Filter 2 Std. ID. Low
#define RXF2EID8  0x0A                  // Acceptance Filter 2 Ext. ID. High
#define RXF2EID0  0x0B                  // Acceptance Filter 2 Ext. ID. Low
#define RXF3SIDH  0x10                  // Acceptance Filter 3 Std. ID. High
#define RXF3SIDL  0x11                  // Acceptance Filter 3 Std. ID. Low
#define RXF3EID8  0x12                  // Acceptance Filter 3 Ext. ID. High
#define RXF3EID0  0x13                  // Acceptance Filter 3 Ext. ID. Low
#define RXF4SIDH  0x14                  // Acceptance Filter 4 Std. ID. High
#define RXF4SIDL  0x15                  // Acceptance Filter 4 Std. ID. Low
#define RXF4EID8  0x16                  // Acceptance Filter 4 Ext. ID. High
#define RXF4EID0  0x17                  // Acceptance Filter 4 Ext. ID. Low
#define RXF5SIDH  0x18                  // Acceptance Filter 5 Std. ID. High
#define RXF5SIDL  0x19                  // Acceptance Filter 5 Std. ID. Low
#define RXF5EID8  0x1A                  // Acceptance Filter 5 Ext. ID. High
#define RXF5EID0  0x1B                  // Acceptance Filter 5 Ext. ID. Low

// Acceptance Filter Mask
#define RXM0SIDH  0x20                  // Acceptance Filter Mask 0 Std. ID. High
#define RXM0SIDL  0x21                  // Acceptance Filter Mask 0 Std. ID. Low
#define RXM0EID8  0x22                  // Acceptance Filter Mask 0 Ext. ID. High
#define RXM0EID0  0x23                  // Acceptance Filter Mask 0 Ext. ID. Low
#define RXM1SIDH  0x24                  // Acceptance Filter Mask 1 Std. ID. High
#define RXM1SIDL  0x25                  // Acceptance Filter Mask 1 Std. ID. Low
#define RXM1EID8  0x26                  // Acceptance Filter Mask 1 Ext. ID. High
#define RXM1EID0  0x27                  // Acceptance Filter Mask 1 Ext. ID. Low

#endif   // CANMCP2515Cfg_H
/**@}*/
