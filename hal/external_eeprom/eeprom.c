/*********************************************************************************************************************************
 *  Filename: eeprom.c
 *
 *  Description: source file for eeprom driver
 *
 *  Created on: Jan 24, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/


/*********************************************************************************************************************************
 *                       									Global Variables
 *********************************************************************************************************************************/

/*********************************************************************************************************************************
 *                       									Function definitions                                                                                     *
 *********************************************************************************************************************************/

#include"../../mcal/twi/twi.h"
#include "eeprom.h"

void EEPROM_init(void){
	TWI_ConfigType config = {TWI_INT_DISABLED, TWI_PRESCALE_1, TWI_GC_DISABLED, 400000, 0x01};
	TWI_Init(&config);
}
uint8 EEPROM_writeByte(uint16 u16addr, uint8 a_data){
	TWI_Start();
	if(TWI_Get_Status() != TW_START){
		return E2ROM_ERROR;
	}
	/*get memory locaiton 1010 which is A and last 3 bits of data put in LSB of memory address*/
	TWI_write((uint8)((0xA0)|((u16addr&0x0700)>>7)));
	if(TWI_Get_Status() != TW_MT_SLA_W_ACK){
		return E2ROM_ERROR;

	}

	TWI_write((uint8)u16addr); /*address of memory location*/
	if(TWI_Get_Status() != TW_MT_DATA_ACK){
		return E2ROM_ERROR;
	}
	TWI_write(a_data); /*address of memory location*/
	if(TWI_Get_Status() != TW_MT_DATA_ACK){
		return E2ROM_ERROR;
	}
	TWI_Stop(); /*send stop bit*/
	return E2ROM_SUCCESS;
}

/*function to write multiple bytes to eeprom, number of bytes is passed as parameter*/
uint8 EEPROM_writeData(uint16 u16addr, uint8* Ptr_data, uint8 a_length){
	uint8 i = 0;
	TWI_Start();
	if(TWI_Get_Status() != TW_START){
		return E2ROM_ERROR;
	}
	/*get memory locaiton 1010 which is A and last 3 bits of data put in LSB of memory address*/
	TWI_write((uint8)((0xA0)|((u16addr&0x0700)>>7)));
	if(TWI_Get_Status() != TW_MT_SLA_W_ACK){
		return E2ROM_ERROR;

	}

	TWI_write((uint8)u16addr); /*address of memory location*/
	if(TWI_Get_Status() != TW_MT_DATA_ACK){
		return E2ROM_ERROR;
	}
	for(i = 0; i < a_length; i++){
		TWI_write(*(Ptr_data+i)); /*address of memory location*/
		if(TWI_Get_Status() != TW_MT_DATA_ACK){
			return E2ROM_ERROR;
		}
	}

	TWI_Stop(); /*send stop bit*/
	return E2ROM_SUCCESS;
}


uint8 EEPROM_readByte(uint16 u16addr, uint8* Ptr_data){
	TWI_Start();
	if(TWI_Get_Status() != TW_START){
		return E2ROM_ERROR;
	}
	/*get memory locaiton 1010 which is A and last 3 bits of data put in LSB of memory address*/
	TWI_write((uint8)(0xA0|((u16addr&0x0700)>>7)));
	if(TWI_Get_Status() != TW_MT_SLA_W_ACK){
		return E2ROM_ERROR;
	}

	TWI_write((uint8)u16addr); /*address of memory location*/
	if(TWI_Get_Status() != TW_MT_DATA_ACK){
		return E2ROM_ERROR;
	}
	TWI_Start(); /*repeated start*/
	if(TWI_Get_Status() != TW_REP_START){
		return E2ROM_ERROR;
	}
	/*get memory locaiton 1010 which is A and last 3 bits of data put in LSB of memory address*/
	TWI_write((uint8)(0xA1|((u16addr&0x0700)>>7))); /*A1 1010 0001 for read*/
	if(TWI_Get_Status() != TW_MT_SLA_R_ACK){
		return E2ROM_ERROR;
	}
	*Ptr_data = TWI_Read_With_Nack();
	if(TWI_Get_Status() != TW_MR_DATA_NACK){
		return E2ROM_ERROR;
	}
	TWI_Stop(); /*send stop bit*/
	return E2ROM_SUCCESS;
}


uint8 EEPROM_readData(uint16 u16addr, uint8* Ptr_data, uint8 a_length){
	uint8 i = 0;
	TWI_Start();
	if(TWI_Get_Status() != TW_START){
		return E2ROM_ERROR;
	}
	/*get memory locaiton 1010 which is A and last 3 bits of data put in LSB of memory address*/
	TWI_write((uint8)(0xA0|((u16addr&0x0700)>>7)));
	if(TWI_Get_Status() != TW_MT_SLA_W_ACK){
		return E2ROM_ERROR;
	}

	TWI_write((uint8)u16addr); /*address of memory location*/
	if(TWI_Get_Status() != TW_MT_DATA_ACK){
		return E2ROM_ERROR;
	}
	TWI_Start(); /*repeated start*/
	if(TWI_Get_Status() != TW_REP_START){
		return E2ROM_ERROR;
	}
	/*get memory locaiton 1010 which is A and last 3 bits of data put in LSB of memory address*/
	TWI_write((uint8)(0xA1|((u16addr&0x0700)>>7))); /*A1 1010 0001 for read*/
	if(TWI_Get_Status() != TW_MT_SLA_R_ACK){
		return E2ROM_ERROR;
	}
	for(i = 0; i < a_length-1; i++){/*read till before last element of array*/
		*(Ptr_data+i) = TWI_Read_With_Ack();
		if(TWI_Get_Status() != TW_MR_DATA_ACK){
			return E2ROM_ERROR;
		}

	}
	*(Ptr_data+i) = TWI_Read_With_Nack(); /*last byte i = index of last element of array master sends nack*/
	if(TWI_Get_Status() != TW_MR_DATA_NACK){
		return E2ROM_ERROR;
	}


	TWI_Stop(); /*send stop bit*/
	return E2ROM_SUCCESS;
}

