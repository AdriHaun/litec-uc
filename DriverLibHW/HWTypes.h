/***************************************************************************//**
Definitions and typedefs for hardware dependent symbols
*******************************************************************************/
/** @file HWTypes.h Definition file for HW-defines and HW-types. */
#ifndef __HW_TYPES_H__
#define __HW_TYPES_H__

//*****************************************************************************
// Define a boolean type, and values for true and false.
//*****************************************************************************
typedef unsigned char BOOL;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

//*****************************************************************************
// Define other types
//*****************************************************************************
// unsigned types see #include stdint.h

// signed types  see #include stdint.h

// character
typedef char               CHAR;
#endif // __HW_TYPES_H__
