/*******************************************************************************************************************************************************
 *  Filename: dc_motor.c
 *
 *  Description: source file for motor driver
 *
 *  Created on: Dec 27, 2019
 *
 *  Author: Shabrawy
 *******************************************************************************************************************************************************/


/******************************************************************************************************************************************************
 *                     Function definition                                  											                 	    	 *
 ***********************S*******************************************************************************************************************************/
#include "dc_motor.h"
#ifdef PWM_CONTROLLED
#include "../../../mcal/pwm/pwm_tim0/pwm_timer0.h"
#endif
/*description initialize the input ports to motor (output form MCU) and set initial value*/
void DC_Motor_Init(void){
	DC_MOTOR_CTRL_PORT_DIR |= (1<<DC_MOTOR_INPUT1)|(1<<DC_MOTOR_INPUT2);/*make ports output from mc and input to bridge for motor1*/
	DC_MOTOR_CTRL_PORT &=~ ((1<<DC_MOTOR_INPUT1)|(1<<DC_MOTOR_INPUT2));/*stop motor1 initially*/

#ifdef TWO_MOTORS
	DC_MOTOR2_CTRL_PORT_DIR |= (1<<DC_MOTOR2_INPUT1)|(1<<DC_MOTOR2_INPUT2);/*make ports output from mc and input to bridge for motor2*/
	DC_MOTOR2_CTRL_PORT &=~ ((1<<DC_MOTOR2_INPUT1)|(1<<DC_MOTOR2_INPUT2));/*stop motor2 initially*/

#endif

#ifdef PWM_CONTROLLED
	PWM_TIM0_ConfigType config = {T0_FAST_PWM, PWM0_NON_INVERTING, PWM0_F_CPU_8, 255};/*initially duty is 100%*/
	PWM_TIM0_Init(&config);
#endif
}

/*rotate motor clockwise*/
void DC_Motor_CW(void){
	DC_MOTOR_CTRL_PORT |=(1<<DC_MOTOR_INPUT2);
	DC_MOTOR_CTRL_PORT &=~ (1<<DC_MOTOR_INPUT1);
}
/*rotate motor anticlockwise*/
void DC_Motor_ACW(void){
	DC_MOTOR_CTRL_PORT &=~(1<<DC_MOTOR_INPUT2);
	DC_MOTOR_CTRL_PORT |= (1<<DC_MOTOR_INPUT1);
}

void DC_Motor_reverse(void){
	DC_MOTOR_CTRL_PORT ^=(1<<DC_MOTOR_INPUT2);
	DC_MOTOR_CTRL_PORT ^= (1<<DC_MOTOR_INPUT1);
}

void DC_Motor_Stop(void){
	DC_MOTOR_CTRL_PORT &=~ ((1<<DC_MOTOR_INPUT1)|(1<<DC_MOTOR_INPUT2));/*stop motor1 initially*/
}

#ifdef PWM_CONTROLLED
void DC_Motor_Speed(uint8 a_speed){

	PWM_TIM0_setDuty(a_speed); /*speed is sent for e.g 50 for 50%*/
}
#endif

#ifdef TWO_MOTORS
		/*rotate motor clockwise*/
		void DC_Motor2_CW(void){
			DC_MOTOR2_CTRL_PORT |=(1<<DC_MOTOR2_INPUT2);
			DC_MOTOR2_CTRL_PORT &=~ (1<<DC_MOTOR2_INPUT1);
		}
		/*rotate motor anticlockwise*/
		void DC_Motor2_ACW(void){
			DC_MOTOR2_CTRL_PORT &=~(1<<DC_MOTOR2_INPUT2);
			DC_MOTOR2_CTRL_PORT |= (1<<DC_MOTOR2_INPUT1);
		}
		void DC_Moto2_reverse(void){
			DC_MOTOR2_CTRL_PORT ^=(1<<DC_MOTOR2_INPUT2);
			DC_MOTOR2_CTRL_PORT ^= (1<<DC_MOTOR2_INPUT1);
		}

		void DC_Motor2_Stop(void){
			DC_MOTOR2_CTRL_PORT &=~ ((1<<DC_MOTOR2_INPUT1)|(1<<DC_MOTOR2_INPUT2));/*stop motor1 initially*/
		}

#endif

