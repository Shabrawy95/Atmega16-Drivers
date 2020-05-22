/*******************************************************************************************************************************************************
 *  Filename: servo.c
 *
 *  Description: source file for servo motor driver
 *
 *  Created on: Dec 27, 2019
 *
 *  Author: Shabrawy
 *******************************************************************************************************************************************************/


/******************************************************************************************************************************************************
 *                     Function definition                                  											                 	    	 *
 ***********************S*******************************************************************************************************************************/
#include "servo.h"
/*description
 * initialize servo by initializing pwm to output wave with 5%, then 7.5%, then 10% duty cyclec*/
void SERVO_Init(void){

	PWM_TIM1_ConfigType config = {T1_FAST_PWM_ICR1, PWM1_OC1A_NON_INVERTING, PWM1_OC1B_OFF,
			PWM1_F_CPU_64, ZERO, NO_COMPARE_B, 2499};/*initially duty is zero will change it when we start motor*/
			/*set servo shaft at 0* by 1 ms puls*/
	PWM_TIM1_Init(&config);

}

void SERVO_Start(void){
	PWM_TIM1_setCompValA(124);/* Set Servo shaft at 0° position by 1 ms pulse */
	_delay_ms(4500);
	PWM_TIM1_setCompValA(187);/* Set Servo shaft at 90° position by 1.5 ms pulse */
	_delay_ms(4500);
	PWM_TIM1_setCompValA(250);/* Set Servo shaft at 180° position by 2 ms pulse */
	_delay_ms(4500);
}



