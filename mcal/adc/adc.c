/*********************************************************************************************************************************
 *  Filename: ADC.h
 *
 *  Description: header file for ADC driver
 *
 *  Created on: Jan 04, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/

#include"adc.h"

/*********************************************************************************************************************************
 *                       									Global Variables                                                                                      *
 *********************************************************************************************************************************/
#ifdef ADC_INTERRUPT

volatile uint16 g_adcResult = 0; /*used in case of interrupt only*/


/*********************************************************************************************************************************
 *                       									ISRS                                                                                     *
 *********************************************************************************************************************************/
ISR(ADC_vect){
	g_adcResult = ADC;

}

#endif

/*********************************************************************************************************************************
 *                       									Function Definitions                                                                                     *
 *********************************************************************************************************************************/

/*
 * Left adjust bits
 * set reference volt
 * ste channel
 * enable ADC
 * set prescaler
 * in case of auto trigger select auto trigger source
 */

void ADC_Init(ADC_Config* a_Config){
	ADMUX &= ~(1<<ADLAR);
	ADMUX = (ADMUX & 0x3F)|((a_Config->ref)<<6); /* 3F -> 0011 1111 to zero ref bits*/
	ADMUX = (ADMUX & 0xE0)|(a_Config->channel); /* E0 -> 1110 0000 to zero out 5 bits of MUX or channel selection*/
	ADCSRA = (1<<ADEN); /*Enable ADC*/
	ADCSRA = (ADCSRA & 0xF8)|(a_Config->clock); /* F8 -> 1111 1000 to zero out ADPS3:0 bits*/
	#ifdef ADC_INTERRUPT

	ADCSRA |=(1<<ADIE); /*In case of interrupt to enable ADC interrupt*/

	#endif

	#ifdef AUTO_TRIGGER
	ADCSRA |= (1<<ADATE); /*Enable auto trigger*/
	SFIOR |= ((a_Config->trigger_select)<<5); /*select auto trigger source ADTS2:0 bits*/
	#endif
}

#ifdef ADC_INTERRUPT

void ADC_startConversion(void){
	SET_BIT(ADCSRA, ADSC); /*start conversion*/

}


#else

uint16 ADC_readValue(void){
	SET_BIT(ADCSRA, ADSC); /*start conversion*/
	while(BIT_IS_CLEAR(ADCSRA, ADIF)); /*remain in loop till ADIF is 1 */
	SET_BIT(ADCSRA, ADIF); /*Clear bit by putting 1 in it*/
	return ADC;

}

#endif
