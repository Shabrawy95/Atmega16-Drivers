/*********************************************************************************************************************************
 *  Filename: ADC.h
 *
 *  Description: header file for ADC driver
 *
 *  Created on: Jan 04, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/

#ifndef ADC_H_
#define ADC_H_
#include "../../common/std_types.h"
#include "../../common/micro_config.h"
#include "../../common/common_macros.h"


#define ADC_INTERRUPT /*to enable INTERRUPT for polling leave it empty*/
#define AUTO_TRIGGER
#undef AUTO_TRIGGER
/*********************************************************************************************************************************
 *                       									External Variables                                                                                      *
 *********************************************************************************************************************************/
#ifdef ADC_INTERRUPT
extern volatile uint16 g_adcResult; /*used in case of interrupt only*/
#endif


/*********************************************************************************************************************************
 *                       									Type definitions                                                                                      *
 *********************************************************************************************************************************/
typedef enum { /*not necessary to put ADC_ prefix since no ref voltage anywhere else*/
	AREF, AVCC, INTERNAL_REF=3
}ADC_Ref;

typedef enum {
	ADC0, ADC1, ADC2, ADC3, ADC4, ADC5, ADC6, ADC7
}ADC_Channel;

typedef enum{
	ADC_F_CPU_2=0, ADC_F_CPU_4=2, ADC_F_CPU_8, ADC_F_CPU_16, ADC_F_CPU_32,
	ADC_F_CPU_64, ADC_F_CPU_128

}ADC_Clock;

/*AT_ for auto trigger*/
typedef enum{
	AT_FREE, AT_COMP, AT_INT_ZERO, AT_T0_COMP, AT_TO_OVF, AT_T1_COMPB, AT_T1_OVF, AT_T1_CAPTURE
}ADC_TriggerSrc;

typedef struct {
	ADC_Ref ref;
	ADC_Channel channel;
	ADC_Clock clock;
	ADC_TriggerSrc trigger_select;
}ADC_Config;


/*********************************************************************************************************************************
 *                       									Function Prototypes                                                                                     *
 *********************************************************************************************************************************/


void ADC_Init(ADC_Config* a_Config);

#ifdef ADC_INTERRUPT

void ADC_startConversion(void);


#else

uint16 ADC_readValue(void);

#endif
#endif /* ADC_H_ */
