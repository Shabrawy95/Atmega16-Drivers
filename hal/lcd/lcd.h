/*********************************************************************************************************************************
 *  Filename: lcd.h
 *
 *  Description: header file for LCD driver
 *
 *  Created on: Dec 27, 2019
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/
#ifndef LCD_H_
#define LCD_H_
#include "../../common/std_types.h"
#include "../../common/micro_config.h"
#include "../../common/common_macros.h"

/*********************************************************************************************************************************
 *                      Preprocessor Macros                                    													 *
 *********************************************************************************************************************************/

/* LCD HW pins */
#define RS PB0
#define RW PB1
#define E PB2

/*Data bit mode configuration 4 or 8*/
#define DATA_BITS_MODE 4

#if (DATA_BITS_MODE == 4)
#define LCD_UPPER_PORT_PINS
#endif

#undef LCD_UPPER_PORT_PINS /*Use lower pins P0 to P3/

/*LCD port config */
#define LCD_CTRL_PORT_DIR DDRB
#define LCD_CTRL_PORT PORTB

#define LCD_DATA_PORT_DIR DDRA
#define LCD_DATA_PORT PORTA

/*LCD Commands*/
#define CLEAR_COMMAND 0x01
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define TWO_LINE_LCD_FOUR_BIT_MODE 0x28
#define FOUR_BIT_MODE 0x02
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80

/*********************************************************************************************************************************
 *                     Function prototypes                                  													 *
 *********************************************************************************************************************************/

void LCD_init();
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char* str);
void LCD_clearScreen(void);
void LCD_goToRowColumn(uint8 row, uint8 col);
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *str);
void LCD_integerToString(int data);

#endif /* LCD_H_ */
