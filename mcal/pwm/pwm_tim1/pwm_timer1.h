/*********************************************************************************************************************************
 *  Filename: pwm_timer1.h
 *
 *  Description: header file for timer 1 pwm driver
 *
 *  Created on: Jan 03, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/

#ifndef PWM_TIMER1_H_
#include "../../../common/std_types.h"
#include "../../../common/micro_config.h"
#include "../../../common/common_macros.h"
/*********************************************************************************************************************************
*                   								Type and PREPROCESSOR defintions                                													 *
 *********************************************************************************************************************************/
#ifndef NO_COMPARE_A
#define NO_COMPARE_A 0
#endif

#ifndef NO_COMPARE_B
#define NO_COMPARE_B 0
#endif

#ifndef NO_ICR1
#define NO_ICR1 0
#endif
/*not necessary to put T1_ prefix because those modes are not defined
 * any where else but for consistency */
typedef enum{
	T1_PHASE_CORRECT_8 = 1, T1_PHASE_CORRECT_9 = 2 ,T1_PHASE_CORRECT_10 = 3,
	T1_FAST_PWM_8 = 5 ,T1_FAST_PWM_9 = 6, T1_FAST_PWM_10 = 7, T1_PHASE_FREQ_ICR1 = 8,
	T1_PHASE_FREQ_OCR1A = 9, T1_PHASE_CORRECT_ICR1 = 10, T1_PHASE_CORRECT_OCR1A = 11,
	T1_FAST_PWM_ICR1 = 14, T1_FAST_PWM_OCR1A = 15
}TIMER1_Mode;

typedef enum{
	PWM1_OC1A_OFF = 0, PWM1_OC1A_TOGGLE = 1, PWM1_OC1A_NON_INVERTING = 2, PWM1_OC1A_INVERTING = 3
}PWM_TIM1_OC1A_MODE;


typedef enum{
	PWM1_OC1B_OFF = 0, PWM1_OC1B_NON_INVERTING = 2, PWM1_OC1B_INVERTING = 3
}PWM_TIM1_OC1B_MODE;



typedef enum{
	PWM1_NO_CLOCK, PWM1_F_CPU_CLOCK, PWM1_F_CPU_8, PWM1_F_CPU_64, PWM1_F_CPU_256,
	PWM1_F_CPU_1024, PWM1_EXTERNAL_FALLING, PWM1_EXTERNAL_RISING
}PWM_TIM1_Clock;


typedef struct{
	TIMER1_Mode timerMode;
	PWM_TIM1_OC1A_MODE pwmMode_OC1A;
	PWM_TIM1_OC1B_MODE pwmMode_OC1B;
	PWM_TIM1_Clock clock;
	uint16 compValueA;
	uint16 compValueB;
	uint16 icuValue; /*for top value when ICR1 is top*/


}PWM_TIM1_ConfigType;






/*********************************************************************************************************************************
 *                   									Function prototypes                               													 *
 *********************************************************************************************************************************/
void PWM_TIM1_Init(PWM_TIM1_ConfigType* config_Ptr);
void PWM_TIM1_setCompValA(uint16 a_Comp);
void PWM_TIM1_setCompValB(uint16 a_Comp);
/* function to change top value in mode 8, 14*/
void PWM_TIM1_setICR1(uint16 a_ICR);
void PWM_TIM1_deInit(void);
#endif /* PWM_TIMER1_H_ */
