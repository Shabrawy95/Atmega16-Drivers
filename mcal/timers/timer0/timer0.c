/*********************************************************************************************************************************
 *  Filename: timer0.c
 *
 *  Description: source file for timer 0 driver
 *
 *  Created on: Jan 03, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/
#include "timer0.h"
/*********************************************************************************************************************************
 *                   									  Global Variables                                  													 *
 *********************************************************************************************************************************/

/* to hold address of callback function form application*/
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*********************************************************************************************************************************
 *                   									  ISRs                                 													 *
 *********************************************************************************************************************************/

ISR(TIMER0_OVF_vect){
	if(g_callBackPtr != NULL_PTR){
		 		(*g_callBackPtr)();
		 	}
}

ISR(TIMER0_COMP_vect){
	if(g_callBackPtr != NULL_PTR){
		 		(*g_callBackPtr)();
		 	}
}
/*********************************************************************************************************************************
 *                   									 Function definitions                                													 *
 *********************************************************************************************************************************/

/*typedef enum{
	NORMAL = 0, CTC = 2
}TIMER0_Mode;

typedef enum{
	OFF, TOGGLE, CLEAR, SET
}TIMER0_OC0_Mode;

typedef enum{
	NO_CLOCK, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024, EXTERNAL_FALLING, EXTERNAL_RISING
}TIMER0_Clock;

typedef enum{
	DISABLED, OVF_ENABLE, COMP_ENABLE
}TIMER0_Interrupt;;
typedef struct{
	TIMER0_Mode mode;
	TIMER0_OC0_Mode oc0_mode;
	TIMER0_Clock clock;
	TIMER0_Interrupt interrupt;
	uint8 initialValue;
	uint8 compValue;
}TIMER0_ConfigType;*/

/*description: Function to set Time0 Mode, clock, interrupts, initial value, and compare value */

void TIMER0_Init(TIMER0_ConfigType* config_Ptr){
		TCNT0 = config_Ptr->initialValue;
		TCCR0 = (1<<FOC0)|(((config_Ptr->mode)&0x01)<<6)|\
				(((config_Ptr->mode)&0x02)<<2)|((config_Ptr->oc0_mode)<<4)|\
				(config_Ptr->clock);
		/*(((config_Ptr->mode)&0x01)<<6) to get WGM00
		 * (((config_Ptr->mode)&0x02)<<2) to get WGM01
		 * ((config_Ptr->oc0_mode)&<<4) to get COM01:00 bits
		 * */
		OCR0 = 0;
		TIMSK |= (config_Ptr)->interrupt; /*OVF_ENABLE = 1, COMP_ENABLE = 2*/

		if((config_Ptr->oc0_mode)!= T0_OFF){ /* OC0 pin is used on compare match*/
			SET_BIT(DDRB, 3); /*OC0 pin output */
		}

		if((config_Ptr->compValue)!= NO_COMPARE){
			OCR0 = (config_Ptr->compValue);
		}
}

/* function to change initial value*/
void TIMER0_setInitial(uint8 a_Initial){
	TCNT0 = a_Initial;
}

/* function to change compare value*/

void TIMER0_setCompVal(uint8 a_Comp){
	OCR0 = a_Comp;
}
/* set callback function to application layer*/
void TIMER0_setCallBack(void (*a_Ptr)(void)){
	g_callBackPtr = a_Ptr;
}

/* function to set specific interrupt*/
void TIMER0_setInterrupt(TIMER0_Interrupt a_Int){
	TIMSK |= a_Int; /*OVF_ENABLE = 1, COMP_ENABLE = 2*/
}

/* function to disable specific interrupt*/
void TIMER0_disableInterrupt(TIMER0_Interrupt a_Int){
	TIMSK &=~ a_Int; /*OVF_ENABLE = 1, COMP_ENABLE = 2*/
}

/* function to pause timer*/
void TIMER0_Pause(void){
	TCCR0 &=~ 0x07;
}

/* function to resume timer*/
void TIMER0_Resume(TIMER0_Clock a_Clock){
	TCCR0 |= (TCCR0 & 0xF8)|a_Clock;
}

void TIMER0_deInit(void){
	TCCR0 = 0;
	TCNT0 = 0;
	OCR0 = 0;
}
