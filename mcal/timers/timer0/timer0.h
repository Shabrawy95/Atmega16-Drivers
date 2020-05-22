/*********************************************************************************************************************************
 *  Filename: timer0.h
 *
 *  Description: header file for timer 0 driver
 *
 *  Created on: Jan 03, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/

#ifndef TIMER0_H_
#define TIMER0_H_
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
	T0_NORMAL = 0, T0_CTC = 2
}TIMER0_Mode;

typedef enum{
	T0_OFF, T0_TOGGLE, T0_CLEAR, T0_SET
}TIMER0_OC0_Mode;

typedef enum{
	T0_NO_CLOCK, T0_F_CPU_CLOCK, T0_F_CPU_8, T0_F_CPU_64, T0_F_CPU_256, T0_F_CPU_1024,
	T0_EXTERNAL_FALLING, T0_EXTERNAL_RISING
}TIMER0_Clock;

typedef enum{
	T0_DISABLED, T0_OVF_ENABLE, T0_COMP_ENABLE, T0_OVF_AND_COMP
}TIMER0_Interrupt;
typedef struct{
	TIMER0_Mode mode;
	TIMER0_OC0_Mode oc0_mode;
	TIMER0_Clock clock;
	TIMER0_Interrupt interrupt;
	uint8 initialValue;
	uint8 compValue;
}TIMER0_ConfigType;


/*********************************************************************************************************************************
 *                   									Function prototypes                               													 *
 *********************************************************************************************************************************/
void TIMER0_Init(TIMER0_ConfigType* config_Ptr);
void TIMER0_setCallBack(void (*a_Ptr)(void));
void TIMER0_setInitial(uint8 a_Initial);
void TIMER0_setCompVal(uint8 a_Comp);
void TIMER0_setInterrupt(TIMER0_Interrupt a_Int);
void TIMER0_disableInterrupt(TIMER0_Interrupt a_Int);
void TIMER0_Pause(void);
void TIMER0_Resume(TIMER0_Clock a_Clock);
void TIMER0_deInit(void);
#endif /* TIMER0_H_ */
