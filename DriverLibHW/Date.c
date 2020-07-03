
#include "Date.h"

uint8_t Date_Month_Offset[DATE_MONTH]={0,3,3,6,1,4,6,2,5,0,3,5};
uint8_t Date_Month[DATE_MONTH]={31,28,31,30,31,30,31,31,30,31,30,31};
uint8_t Date_Month_CalWeek_Offset[DATE_MONTH]={0,4,8,12,17,21,25,30,34,39,43,47};

uint8_t DateCalculate ( DateStruct* p_date ) {
  uint8_t day=0;

  if((p_date->month>12)||(p_date->month<1)) return 0;
  if (p_date->year>7999)                    return 0;
  DateCalcLeapYear (p_date);
  day=Date_Month[p_date->month-1];
  if((p_date->month==2)&&p_date->leapyear)  day++;
  if((p_date->day>day)||(p_date->day<1))    return 0;
  DateCalcWeekDay (p_date);             // calculate valid weekday first
  DateCalcCalweek (p_date);             // calculate actual calender week
  return 1;
}

void DateCalcLeapYear(DateStruct* p_date) {
  if(((p_date->year%4==0) && (p_date->year%100!=0)) || (p_date->year%400==0)){
    p_date->leapyear=1;
  } else {
    p_date->leapyear=0;
  }
} // void DateCalcLeapYear(DateStruct* p_date)

void DateCalcWeekDay (DateStruct* p_date) {
  uint8_t week_day=0;
  uint8_t century=0;
  uint8_t yearone=0;

  week_day=p_date->day;
  week_day+=Date_Month_Offset[p_date->month-1];
  DateCalcLeapYear(p_date);

  if((p_date->month<3)&&p_date->leapyear) week_day--;

  yearone=p_date->year%100;
  week_day+=((yearone+yearone/4)%7);

  century=p_date->year/100;
  week_day+=((3-(century%4))*2);

  week_day+=6; //offset corr (1=>Mo...7=>So)

  week_day%=7;
  week_day++;
  p_date->weekday=week_day;
} // void DateCalcWeekDay (DateStruct* p_date)

//returns 1 if the last day in a year is in a 53 calendarweek
uint8_t Date_Calc_If_53Week_End (DateStruct* p_date) {
  DateStruct date_begin, date_end;
  //calc 01.01.x
  date_begin.day=1;
  date_begin.month=1;
  date_begin.year=p_date->year;
  DateCalcWeekDay((DateStruct*)&date_begin);
  //calc 31.12.x
  date_end.day=31;
  date_end.month=12;
  date_end.year=p_date->year;
  DateCalcWeekDay((DateStruct*)&date_end);
  if((date_begin.weekday==4)||(date_end.weekday==4))  {  // Tu
    return 1;
  } else {
    return 0;
  }
} // uint8_t Date_Calc_If_53Week_End

//returns 1 if the first day in a year is in a 53 calendarweek
uint8_t Date_Calc_If_53Week_Begin (DateStruct* p_date){
  DateStruct date_begin;
  //calc 01.01.x
  date_begin.day=1;
  date_begin.month=1;
  date_begin.year=p_date->year;
  DateCalcWeekDay((DateStruct*)&date_begin);

  if(date_begin.weekday==5) {           // friday
    return 1;
  } else {
//if this year %4=1 the year before was %4=0  AND this date begins with saturday AND year %400 is not 101
    if(((p_date->year&0x3)==1)&&(date_begin.weekday==6)&&((p_date->year%400)!=101)) {
      return 1;
    } else {
      return 0;
    }
  }
} // uint8_t Date_Calc_If_53Week_Begin (DateStruct* p_date)

//calweek calc with prints
void DateCalcCalweek(DateStruct* p_date) {
  uint8_t calweek=0;
   DateStruct date_begin;

  //calc 04.01.x
  date_begin.day=4;
  date_begin.month=1;
  date_begin.year=p_date->year;
  DateCalcWeekDay((DateStruct*)&date_begin);

  //get day "offset"
  calweek=date_begin.weekday-1;         // correct to 0=Mo

  //add month offset
  calweek+=Date_Month_Offset[p_date->month-1];

  //
  calweek+=p_date->day;

  DateCalcLeapYear(p_date);
  if((p_date->month>2)&&p_date->leapyear) calweek++;
  calweek=(calweek+3)/7;

  //add calweek offset
  calweek+=Date_Month_CalWeek_Offset[p_date->month-1];

  //Date_Print(p_date);
  if(calweek==0){
    if(Date_Calc_If_53Week_Begin(p_date)) calweek=53;
    else                                  calweek=52;
  } else if(calweek==53) {
    if(!Date_Calc_If_53Week_End(p_date))  calweek=1;
  }
  p_date->calweek=calweek;
} // void DateCalcCalweek(DateStruct* p_date)

//Increment actual date
void DateCalcDayInc (DateStruct* p_date) {
  uint8_t maxday=0;

  maxday=Date_Month[p_date->month-1];
  if (p_date->month==2) {
    DateCalcLeapYear(p_date);
    if ( p_date->leapyear ) maxday = 29;
    else                    maxday = 28;
  }
  if ( p_date->day < maxday ) {
    p_date->day++;
  } else {
    p_date->day = 1;
    p_date->month++;
    if ( p_date->month > 12 ) {
      p_date->month = 1; p_date->year++;
    }
  }
  DateCalcLeapYear (p_date);
  DateCalcCalweek  (p_date);
  DateCalcWeekDay  (p_date);
} // DateCalcDayInc

//Decrement actual date
void DateCalcDayDec (DateStruct* p_date) {
  uint8_t month=0;       // calculate last month

  p_date->day--;

  if ( p_date->day == 0 ) {
    month = p_date->month-1;
    if ( month == 0 ) {
      month = 12;
      p_date->year --;
    }
    p_date->day=Date_Month[p_date->month-1];  // last day in month
    if (p_date->month==2) {
      DateCalcLeapYear(p_date);
      if ( p_date->leapyear ) p_date->day = 29;
    }
  }

  DateCalcLeapYear (p_date);
  DateCalcCalweek  (p_date);
  DateCalcWeekDay  (p_date);
} // uint8_t DateCalcDayInc
