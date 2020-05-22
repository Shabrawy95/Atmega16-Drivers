/*********************************************************************************************************************************
 *  Filename: icu.h
 *
 *  Description: header file for icu driver
 *
 *  Created on: Jan 03, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/

#ifndef ICU_H_
#define ICU_H_
#include "../../common/std_types.h"
#include "../../common/micro_config.h"
#include "../../common/common_macros.h"


/*********************************************************************************************************************************
 *               								      type definition                                  													 *
 *********************************************************************************************************************************/

typedef enum{
	ICU_FALLING, ICU_RISING
}ICU_EdgeType;

typedef enum{
	ICU_NO_CLOCK, ICU_F_CPU_CLOCK, ICU_F_CPU_8, ICU_F_CPU_64, ICU_F_CPU_256, ICU_F_CPU_2014
}ICU_Clock;

typedef struct{
	ICU_EdgeType edge;
	ICU_Clock clock;
}ICU_ConfigType;

/*********************************************************************************************************************************
 *               								      function prototypes
 *********************************************************************************************************************************/
void ICU_init(ICU_ConfigType* Config_Ptr);
void ICU_setCallBack(void (*a_Ptr)(void));
void ICU_clearTimerValue(void);
uint16 ICU_getInputCaptureValue(void);
void ICU_setEdgeType(ICU_EdgeType a_edge);
void ICU_deInit(void);

#endif /* ICU_H_ */
