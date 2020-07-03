#ifndef TIME_H
#define TIME_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif


typedef struct TimeStruct {
   uint8_t sec;
   uint8_t min;
   uint8_t hour;
} TimeStruct;

//void TimeCalcStop       ( TimeStruct* p_time, uint16_t min );
uint32_t TimeGetMinOffset ( TimeStruct* p_time );
uint32_t TimeGetMinDiff ( TimeStruct* p_time_start, TimeStruct* p_time_end);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
