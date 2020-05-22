/*********************************************************************************************************************************
 *  Filename: pwm_timer2.c
 *
 *  Description: source file for timer 0 pwm driver
 *
 *  Created on: Jan 03, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/
#include "pwm_timer2.h"


/*********************************************************************************************************************************
 *                   									 Function definitions                                													 *
 *********************************************************************************************************************************/

/*description: Function to set PWM Mode for timer 2, clock,  initial value, and duty cycle */


void PWM_TIM2_Init(PWM_TIM2_ConfigType* config_Ptr){
	TCNT2 = 0;
	TCCR2 = (((config_Ptr->timerMode) &0x01)<<6)|	(((config_Ptr->timerMode)&0x02)<<2)|\
			((config_Ptr->pwmMode)<<4)|(config_Ptr->clock);
	/*(((config_Ptr->timerMode)&0x01)<<6) to get WGM20
	 * (((config_Ptr->timerMode)&0x02)<<2) to get WGM21
	 * ((config_Ptr->pwmMode)<<4) to get COM21:20 bits
	 * */
	SET_BIT(DDRD, 7); /*OC2 is o/o for pwm signal*/
	OCR2 = config_Ptr->duty;


}

void PWM_TIM2_setDuty(uint8 a_Duty){
	OCR2 = a_Duty;
}


void PWM_TIM2_deInit(void){
	TCCR2 = 0;
	TCNT2 = 0;
	OCR2 = 0;
}
