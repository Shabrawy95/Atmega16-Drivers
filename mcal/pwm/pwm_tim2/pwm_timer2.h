/*********************************************************************************************************************************
 *  Filename: pwm_timer2.h
 *
 *  Description: header file for timer 2 pwm driver
 *
 *  Created on: Jan 03, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/

#ifndef PWM_TIMER2_H_
#define PWM_TIMER2_H_
#include "../../../common/std_types.h"
#include "../../../common/micro_config.h"
#include "../../../common/common_macros.h"
/*********************************************************************************************************************************
 *                   									Type defintions                                													 *
 *********************************************************************************************************************************/

typedef enum{
	 T2_PHASE_CORRECT = 1, T2_FAST_PWM = 3
}TIMER2_Mode;

typedef enum{
	PWM2_OFF = 0, PWM2_NON_INVERTING = 2, PWM2_INVERTING = 3
}PWM_TIM2_MODE;
typedef enum{
	PWM2_NO_CLOCK, PWM2_F_CPU_CLOCK, PWM2_F_CPU_8, PWM2_F_CPU_32,
	PWM2_F_CPU_64, PWM2_F_CPU_128, PWM2_F_CPU_256, PWM2_F_CPU_1024
}PWM_TIM2_Clock;


typedef struct{
	TIMER2_Mode timerMode;
	PWM_TIM2_MODE pwmMode;
	PWM_TIM2_Clock clock;
	uint8 duty;
}PWM_TIM2_ConfigType;

/*********************************************************************************************************************************
 *                   									Function prototypes                               													 *
 *********************************************************************************************************************************/
void PWM_TIM2_Init(PWM_TIM2_ConfigType* config_Ptr);
void PWM_TIM2_setDuty(uint8 a_Duty);
void PWM_TIM2_deInit(void);
#endif /* PWM_TIMER2_H_ */
