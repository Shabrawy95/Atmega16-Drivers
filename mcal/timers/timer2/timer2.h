/*********************************************************************************************************************************
 *  Filename: timer2.h
 *
 *  Description: header file for timer 2 driver
 *
 *  Created on: Jan 03, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/

#ifndef TIMER2_H_
#define TIMER2_H_
#include "../../../common/std_types.h"
#include "../../../common/micro_config.h"
#include "../../../common/common_macros.h"
/*********************************************************************************************************************************
 *                   									Type and PREPROCESSOR defintions                                													 *
 *********************************************************************************************************************************/
#ifndef NO_COMPARE
#define NO_COMPARE 0
#endif

typedef enum{
	T2_NORMAL = 0, T2_CTC = 2
}TIMER2_Mode;

typedef enum{
	T2_OFF, T2_TOGGLE, T2_CLEAR, T2_SET
}TIMER2_OC2_Mode;

typedef enum{
	T2_NO_CLOCK, T2_F_CPU_CLOCK, T2_F_CPU_8, T2_F_CPU_32, T2_F_CPU_64, T2_F_CPU_128, T2_F_CPU_256, T2_F_CPU_1024
}TIMER2_Clock;

typedef enum{
	T2_DISABLED, T2_OVF_ENABLE, T2_COMP_ENABLE, T2_OVF_AND_COMP
}TIMER2_Interrupt;
typedef struct{
	TIMER2_Mode mode;
	TIMER2_OC2_Mode oc2_mode;
	TIMER2_Clock clock;
	TIMER2_Interrupt interrupt;
	uint8 initialValue;
	uint8 compValue;
}TIMER2_ConfigType;


/*********************************************************************************************************************************
 *                   									Function prototypes                               													 *
 *********************************************************************************************************************************/
void TIMER2_Init(TIMER2_ConfigType* config_Ptr);
void TIMER2_setCallBack(void (*a_Ptr)(void));
void TIMER2_setInitial(uint8 a_Initial);
void TIMER2_setCompVal(uint8 a_Comp);
void TIMER2_setInterrupt(TIMER2_Interrupt a_Int);
void TIMER2_disableInterrupt(TIMER2_Interrupt a_Int);
void TIMER2_Pause(void);
void TIMER2_Resume(TIMER2_Clock a_Clock);
void TIMER2_deInit(void);
#endif /* TIMER2_H_ */
