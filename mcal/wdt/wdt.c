 /*********************************************************************************************************************************
 *
 * Module: Watchdog Timer
 *
 * File Name: wdt.c
 *
 * Description: source file for WDT driver
 *
 * Author: Shabrawy
 *
 *********************************************************************************************************************************/
#include "wdt.h"
/*********************************************************************************************************************************
 *              							Function Definitions                                 													 *
 *********************************************************************************************************************************/
/*Enable WDT and set timeout period*/
void WDT_on(WDT_timeout a_timeout){
	SET_BIT(WDTCR, WDE);
	WDTCR = (WDTCR & 0xF8)|(a_timeout);
}

/*disable WDT*/
void WDT_off(void){
	WDTCR = (1<<WDTOE)|(1<<WDE);
	_delay_us(4); //4 micro sec since 1mhz freq and need 4clock to set wde to 0
	WDTCR =0x00;

}
