/*********************************************************************************************************************************
 *  Filename: icu.c
 *
 *  Description: source file for icu driver
 *
 *  Created on: Jan 03, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/
#include "icu.h"

/*********************************************************************************************************************************
 *                   									  Global Variables                                  													 *
 *********************************************************************************************************************************/
/* to hold address of callback function from application*/
static volatile void(* g_callBackPtr)(void)= NULL_PTR;

/*********************************************************************************************************************************
 *              										        ISRs                                  													 *
 *********************************************************************************************************************************/
ISR(TIMER1_CAPT_vect){
	if(g_callBackPtr != NULL_PTR){
		(* g_callBackPtr)();
	}
}

/*********************************************************************************************************************************
 *       								                Function definition                                  													 *
 *********************************************************************************************************************************/
/*
 * Initialize ICU
 * Normal Mode: timer 1
 * enable edge select initially for rising
 * no prescaler
 * initialize TCNT1 & ICR1 Registers
 * Enable ICU Interrupt
 * */
void ICU_init(ICU_ConfigType* Config_Ptr){
	DDRD &= ~(1<<PD6); /*set ICP1 pin as input to capture signal*/
	TCCR1A = (1<<FOC1A)|(1<<FOC1B); /*Normal mode and no COM needed and FOC since non pwm mode*/
	TCCR1B = (TCCR1B & 0xBF)|((Config_Ptr->edge)<<6); /* 0xBF 1011 1111 to zeroe the ICES bit*/
	TCCR1B = (TCCR1B & 0xF8)|(Config_Ptr->clock); /* 0xF8 1111 1000 to zeroe the CS bits*/
	TCNT1 = 0; /*Timer initially is zero*/
	ICR1 = 0;
	TIMSK |= (1<<TICIE1);

}

/*function to set callback pointer form application*/
void ICU_setCallBack(void (*a_Ptr)(void)){
	g_callBackPtr = a_Ptr;
}

/*function to clear timer value at beggining of measurement i.e after first edge */
void ICU_clearTimerValue(void){
	TCNT1 = 0;
}

/*function to return value in ICR1 at each interrupt*/
uint16 ICU_getInputCaptureValue(void){
	return ICR1;
}

void ICU_setEdgeType(ICU_EdgeType a_edge){
	TCCR1B = (TCCR1B & 0xBF)|(a_edge<<6); /* 0xBF 1011 1111 to zeroe the ICES bit*/

}

/*function to disable ICU Driver*/
void ICU_deInit(void){
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 =0;
	TIMSK &= ~(1<<TICIE1);/*disable ICU interrupt*/

}
