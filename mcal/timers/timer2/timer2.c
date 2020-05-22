/*********************************************************************************************************************************
 *  Filename: timer2.c
 *
 *  Description: source file for timer 0 driver
 *
 *  Created on: Jan 03, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/
#include "timer2.h"
/*********************************************************************************************************************************
 *                   									  Global Variables                                  													 *
 *********************************************************************************************************************************/

/* to hold address of callback function form application*/
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*********************************************************************************************************************************
 *                   									  ISRs                                 													 *
 *********************************************************************************************************************************/

ISR(TIMER2_OVF_vect){
	if(g_callBackPtr != NULL_PTR){
		 		(*g_callBackPtr)();
		 	}
}

ISR(TIMER2_COMP_vect){
	if(g_callBackPtr != NULL_PTR){
		 		(*g_callBackPtr)();
		 	}
}
/*********************************************************************************************************************************
 *                   									 Function definitions                                													 *
 *********************************************************************************************************************************/


void TIMER2_Init(TIMER2_ConfigType* config_Ptr){
		TCNT2 = config_Ptr->initialValue;
		TCCR2 = (1<<FOC2)|(((config_Ptr->mode)&0x01)<<6)|\
				(((config_Ptr->mode)&0x02)<<2)|((config_Ptr->oc2_mode)<<4)|\
				(config_Ptr->clock);
		/*(((config_Ptr->mode)&0x01)<<6) to get WGM20
		 * (((config_Ptr->mode)&0x02)<<2) to get WGM21
		 * ((config_Ptr->oc0_mode)&<<4) to get COM01:20 bits
		 * */
		OCR2 = 0;
		TIMSK |= (((config_Ptr)->interrupt)<<6); /*OVF_ENABLE = 1, COMP_ENABLE = 2*/

		if((config_Ptr->oc2_mode)!= T2_OFF){ /* OC0 pin is used on compare match*/
			SET_BIT(DDRD, 7); /*OC2 is o/p*/
		}

		if((config_Ptr->compValue)!= NO_COMPARE){
			OCR2 = (config_Ptr->compValue);
		}
}

/* function to change initial value*/
void TIMER2_setInitial(uint8 a_Initial){
	TCNT2 = a_Initial;
}

/* function to change compare value*/

void TIMER2_setCompVal(uint8 a_Comp){
	OCR2 = a_Comp;
}
/* set callback function to application layer*/
void TIMER2_setCallBack(void (*a_Ptr)(void)){
	g_callBackPtr = a_Ptr;
}

/* function to set specific interrupt*/
void TIMER2_setInterrupt(TIMER2_Interrupt a_Int){
	TIMSK |= (a_Int<<6); /*OVF_ENABLE = 1, COMP_ENABLE = 2*/
}

/* function to disable specific interrupt*/
void TIMER2_disableInterrupt(TIMER2_Interrupt a_Int){
	TIMSK &=~ (a_Int<<6); /*OVF_ENABLE = 1, COMP_ENABLE = 2*/
}

/* function to pause timer*/
void TIMER2_Pause(void){
	TCCR2 &=~ 0x07;
}

/* function to resume timer*/
void TIMER2_Resume(TIMER2_Clock a_Clock){
	TCCR2 |= (TCCR2 & 0xF8)|a_Clock;
}

void TIMER2_deInit(void){
	TCCR2 = 0;
	TCNT2 = 0;
	OCR2 = 0;
}
