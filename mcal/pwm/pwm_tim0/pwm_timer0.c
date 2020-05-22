/*********************************************************************************************************************************
 *  Filename: pwm_timer0.c
 *
 *  Description: source file for timer 0 pwm driver
 *
 *  Created on: Jan 03, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/
#include "pwm_timer0.h"


/*********************************************************************************************************************************
 *                   									 Function definitions                                													 *
 *********************************************************************************************************************************/

/*description: Function to set PWM Mode for timer 0, clock,  initial value, and duty cycle */


void PWM_TIM0_Init(PWM_TIM0_ConfigType* config_Ptr){
	TCNT0 = 0;
	TCCR0 = (((config_Ptr->timerMode) &0x01)<<6)|	(((config_Ptr->timerMode)&0x02)<<2)|\
			((config_Ptr->pwmMode)<<4)|(config_Ptr->clock);
	/*(((config_Ptr->timerMode)&0x01)<<6) to get WGM00
	 * (((config_Ptr->timerMode)&0x02)<<2) to get WGM01
	 * ((config_Ptr->pwmMode)<<4) to get COM01:00 bits
	 * */
	SET_BIT(DDRB, 3); /*OC0 is o/o for pwm signal*/
	OCR0 = config_Ptr->duty;


}

void PWM_TIM0_setDuty(uint8 a_Duty){
	OCR0 = a_Duty;
}


void PWM_TIM0_deInit(void){
	TCCR0 = 0;
	TCNT0 = 0;
	OCR0 = 0;
}
