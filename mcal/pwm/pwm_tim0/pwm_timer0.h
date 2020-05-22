/*********************************************************************************************************************************
 *  Filename: pwm_timer0.h
 *
 *  Description: header file for timer 0 pwm driver
 *
 *  Created on: Jan 03, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/

#ifndef PWM_TIMER0_H_
#define PWM_TIMER0_H_
#include "../../../common/std_types.h"
#include "../../../common/micro_config.h"
#include "../../../common/common_macros.h"
/*********************************************************************************************************************************
 *                   									Type defintions                                													 *
 *********************************************************************************************************************************/




typedef enum{
	 T0_PHASE_CORRECT = 1, T0_FAST_PWM = 3
}TIMER0_Mode;

typedef enum{
	PWM0_OFF = 0, PWM0_NON_INVERTING = 2, PWM0_INVERTING = 3
}PWM_TIM0_MODE;
typedef enum{
	PWM0_NO_CLOCK, PWM0_F_CPU_CLOCK, PWM0_F_CPU_8, PWM0_F_CPU_64,
	PWM0_F_CPU_256, PWM0_F_CPU_1024, PWM0_EXTERNAL_FALLING, PWM0_EXTERNAL_RISING
}PWM_TIM0_Clock;


typedef struct{
	TIMER0_Mode timerMode;
	PWM_TIM0_MODE pwmMode;
	PWM_TIM0_Clock clock;
	uint8 duty;
}PWM_TIM0_ConfigType;

/*********************************************************************************************************************************
 *                   									Function prototypes                               													 *
 *********************************************************************************************************************************/
void PWM_TIM0_Init(PWM_TIM0_ConfigType* config_Ptr);
void PWM_TIM0_setDuty(uint8 a_Duty);
void PWM_TIM0_deInit(void);
#endif /* PWM_TIMER0_H_ */
