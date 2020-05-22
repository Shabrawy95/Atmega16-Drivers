/*********************************************************************************************************************************
 *  Filename: timer1.c
 *
 *  Description: source file for timer 1 driver
 *
 *  Created on: Jan 07, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/
#include "timer1.h"
/*********************************************************************************************************************************
 *                   									  Global Variables                                  													 *
 *********************************************************************************************************************************/

/* to hold address of callback function form application*/
static volatile void (*g_callBackPtr1)(void) = NULL_PTR;
static volatile void (*g_callBackPtr2)(void) = NULL_PTR;
static volatile void (*g_callBackPtr3)(void) = NULL_PTR;
/*********************************************************************************************************************************
 *                   									  ISRs                                 													 *
 *********************************************************************************************************************************/

ISR(TIMER1_OVF_vect){
	if(g_callBackPtr1 != NULL_PTR){
		 		(*g_callBackPtr1)();
		 	}
}

ISR(TIMER1_COMPA_vect){
	if(g_callBackPtr2 != NULL_PTR){
		 		(*g_callBackPtr2)();
		 	}
}
ISR(TIMER1_COMPB_vect){
	if(g_callBackPtr3 != NULL_PTR){
		 		(*g_callBackPtr3)();
		 	}
}

/*********************************************************************************************************************************
 *                   									 Function definitions                                													 *
 *********************************************************************************************************************************/

/*description: Function to set Time0 Mode, clock, interrupts, initial value, and compare value */
void TIMER1_Init(TIMER1_ConfigType* config_Ptr){

	TCNT1 = config_Ptr->initialValue;
	TCCR1A = (1<<FOC1A)|(1<<FOC1B)|(((config_Ptr->mode)&0x03)) |((config_Ptr->oc1a_mode)<<6)\
			|((config_Ptr->oc1b_mode)<<4);
			/*(((config_Ptr->mode)&0x03))  to get WGM11:10
			 * ((config_Ptr->oc1a_mode)<<6) to get COM1A1:0 bits*/
	TCCR1B = (((config_Ptr->mode)&0x0C)<<1) | ((config_Ptr->clock));
			/* 0x0C = 0000 1100 to get higher bits of mode xx00 then shift left by one
			 * to get WGM13:12 bits since WGM13 is bit no 4 in TCCR1B*/
	TIMSK |= (config_Ptr->interrupt);
	OCR1A = 0; /*unless needed*/
	OCR1B = 0; /*unless needed*/
	ICR1 = 0;

		if((config_Ptr->oc1a_mode) != T1_OC1A_OFF){ /*you can output two wave on OC1A and OC1B */
			SET_BIT(DDRD, 5); /*OC1A pin output to generate wave using normal mode*/
		}
		if((config_Ptr->oc1b_mode) != T1_OC1B_OFF){
			SET_BIT(DDRD, 4); /*OC1B pin output to generate wave using normal mode*/
		}

		if((config_Ptr->compValueA) != NO_COMPARE_A){
			OCR1A = (config_Ptr->compValueA);
		}
		if((config_Ptr->compValueB) != NO_COMPARE_B){
			OCR1A = (config_Ptr->compValueB);
		}
		if((config_Ptr->icuValue) != NO_ICR1){
			OCR1A = (config_Ptr->icuValue);
		}



	}




/* function to change initial value*/
void TIMER1_setInitial(uint16 a_Initial){
	TCNT1 = a_Initial;
}

/* function to change compare value or top value in mode 4*/

void TIMER1_setCompValA(uint16 a_Comp){
	OCR1A = a_Comp;
}
/* function to change compare value */
void TIMER1_setCompValB(uint16 a_Comp){
	OCR1B = a_Comp;
}
/* function to change top value */
void TIMER1_setICR1(uint16 a_ICR){
	ICR1 = a_ICR;
}
/* set callback function to application layer
 *
 * three functions cause you can have over flow interrupt and COMP A and COMP B
 * at the same time in case of normal mode and OC1IE1A OC1BIE1B are set at compare
 * match (not necassary but whatever)
 */

void TIMER1_setCallBack_OVF(void (*a_Ptr)(void)){
	g_callBackPtr1 = a_Ptr;
}

void TIMER1_setCallBack_COMPA(void (*a_Ptr)(void)){
	g_callBackPtr2 = a_Ptr;
}

void TIMER1_setCallBack_COMPB(void (*a_Ptr)(void)){
	g_callBackPtr3 = a_Ptr;
}

void TIMER1_setInterrupt(TIMER1_Interrupt a_Int){
	TIMSK |= a_Int;
}

void TIMER1_disableInterrupt(TIMER1_Interrupt a_Int){
	TIMSK &=~ a_Int;
}

void TIMER1_Pause(void){
	TCCR1B &=~ 0x07;
}

void TIMER1_Resume(TIMER1_Clock a_Clock){
	TCCR1B = (TCCR1B & 0xF8)|a_Clock;
}


void TIMER1_deInit(void){
	TCNT0 = 0;
	OCR1A = 0;
	OCR1B = 0;
	TCCR1A = 0;
	TCCR1B = 0;
	ICR1 =0;
}
