 /*********************************************************************************************************************************
 *
 * Module: External Interrupts
 *
 * File Name: interrupt.c
 *
 * Description: source file for external interrupts
 *
 * Author: Shabrawy
 *
 *********************************************************************************************************************************/

#include "interrupt.h"
/*********************************************************************************************************************************
 *                     							Global Variables                                 													 *
 *********************************************************************************************************************************/

/*Callback function to do any task in the application layer*/
 static volatile void (*g_int0CallBackPtr)(void) = NULL_PTR;
 static volatile void (*g_int1CallBackPtr)(void) = NULL_PTR;
 static volatile void (*g_int2CallBackPtr)(void) = NULL_PTR;

/*********************************************************************************************************************************
 *                     							ISR Definitions                                 													 *
 *********************************************************************************************************************************/
ISR(INT0_vect){
	if(g_int0CallBackPtr!=NULL_PTR){
		(*g_int0CallBackPtr)();
	}
}

ISR(INT1_vect){
	if(g_int1CallBackPtr!=NULL_PTR){
		(*g_int1CallBackPtr)();
	}
}

ISR(INT2_vect){
	if(g_int2CallBackPtr!=NULL_PTR){
		(*g_int2CallBackPtr)();
	}
}

/*********************************************************************************************************************************
 *                     							Function Definitions                                 													 *
 *********************************************************************************************************************************/

void INT_init(INT_Config* config_Ptr){
	SREG |= (1<<7); /*Enable global interrupts*/
	if((config_Ptr->num)==INT_0){
		CLEAR_BIT(DDRD, PD2);/* INT 0 pin input*/
		SET_BIT(GICR, config_Ptr->num); /* Set bit of INT0 i.e 6*/
		MCUCR = (MCUCR & 0xFC)|(config_Ptr->trigger); /* 0xFC -> 1111 1100 to zero out ISC01: ISC00*/
		if(config_Ptr->pullUp){
			SET_BIT(PORTD, PD2);/* INT 0 pin Internal resistance*/
		}
	}
	else if((config_Ptr->num)==INT_1){
		CLEAR_BIT(DDRD, PD3);/* INT 1 pin input*/
		SET_BIT(GICR, config_Ptr->num); /* Set bit of INT1 i.e 7*/
		MCUCR = (MCUCR & 0xF3)|((config_Ptr->trigger)<<2); /* 0xF3 -> 1111 0011 to zero out ISC11: ISC10*/
		if(config_Ptr->pullUp){
			SET_BIT(PORTD, PD3);/* INT 1 pin Internal resistance*/
		}

	}
	else if((config_Ptr->num)==INT_2){
		CLEAR_BIT(DDRB, PB2);/* INT 2 pin input*/
		SET_BIT(GICR, config_Ptr->num); /* Set bit of INT2 i.e5 */
		MCUCSR = (MCUCSR & 0xBF) | (((config_Ptr->trigger)& 0x01)<<6);/* 0xBF -> 1011 1111 to zero out ISC2 Bit

			(Config_PTR -> num & 0x01) since for INT2 falling edge = 0 and rising edge = 1
			so we and the value of falling which is 2 with 1 to get zero
			and for rising edge and the value of rising which is 3 with 1 to get 1
		*/
		if(config_Ptr->pullUp){
			SET_BIT(PORTB, PB2);/* INT 2 pin Internal resistance*/
		}
	}
}

void INT0_setEdgeDetectionType(const INT_Trigger a_trigger){
	MCUCR = (MCUCR & 0xFC)|(a_trigger); /* 0xFC -> 1111 1100 to zero out ISC01: ISC00*/

}

void INT1_setEdgeDetectionType(const INT_Trigger a_trigger){
	MCUCR = (MCUCR & 0xF3)|(a_trigger<<2);
}
void INT2_setEdgeDetectionType(const INT_Trigger a_trigger){
	MCUCSR = (MCUCSR & 0xBF) | ((a_trigger& 0x01)<<6);
}

void INT0_setCallBack(void (*a_Ptr)(void)){
	g_int0CallBackPtr=a_Ptr;
}

void INT1_setCallBack(void (*a_Ptr)(void)){
	g_int1CallBackPtr=a_Ptr;
}

void INT2_setCallBack(void (*a_Ptr)(void)){
	g_int2CallBackPtr=a_Ptr;
}
/*function that takes interrupt number and disables it*/
void INT_Disable(const INT_Number a_intNum){
	CLEAR_BIT(GICR, a_intNum);
}
