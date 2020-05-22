/*********************************************************************************************************************************
 *  Filename: timer1.h
 *
 *  Description: header file for timer 1 driver
 *
 *  Created on: Jan 07, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_
#include "../../../common/std_types.h"
#include "../../../common/micro_config.h"
#include "../../../common/common_macros.h"

/*********************************************************************************************************************************
 *                   									Type and PREPROCESSOR defintions                                   													 *
 *********************************************************************************************************************************/
#ifndef NO_COMPARE_A
#define NO_COMPARE_A 0
#endif

#ifndef NO_COMPARE_B
#define NO_COMPARE_B 0
#endif

#ifndef NO_ICR1
#define NO_ICR1 0
#endif

typedef enum{
	T1_NORMAL = 0, T1_CTC_OCR1A=4, T1_CTC_ICR1 = 12, /*CTC_OCR1A, CTC_ICR1 not necessary to put prefix cause the don't
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 exist anywhere else*/
}TIMER1_Mode;

typedef enum{
	T1_OC1A_OFF, T1_OC1A_TOGGLE, T1_OC1A_CLEAR, T1_OC1A_SET
}TIMER1_OC1A_Mode;

typedef enum{
	T1_OC1B_OFF, T1_OC1B_TOGGLE, T1_OC1B_CLEAR, T1_OC1B_SET
}TIMER1_OC1B_Mode;

typedef enum{
	T1_NO_CLOCK, T1_F_CPU_CLOCK, T1_F_CPU_8, T1_F_CPU_64, T1_F_CPU_256, T1_F_CPU_1024,
	T1_EXTERNAL_FALLING, T1_EXTERNAL_RISING
}TIMER1_Clock;

typedef enum{
	T1_DISABLED, T1_OVF_ENABLE = 4, T1_COMPB_ENABLE = 8, T1_COMPA_ENABLE = 16,
	T1_OVF_AND_COMPB = 12 ,  T1_OVF_AND_COMPA = 20, T1_COMPA_AND_COMPB = 24,
	T1_OVF_AND_COMPA_AND_COMPB = 28/*values in TIMSK register for each bit*/
}TIMER1_Interrupt;
typedef struct{
	TIMER1_Mode mode;
	TIMER1_OC1A_Mode oc1a_mode;
	TIMER1_OC1B_Mode oc1b_mode;
	TIMER1_Clock clock;
	TIMER1_Interrupt interrupt;
	uint16 initialValue;
	uint16 compValueA;
	uint16 compValueB;
	uint16 icuValue;
}TIMER1_ConfigType;




/*********************************************************************************************************************************
 *                   									Function prototypes                               													 *
 *********************************************************************************************************************************/
void TIMER1_Init(TIMER1_ConfigType* config_Ptr);
/* function to change initial value*/
void TIMER1_setInitial(uint16 a_Initial);
void TIMER1_setCompValA(uint16 a_Comp);
/* function to change compare value */
void TIMER1_setCompValB(uint16 a_Comp);
/* function to change top value */
void TIMER1_setICR1(uint16 a_ICR);
void TIMER1_deInit(void);
void TIMER1_setCallBack_OVF(void (*a_Ptr)(void));
void TIMER1_setCallBack_COMPA(void (*a_Ptr)(void));
void TIMER1_setCallBack_COMPB(void (*a_Ptr)(void));
void TIMER1_setInterrupt(TIMER1_Interrupt a_Int);
void TIMER1_disableInterrupt(TIMER1_Interrupt a_Int);
void TIMER1_Pause(void);
void TIMER1_Resume(TIMER1_Clock a_Clock);
#endif /* TIMER1_H_ */
