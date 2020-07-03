/***************************************************************************//**
Structure for time and date.
*******************************************************************************/
/** @addtogroup TimeDate_api
@{*/
/** @file TimeDate.h Definition of time and date format. */
#ifndef  TIMEDATE_H
#define  TIMEDATE_H

#include <stdint.h>
#include "date.h"
#include "time.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct TimeDateStruct {
   TimeStruct time;
   DateStruct date;
} TimeDateStruct;

#ifdef __cplusplus
} // extern "C"
#endif


#endif // TIMEDATE_H
/** @} */
