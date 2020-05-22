/*******************************************************************************************************************************************************
 *  Filename: stepper_motor.c
 *
 *  Description: source file for stepper motor driver
 *
 *  Created on: Dec 27, 2019
 *
 *  Author: Shabrawy
 *******************************************************************************************************************************************************/


/******************************************************************************************************************************************************
 *                     Function definition                                  											                 	    	 *
 ***********************S*******************************************************************************************************************************/
#include "stepper_motor.h"


void STEPPER_Motor_Init(void){
#ifdef STPR_UPPER_PORT_PINS
	SET_HI_NIBBLE(STEPPER_MOTOR_CTRL_PORT_DIR); /*use pins p4 to p7 as input to motor and output form mcu*/
	CLEAR_HI_NIBBLE(STEPPER_MOTOR_CTRL_PORT);
#else
		SET_LW_NIBBLE(STEPPER_MOTOR_CTRL_PORT_DIR); /*use pins p0 to p3 */
		CLEAR_LW_NIBBLE(STEPPER_MOTOR_CTRL_PORT);
#endif


}

void STEPPER_FullStep_Begin(uint16 a_Speed){

	static unsigned char count1 = 0;

	    unsigned char motor_fullSteps[FULL_WAVE_STEPS] = {12,6,3,9};

	    for(count1 = 0; count1 < FULL_WAVE_STEPS; count1++){
			#ifdef STPR_UPPER_PORT_PINS
					STEPPER_MOTOR_CTRL_PORT = (STEPPER_MOTOR_CTRL_PORT&0x0F)|((motor_fullSteps[count1]&0x0F)<<4);
					_delay_ms(a_Speed);
			#else
					STEPPER_MOTOR_CTRL_PORT = (STEPPER_MOTOR_CTRL_PORT&0xF0)|(motor_fullSteps[count1]&0x0F);
					_delay_ms(a_Speed);
			#endif
	    }
	count1 = 0;

}

void STEPPER_HalfStep_Begin(uint16 a_Speed){
	static unsigned char count2 = 0;
	unsigned char motor_halfSteps[HALF_WAVE_STEPS] = {8,12,4,6,2,3,1,9};
	for(count2 = 0; count2 < HALF_WAVE_STEPS; count2++){
	#ifdef STPR_UPPER_PORT_PINS

			STEPPER_MOTOR_CTRL_PORT = (STEPPER_MOTOR_CTRL_PORT&0x0F)|((motor_halfSteps[count2]&0x0F)<<4);
			_delay_ms(a_Speed);
	#else
			STEPPER_MOTOR_CTRL_PORT = (STEPPER_MOTOR_CTRL_PORT&0xF0)|(motor_halfSteps[count2]&0x0F);
			_delay_ms(a_Speed);
	#endif
	}
	count2=0;

}

void STEPPER_Motor_Stop(void){
#ifdef STPR_UPPER_PORT_PINS
	CLEAR_HI_NIBBLE(STEPPER_MOTOR_CTRL_PORT);
#else
		CLEAR_LW_NIBBLE(STEPPER_MOTOR_CTRL_PORT);
#endif

}


