/***************************************************************************//**
Definitions for AMTEL AVR-timer
*******************************************************************************/
/** @addtogroup TIMER_api
@{*/
/** @file HWTimer.h Definition file for timers. */
#ifndef __HW_TIMER_H__
#define __HW_TIMER_H__

//*****************************************************************************
// The following constants are defines for the Timer Module
//*****************************************************************************
#define TIMER_0      0
#define TIMER_1      1
#define TIMER_2      2
#define TIMER_3      3
#define TIMER_4      4
#define TIMER_5      5

//*****************************************************************************
// The following constants are defines for the Timer Mode
// For more information see Datasheets for ATMEL ATMEGA 2560 TCCRnA
// The n is for the Timer
// In this program the Timer Modes Normal and FAST_PWM_8_Bit are the only one
// which are fully implemented
//*****************************************************************************
#define TIMER_MODE0_NORMAL                  0x00
#define TIMER_MODE1_PWM_8BIT                0x01
#define TIMER_MODE2_PWM_9BIT                0x02
#define TIMER_MODE3_PWM_10BIT               0x03
#define TIMER_MODE4_CTC                     0x04
#define TIMER_MODE5_FAST_PWM_8BIT           0x05
#define TIMER_MODE6_FAST_PWM_9BIT           0x06
#define TIMER_MODE7_FAST_PWM_10BIT          0x07

#define TIMER_MODE8_PWM_PF_CORRECT          0x08
#define TIMER_MODE9_PWM_PF_CORRECT          0x09

#define TIMER_MODE10_PWM_PHASE_CORRECT      0x0A
#define TIMER_MODE11_PWM_PHASE_CORRECT      0x0B
#define TIMER_MODE12_CTC                    0x0C
#define TIMER_MODE14_FAST_PWM_ICR           0x0E
#define TIMER_MODE15_FAST_PWM_OCR           0x0F

//*****************************************************************************
// The following constants are defines for the Prescale-Factor
// For more information see Datasheets for ATMEL ATMEGA 2560 TCCRnA
// The n is for the Timer
//*****************************************************************************
#define PRE_NO_CLK                         0x00
#define PRE_DIV_1                          0x01
#define PRE_DIV_8                          0x02
#define PRE_DIV_64                         0x03
#define PRE_DIV_256                        0x04
#define PRE_DIV_1024                       0x05
#define PRE_FALLING_EDGE                   0x06
#define PRE_RISING_EDGE                    0x07

#endif // __HW_TIMER_H__
/**@}*/
