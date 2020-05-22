/*********************************************************************************************************************************
 *  Filename: usart.h
 *
 *  Description: header file for usart driver
 *
 *  Created on: Jan 04, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/

#ifndef USART_H_
#define USART_H_
#include "../../common/std_types.h"
#include "../../common/micro_config.h"
#include "../../common/common_macros.h"

#define BAUD_PRESCALE(BAUD, DIVISOR) (((F_CPU)/(DIVISOR*BAUD))-1)
#define USART_FRAME_ERROR 0xFFFF


/*********************************************************************************************************************************
 *                       									Type definitions                                                                                      *
 *********************************************************************************************************************************/
typedef enum{
	USART_SYNCH_RATE = 0, USART_NORMAL_RATE = 0, USART_DOUBLE_RATE /*double = 1*/
}USART_Rate;

typedef enum{
	USART_INT_DISABLED, USART_DATA_REG_EMPTY_ENABLE, USART_TX_ENABLE, USART_TX_AND_DATA_REG_EMPTY,  USART_RX_ENABLE,
	USART_RX_AND_DATA_REG_EMPTY, USART_TX_AND_RX,  USART_TX_RX_DATA_REG_EMPTY
}USART_Interrupt; /*changed place for easier insertion in interrupt register*/

typedef enum{
	USART_FIVE, USART_SIX, USART_SEVEN, USART_EIGHT, USART_NINE = 7
}USART_CharSize;

typedef enum{
	USART_ASYNCH, USART_SYNCH
}USART_Mode;

typedef enum{
	USART_PAR_DISABLED, USART_EVEN = 2, USART_ODD
}USART_Parity;

typedef enum{
	USART_ONE, USART_TWO
}USART_StopBits;
typedef enum{
	USART_POL_ASYNCH = 0, USART_RISING = 0, USART_FALLING
}USART_Polarity;

typedef struct{
	USART_Rate rate;
	USART_Interrupt interrupt;
	USART_CharSize charSize;
	USART_Mode mode;
	USART_Parity parity;
	USART_StopBits stopBits;
	USART_Polarity polarity;
	uint32 baud;
}USART_ConfigType;

/*********************************************************************************************************************************
 *                       									Function Prototypes                                                                                     *
 *********************************************************************************************************************************/
void USART_Init(USART_ConfigType *config_Ptr);
void USART_sendFrame(const uint16 a_data);
uint16 USART_receiveFrame(void);
void USART_sendString(const uint8 *Str);
void USART_receiveString(uint8 *Str);

#endif /* USART_H_ */
