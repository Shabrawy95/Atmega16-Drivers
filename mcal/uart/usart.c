/*********************************************************************************************************************************
 *  Filename: usart.c
 *
 *  Description: header file for usart driver
 *
 *  Created on: Jan 04, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/
#include "usart.h"

/*********************************************************************************************************************************
 *                       									Global Variables
 *********************************************************************************************************************************/


/*********************************************************************************************************************************
 *                       									ISRS
 ********************************************************************************************************************************/
static uint8 g_ninthBit; /*to know if we're using 9 bit mode*/

ISR(USART_RXC_vect){

}
ISR(USART_TXC_vect){

}
ISR(USART_UDRE_vect){

}

/*********************************************************************************************************************************
 *                       									Function Definitions                                                                                     *
 *********************************************************************************************************************************/
/*function */

/*function to initialize rate, usart interrupts, character size, mode, parity config, stop bits
 * clock polarity and baud*/

void USART_Init(USART_ConfigType *config_Ptr){
	g_ninthBit = config_Ptr->charSize;
	UCSRA = (UCSRA & 0xFD)|((config_Ptr->rate)<<1);/*FD 1111 1101 to zero out u2x bit*/
	UCSRB = (UCSRB & 0x1F)|((config_Ptr->interrupt)<<5); /*1F = 0001 1111 to zero interrupt enable bits*/
	UCSRB = (UCSRB & 0xE3)|(1<<TXEN)|(1<<RXEN)|(((config_Ptr->charSize)&0x04)<<2);
	/* 0x E3 1110 0011 to zero out txen rxen ucsz2
	 * 04 0000 0100 to get third bit in size and shift left by 2 to put in ucsz2*/
	UCSRC = (1<<URSEL)|((config_Ptr->mode)<<6)|((config_Ptr->parity)<<4)|((config_Ptr->stopBits)<<3)\
			|(((config_Ptr->charSize)&0x03)<<1)|(config_Ptr->polarity);
	if((config_Ptr->rate) == USART_SYNCH_RATE){
		UBRRH = BAUD_PRESCALE((config_Ptr->baud), 2)>>8;
		UBRRL = BAUD_PRESCALE((config_Ptr->baud), 2);
	}
	else if((config_Ptr->rate) == USART_NORMAL_RATE){
		UBRRH = BAUD_PRESCALE((config_Ptr->baud), 16)>>8;
		UBRRL = BAUD_PRESCALE((config_Ptr->baud), 16);
	}
	else if((config_Ptr->rate) == USART_DOUBLE_RATE){
		UBRRH = BAUD_PRESCALE((config_Ptr->baud), 8)>>8;
		UBRRL = BAUD_PRESCALE((config_Ptr->baud), 8);
	}

}



void USART_sendFrame(const uint16 a_data){/*uint16 for 9 bit data*/
	while(BIT_IS_CLEAR(UCSRA, UDRE)); /*out of loop when UDR is empty is 1 i.e data has been transmitted*/
	if(g_ninthBit == USART_NINE){
		UCSRB =(UCSRB & 0xFE)|(a_data&0x0100); /*FE to zero out TXB8 bit
		0x0100 > 0000 0001 0000 0000 to get 9th bit*/
	}
	UDR = a_data; /*UDRIE flag cleared automatically because register is no longer empty*/

	/*UDR = a_data;
	while(BIT_IS_CLEAR(UCSRA, TXC));
	SET_BIT(UCSRA, TXC); */

}


uint16 USART_receiveFrame(void){ /*uint16 for 9 bit data*/
	while(BIT_IS_CLEAR(UCSRA, RXC)); /*remain in loop ill there is daata in rx buffer*/

	if((UCSRA & (1<<FE))||(UCSRA & (1<<DOR))||((UCSRA & (1<<PE))&&(UCSRC & 0x30))){ /*error exists*/
		return USART_FRAME_ERROR; /*error*/

	}

	if(g_ninthBit == USART_NINE){

		return (((UCSRB & 0x02)<<7)|UDR); /*0x02 0000 0010 to get RXB8 pin then shift and or with 7 bit udr register*/

	}


	return UDR; /*RXC is cleared by reading UDR automatically(for next transmission*/

}




void USART_sendString(const uint8 *Str){ /*for both polled and interrupt driven*/
	while(*Str != '\0'){
		USART_sendFrame(*Str);
		Str++;
	}
}





void USART_receiveString(uint8 *Str){
	*Str = USART_receiveFrame();
	while(*Str != '#'){
		Str++;
		*Str = (uint8)USART_receiveFrame();
	}
	*Str = '\0';
}

void USART_deInit(void){
	UCSRA = UCSRB = UCSRC = 0; /*de initialize USART check if UCSRA can be omitted*/
}
