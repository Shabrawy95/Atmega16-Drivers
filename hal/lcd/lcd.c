/*********************************************************************************************************************************
 *  Filename: lcd.c
 *
 *  Description: source file for lcd driver
 *
 *  Created on: Dec 27, 2019
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/
#include "lcd.h"

/*********************************************************************************************************************************
 *                     Function definition                                  													 *
 *********************************************************************************************************************************/

void LCD_init(void){
	LCD_CTRL_PORT_DIR |=(1<<RS)|(1<<RW)|(1<<E);/*Configure pins as o/p*/
#if (DATA_BITS_MODE == 4)
	#ifdef LCD_UPPER_PORT_PINS
		LCD_DATA_PORT_DIR |=0xF0; /*configure higher 4 bits of data port as output*/
	#else
		LCD_DATA_PORT_DIR |=0x0F;/*configure lower 4 bits of data port as output*/
	#endif
	LCD_sendCommand(FOUR_BIT_MODE); /*initialize LCD in 4 bit mode*/
	LCD_sendCommand(TWO_LINE_LCD_FOUR_BIT_MODE);/*configure 2 line, 8bit mode*/
#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT_DIR =0xFF;/*configure data port as o/p*/
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE);/*configure 2 line, 8bit mode*/
#endif
	LCD_sendCommand(CURSOR_OFF);/*cursor off*/
	LCD_sendCommand(CLEAR_COMMAND);/* clear lcd at the beginning*/

}

void LCD_sendCommand(uint8 command){
	CLEAR_BIT(LCD_CTRL_PORT, RS);/* instruction mode RS =0*/
	CLEAR_BIT(LCD_CTRL_PORT, RW); /*Write mode */
	_delay_ms(1);/* delay for processing Tas = 50ns */
	SET_BIT(LCD_CTRL_PORT, E);/* Enable LCD E=1 */
	_delay_ms(1);/* delay for processing Tpw - Tdws = 190ns */
#if (DATA_BITS_MODE == 4)
	#ifdef LCD_UPPER_PORT_PINS
		LCD_DATA_PORT = (LCD_DATA_PORT&0x0F)|(command&0xF0);/* out the higher nibble of command to the data bus D4 --> D7 */
	#else
		LCD_DATA_PORT = (LCD_DATA_PORT&0xF0)|((command&0xF0)>>4);/* out the higher nibble of to the data bus D4 --> D7 */
	#endif
	_delay_ms(1);/* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT, E);/* disable LCD E=0 */
	_delay_ms(1);/* delay for processing Th = 13ns */
	SET_BIT(LCD_CTRL_PORT, E);
	_delay_ms(1);/* delay for processing Tpw - Tdws = 190ns */
	#ifdef LCD_UPPER_PORT_PINS
		LCD_DATA_PORT = (LCD_DATA_PORT&0x0F)|((command&0x0F)<<4);/* out the lower nibble of command to the data bus D4 --> D7 */
	#else
		LCD_DATA_PORT = (LCD_DATA_PORT&0xF0)|((command&0x0F));/* out lower nibble of command command to the data bus D4 --> D7 */
	#endif
		_delay_ms(1);/* delay for processing Tdsw = 100ns */
		CLEAR_BIT(LCD_CTRL_PORT, E);
		_delay_ms(1);/* delay for processing Th = 13ns */
#elif 	(DATA_BITS_MODE == 8)
		LCD_DATA_PORT = command;
		_delay_ms(1);/* delay for processing Tdsw = 100ns */
		CLEAR_BIT(LCD_CTRL_PORT, E);
		_delay_ms(1);/* delay for processing Th = 13ns */
#endif

}
void LCD_displayCharacter(uint8 data){
	SET_BIT(LCD_CTRL_PORT, RS);/* Data mode RS =1*/
	CLEAR_BIT(LCD_CTRL_PORT, RW); /*Write mode */
	_delay_ms(1);/* delay for processing Tas = 50ns */
	SET_BIT(LCD_CTRL_PORT, E);/* Enable LCD E=1 */
	_delay_ms(1);/* delay for processing Tpw - Tdws = 190ns */
#if (DATA_BITS_MODE == 4)
	#ifdef LCD_UPPER_PORT_PINS
		LCD_DATA_PORT = (LCD_DATA_PORT&0x0F)|(data&0xF0);/* out the higher nibble of data to the data bus D4 --> D7 */
	#else
		LCD_DATA_PORT = (LCD_DATA_PORT&0xF0)|((data&0xF0)>>4);/* out the higher nibble of data to the data bus D4 --> D7 */
	#endif
	_delay_ms(1);/* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT, E);/* disable LCD E=0 */
	_delay_ms(1);/* delay for processing Th = 13ns */
	SET_BIT(LCD_CTRL_PORT, E);
	_delay_ms(1);/* delay for processing Tpw - Tdws = 190ns */
	#ifdef LCD_UPPER_PORT_PINS
		LCD_DATA_PORT = (LCD_DATA_PORT&0x0F)|((data&0x0F)<<4);/* out the lower nibble of data to the data bus D4 --> D7 */
	#else
		LCD_DATA_PORT = (LCD_DATA_PORT&0xF0)|((data&0x0F));/* out lower nibble of cdata to the data bus D4 --> D7 */
	#endif
		_delay_ms(1);/* delay for processing Tdsw = 100ns */
		CLEAR_BIT(LCD_CTRL_PORT, E);
		_delay_ms(1);/* delay for processing Th = 13ns */
#elif 	(DATA_BITS_MODE == 8)
		LCD_DATA_PORT = data;
		_delay_ms(1);/* delay for processing Tdsw = 100ns */
		CLEAR_BIT(LCD_CTRL_PORT, E);
		_delay_ms(1);/* delay for processing Th = 13ns */
#endif
}

void LCD_displayString(const char* str){
	while (*str != '\0'){
		LCD_displayCharacter(*str);
		str++;
	}

}

void  LCD_clearScreen(void){
	LCD_sendCommand(CLEAR_COMMAND); /*clear display*/
}
void LCD_goToRowColumn(uint8 row, uint8 col){
	uint8 address;
	/*calculate address*/
	switch(row){
	case 0: address = col;
	break;
	case 1: address = 0x40 +col;
	break;
	case 2: address = 0x10 +col;
	break;
	case 3: address = 0x50 +col;
	break;
	}
	LCD_sendCommand(address|SET_CURSOR_LOCATION);
}
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *str){
	LCD_goToRowColumn(row, col); /*go to required position then display string*/
	LCD_displayString(str);
}
void LCD_integerToString(int data){
	char buff[16];
	itoa(data, buff, 10); /*convert number to ascii*/
	LCD_displayString(buff); /*display number after conversion*/
}

