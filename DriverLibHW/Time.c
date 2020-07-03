
#include "Time.h"

//void TimeCalcEnd( TimeStruct* p_time_start, uint16_t min ) {

//} // void TimeCalcEnd( DateStruct* p_time_start, uint16_t min )


uint32_t TimeGetMinOffset ( TimeStruct* p_time ) {
  return (uint32_t)(p_time->min) + (uint32_t)(p_time->hour)*60;
}

uint32_t TimeGetMinDiff ( TimeStruct* p_time_start, TimeStruct* p_time_end) {
  if ( (p_time_start->hour > p_time_end->hour) ||
       ((p_time_start->hour == p_time_end->hour) && ((p_time_start->min >= p_time_end->min) )) ) {
    return (uint32_t)0;
  } else {
    return ( (uint32_t)(p_time_start->hour - p_time_end->hour)*60 + 
             (uint32_t)( (int16_t)p_time_end->min - (int16_t)p_time_start->min) );
  }
} // uint32_t TimeGetMinDiff ( TimeStruct* p_time_start, TimeStruct* p_time_end)
