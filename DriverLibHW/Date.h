
#ifndef DATE_H
#define DATE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

#define DATE_MONTH      12

__attribute__((unused)) static const char* weekday_txt [8]        = {"xx", "Mo", "Di", "Mi", "Do", "Fr", "Sa", "So"};

typedef struct DateStruct {
  uint8_t  day;
  uint8_t  month;
  uint16_t year;
  uint8_t  weekday;
  uint8_t  calweek;
  uint8_t  leapyear;
} DateStruct;

uint8_t DateCalculate   ( DateStruct* p_date );
void    DateCalcWeekDay ( DateStruct* p_date );
void    DateCalcCalweek ( DateStruct* p_date );
void    DateCalcDayInc  ( DateStruct* p_date );
void    DateCalcDayDec  ( DateStruct* p_date );
void    DateCalcLeapYear( DateStruct* p_date );

#ifdef __cplusplus
} // extern "C"
#endif

#endif
