/*******************************************************************************************************************************************************
 *  Filename: stepper_motor.h
 *
 *  Description: header file for stepper motor driver
 *
 *  Created on: Dec 27, 2019
 *
 *  Author: Shabrawy
 *******************************************************************************************************************************************************/


#ifndef STEPPER_MOTOR_H_
#define STEPPER_MOTOR_H_

#include "../../../common/std_types.h"
#include "../../../common/micro_config.h"
#include "../../../common/common_macros.h"

/******************************************************************************************************************************************************
 *                     											CONFIG definition      s                            											                 	    	 *
 ******************************************************************************************************************************************************/
#define FULL_WAVE_STEPS 4 /*for four step sequence*/
#define HALF_WAVE_STEPS 8 /*for 8 step sequence*/


#undef STPR_UPPER_PORT_PINS /*use pins P4 to P7*/


#define STEPPER_MOTOR_CTRL_PORT_DIR DDRC
#define STEPPER_MOTOR_CTRL_PORT PORTC
#define STEPPER_MOTOR_INPUT1 PC0
#define STEPPER_MOTOR_INPUT2 PC1
#define STEPPER_MOTOR_INPUT3 PC2
#define STEPPER_MOTOR_INPUT4 PC3

/******************************************************************************************************************************************************
 *                     											 Function prototypes                          											                 	    	 *
 ******************************************************************************************************************************************************/

void STEPPER_Motor_Init(void);
void STEPPER_FullStep_Begin(uint16 a_Speed);
void STEPPER_HalfStep_Begin(uint16 a_Speed);
void STEPPER_Motor_Stop(void);



#endif /* STEPPER_MOTOR_H_ */
