/*******************************************************************************************************************************************************
 *  Filename: dc_motor.h
 *
 *  Description: header file for motor driver
 *
 *  Created on: Dec 27, 2019
 *
 *  Author: Shabrawy
 *******************************************************************************************************************************************************/


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "../../../common/std_types.h"
#include "../../../common/micro_config.h"
#include "../../../common/common_macros.h"

#define PWM_CONTROLLED
#undef PWM_CONTROLLED




/******************************************************************************************************************************************************
 *                     											CONFIG definition      s                            											                 	    	 *
 ******************************************************************************************************************************************************/
#define ONE_MOTOR /*only one motor connected*/
#undef TWO_MOTORS /*change to #define for two motors connected and #undef the othr*/


#define DC_MOTOR_CTRL_PORT_DIR DDRB
#define DC_MOTOR_CTRL_PORT PORTB
#define DC_MOTOR_INPUT1 PB0
#define DC_MOTOR_INPUT2 PB1

#ifdef TWO_MOTORS
#define DC_MOTOR2_CTRL_PORT_DIR DDRA
#define DC_MOTOR2_CTRL_PORT PORTA
#define DC_MOTOR2_INPUT1 PA0
#define DC_MOTOR2_INPUT2 PA1
#endif
/******************************************************************************************************************************************************
 *                     											 Function prototypes                          											                 	    	 *
 ******************************************************************************************************************************************************/
void DC_Motor_Init(void);

void DC_Motor_CW(void);
void DC_Motor_ACW(void);
void DC_Motor_Stop(void);
void DC_Motor_reverse(void);

#ifdef PWM_CONTROLLED
void DC_Motor_Speed(uint8 a_speed);
#endif

#ifdef TWO_MOTORS
void DC_Motor2_CW(void);
void DC_Motor2_ACW(void);
void DC_Motor2_Stop(void);
void DC_Moto2_reverse(void);
#endif



#endif /* DC_MOTOR_H_ */
