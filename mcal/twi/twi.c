/*********************************************************************************************************************************
 *  Filename: i2c.c
 *
 *  Description: header file for TWI driver
 *
 *  Created on: Jan 24, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/
#include "math.h"
#include "twi.h"

/*********************************************************************************************************************************
 *                       									ISRS
 ********************************************************************************************************************************/
ISR(TWI_vect){

}

/*********************************************************************************************************************************
 *                       									Function Definitions                                                                                     *
 *********************************************************************************************************************************/
void TWI_Init(TWI_ConfigType* config_Ptr){
	TWBR = BITRATE(config_Ptr->scl_freq, config_Ptr->prescale); /*setting freqeunecy*/
	TWSR = ((config_Ptr->prescale)&0x03); /*TWPS1:0 bits*/
	_delay_ms(1000);
	TWAR = ((config_Ptr->address)<<1)|(config_Ptr->gen_call);
	TWCR = (1<<TWEN)|((config_Ptr->interrupt)); /*enabling or disabling interrupt*/
}

void TWI_Start(void){
	/*Clearing TWINT flag, sending start bit, enabling module*/
	TWCR = (1<<TWSTA)|(1<<TWINT)|(1<<TWEN);
	while(BIT_IS_CLEAR(TWCR, TWINT)); /*wait till start is sent successfuilly i.e TWINT = 1*/

}

void TWI_Stop(void){
	/*clear flag, send sotp bit, enable module*/
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	/*no need for polling flag as I'm leaving bus no action required after then*/
}

void TWI_Listen(void){
	/*used in case of slave*/
	while(BIT_IS_CLEAR(TWCR, TWINT)); /*slave waiting to be addressed */

}


void TWI_write(uint8 a_data){
	TWDR = a_data;
	TWCR  = (1<<TWEN)|(1<<TWINT); /*clearing flag before sending data*/
	while(BIT_IS_CLEAR(TWCR, TWINT)); /*wait till data is sent successfuilly i.e TWINT = 1*/

}

uint8 TWI_Read_With_Ack(void){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA); /*clear flag before reading, enable acknowledgment on receiving*/
	while(BIT_IS_CLEAR(TWCR, TWINT));/*wait till data has been received*/
	return TWDR;
}

uint8 TWI_Read_With_Nack(void){
	TWCR = (1<<TWINT)|(1<<TWEN); /*clear flag before reading, no ack on receiving*/
	while(BIT_IS_CLEAR(TWCR, TWINT));/*wait till data has been received*/
	return TWDR;
}

uint8 TWI_Get_Status(void){
	return (TWSR & 0xF8); /*F8 1111 1000 to get TWS7:3*/
}
