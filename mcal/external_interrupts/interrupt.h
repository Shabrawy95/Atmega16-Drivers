 /*********************************************************************************************************************************
 *
 * Module: External Interrupts
 *
 * File Name: interrupt.h
 *
 * Description: header file for external interrupts
 *
 * Author: Shabrawy
 *
 *********************************************************************************************************************************/
#ifndef INTERRUPT_H_
#define INTERRUPT_H_
#include "../../common/std_types.h"
#include "../../common/micro_config.h"
#include "../../common/common_macros.h"


/*********************************************************************************************************************************
 *                     							Type Definitions                                 													 *
 *********************************************************************************************************************************/
/*when configured with my DIO ISA remove underscore from INT_x
 * INT2 = 5 to put in GICR at bit 5 same from INT0 and INT1 for bits 6 and 7
 * */
typedef enum{
	INT_2=5, INT_0 , INT_1
}INT_Number;
/*INT_ prefix is not necessary unless dio is included* since INFREE, IN_PULL are defined here*/
typedef enum{
	INT_LOW_LEVEL, INT_LOGICAL_CHANGE, INT_FALLING_EDGE, INT_RISING_EDGE
}INT_Trigger;

typedef enum{
	INT_INFREE, INT_IN_PULLUP
}INT_internalPullUp;

typedef struct{
	INT_Number num;
	INT_Trigger trigger;
	INT_internalPullUp pullUp;
}INT_Config;

/*********************************************************************************************************************************
 *                     							Function Prototypes                                													 *
 *********************************************************************************************************************************/

void INT_init(INT_Config* config_Ptr);
void INT0_setEdgeDetectionType(const INT_Trigger a_trigger);
void INT1_setEdgeDetectionType(const INT_Trigger a_trigger);
void INT2_setEdgeDetectionType(const INT_Trigger a_trigger);
void INT0_setCallBack(void (*a_Ptr)(void));
void INT1_setCallBack(void (*a_Ptr)(void));
void INT2_setCallBack(void (*a_Ptr)(void));
void INT_Disable(const INT_Number a_intNum);

#endif /* INTERRUPT_H_ */
