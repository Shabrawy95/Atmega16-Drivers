/*********************************************************************************************************************************
 *  Filename: keypad.h
 *
 *  Description: header file for keypad driver
 *
 *  Created on: Dec 27, 2019
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/
#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "../../common/std_types.h"
#include "../../common/micro_config.h"
#include "../../common/common_macros.h"

/*********************************************************************************************************************************
 *                      Preprocessor Macros                                    													 *
 *********************************************************************************************************************************/

/* Keypad configurations for number of rows and columns */
#define N_COL 3
#define N_ROW 4

/*keypad port config */
#define KEYPAD_PORT_OUT PORTC
#define KEYPAD_PORT_IN PINC
#define KEYPAD_PORT_DIR DDRC

/*********************************************************************************************************************************
 *                     Function prototypes                                  													 *
 *********************************************************************************************************************************/

/*function for getting pressed key*/
uint8 Keypad_getPressedKey(void);


#endif /* LCD_H_ */
