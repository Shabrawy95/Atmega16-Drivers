/*********************************************************************************************************************************
 *  Filename: pwm_timer1.c
 *
 *  Description: source file for timer 2 pwm driver
 *
 *  Created on: Jan 03, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/
#include "pwm_timer1.h"

/*********************************************************************************************************************************
 *                   									 Function definitions                                													 *
 *********************************************************************************************************************************/


/*description: Function to set Time0 Mode, clock, interrupts, initial value, and compare value */

void PWM_TIM1_Init(PWM_TIM1_ConfigType* config_Ptr){

	TCNT1 = 0;
	OCR1A = 0;/*initially OCR1A, OCR1B and ICR1 are zero until changed if need be*/
	OCR1B = 0;
	ICR1 = 0;
	TCCR1A = (((config_Ptr->timerMode)&0x03)) |((config_Ptr->pwmMode_OC1A)<<6)\
			|((config_Ptr->pwmMode_OC1B)<<4);
	/*(((config_Ptr->timerMode)&0x03))  to get WGM11:10
	 * ((config_Ptr->pwmMode_OC1A)<<6) to get COM1A1:0 bits
	 * ((config_Ptr->pwmMode_OC1B)<<4) to get COM1B1:0 bits*/

	TCCR1B = (((config_Ptr->timerMode) & 0x0C)<<1) | ((config_Ptr->clock));
	/* 0x0C = 0000 1100 to get higher bits of mode xx00 then shift left by one
	 * to get WGM13:12 bits since WGM13 is bit no 4 in TCCR1B*/

	if((config_Ptr->pwmMode_OC1A) != PWM1_OC1A_OFF){ /*you can output two wave on OC1A and OC1B */
		SET_BIT(DDRD, 5); /*OC1A is o/p for pwm signal*/
	}
	if((config_Ptr->pwmMode_OC1A) != PWM1_OC1B_OFF){

		SET_BIT(DDRD, 4); /*OC1B is o/p for pwm signal*/
	}

	if((config_Ptr->compValueA) != NO_COMPARE_A){
		OCR1A = (config_Ptr->compValueA);
	}
	if((config_Ptr->compValueB) != NO_COMPARE_B){
		OCR1B = (config_Ptr->compValueB);
	}
	if((config_Ptr->icuValue) != NO_ICR1){
		ICR1 = (config_Ptr->icuValue);
	}




}


void PWM_TIM1_setCompValA(uint16 a_Comp){
	OCR1A = a_Comp;
}
/* function to change compare value, or top value in mode 9, 15 */
void PWM_TIM1_setCompValB(uint16 a_Comp){
	OCR1B = a_Comp;
}
/* function to change top value in mode 8, 14*/
void PWM_TIM1_setICR1(uint16 a_ICR){
	ICR1 = a_ICR;
}



void PWM_TIM1_deInit(void){
	TCNT0 = 0;
	OCR1A = 0;
	OCR1B = 0;
	TCCR1A = 0;
	TCCR1B = 0;
	ICR1 =0;
}
