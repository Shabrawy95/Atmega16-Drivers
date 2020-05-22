/*********************************************************************************************************************************
 *  Filename: spi.c
 *
 *  Description: header file for spi driver
 *
 *  Created on: Jan 04, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/
#include "spi.h"

/*********************************************************************************************************************************
 *                       									ISRS
 ********************************************************************************************************************************/

ISR(SPI_STC_vect){


}


/*********************************************************************************************************************************
 *                       									Function Definitions                                                                                     *
 *********************************************************************************************************************************/
/*function */

/*function to initialize SPI clock, Dataorder, mode, interrupt*/

void SPI_initMaster(SPI_ConfigType *config_Ptr){
	SPI_DATA_PORT |= (1<<PB4)|(1<<PB5)|(1<<PB7); /*SS, MOSI, SCK all output*/
	SPI_DATA_PORT &=~ (1<<PB6); /*MISO input*/
	SPCR = (1<<SPE)|(1<<MSTR)|((config_Ptr->interrupt)<<7)|((config_Ptr->dataOrder)<<5)|(((config_Ptr->mode)&0x03)<<2)\
			|((config_Ptr->clock)&0x03);
	/*(((config_Ptr->mode)&0x03)<<2) to get CPOL CPHA bits
	 * ((config_Ptr->mode)&0x03) to get SPR 0:1 bits*/
	SPSR |= (((config_Ptr->clock)&0x04)>>2); /*to get SPI2X bit*/
}
void SPI_initSlave(SPI_ConfigType *config_Ptr){
	SPI_DATA_PORT &=~ ((1<<PB4)|(1<<PB5)|(1<<PB7));/*SS, MOSI, SCK all input*/
	SPI_DATA_PORT |= (1<<PB6);/*MISO output*/
	SPCR = (1<<SPE)|((config_Ptr->interrupt)<<7)|((config_Ptr->dataOrder)<<5)|(((config_Ptr->mode)&0x03)<<2)\
			|((config_Ptr->clock)&0x03);
	/*(((config_Ptr->mode)&0x03)<<2) to get CPOL CPHA bits
	 * ((config_Ptr->mode)&0x03) to get SPR 0:1 bits
	 * MSTR = 0 since slave*/
	SPSR |= (((config_Ptr->clock)&0x04)>>2); /*to get SPI2X bit*/
}

void SPI_sendByte(const uint8 a_data){
	SPDR = a_data; /*SPIF is cleared by first reading SPSR while SPIF is set then accessing SPDR so we did that but here in reverse way*/
	while(BIT_IS_CLEAR(SPSR, SPIF));
}



void SPI_sendString(const uint8 *Str){
	while(*Str != '\0'){
		SPI_sendByte(*Str);
		Str++;
	}
}
uint8 SPI_receiveByte(void){
	if(SPSR & (1<<WCOL)){
		return SPI_FRAME_ERROR;
	}
	while(BIT_IS_CLEAR(SPSR, SPIF));/*SPIF is cleared by first reading SPSR while SPIF is set then accessing SPDR so we did that */
	return SPDR;
}

void SPI_receiveString(uint8 *Str){
	*Str = SPI_receiveByte();
	while(*Str != '#'){
		Str++;
		*Str = SPI_receiveByte();
	}
	*Str = '\0';
}
