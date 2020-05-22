/*********************************************************************************************************************************
 *  Filename: keypad.c
 *
 *  Description: source file for keypad driver
 *
 *  Created on: Dec 27, 2019
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/
#include "keypad.h"

/*********************************************************************************************************************************
 *                     Function prototypes                                  													 *
 *********************************************************************************************************************************/

#if (N_COL == 4)
/*function resposnsible for mapping the button in keypad to its corresponding number in proteus for keypad 4x4 */
static uint8 Keypad_4x4_adjustSwitchNumber(uint8 button_num);
#endif

#if (N_COL == 3)
/*function resposnsible for mapping the button in keypad to its corresponding number in proteus for keypad 4x3 */
static uint8 Keypad_4x3_adjustSwitchNumber(uint8 button_num);
#endif


/*********************************************************************************************************************************
 *                     Function definition                                  													 *
 *********************************************************************************************************************************/

uint8 Keypad_getPressedKey(void){
	uint8 row, col;
	while(1){
		for(col=0; col<N_COL; col++){
			/*each time only one column is output and the other are input */
			KEYPAD_PORT_DIR = (0b00010000<<col);
			/*clear output for this column and also enable internal pull up for rows*/
			KEYPAD_PORT_OUT = (~(0b00010000<<col));
			for(row=0; row<N_ROW; row++){
				if(BIT_IS_CLEAR(KEYPAD_PORT_IN, row)){
					#if (N_COL == 4)
						return Keypad_4x4_adjustSwitchNumber((row*N_COL) + col +1);
					#elif (N_COL == 3)
						return Keypad_4x3_adjustSwitchNumber((row*N_COL) + col +1);
					#endif
				}
			}

		}
	}}

#if (N_COL == 4)
	static uint8 Keypad_4x4_adjustSwitchNumber(uint8 button_num){
		switch (button_num){
		case 1: return 7;
				   	break;
		case 2: return 8;
				     break;

		case 3: return 9;
					break;
		case 4: return '%';
					break;
		case 5: return 4;
				     break;

		case 6: return 5;
					break;
		case 7: return 6;
				   	break;
		case 8: return '*';
				     break;

		case 9: return 1;
					break;
		case 10: return 2;
					break;
		case 11: return 3;
				     break;

		case 12: return '-';
					break;
		case 13: return 13;
				     break;

		case 14: return 0;
					break;
		case 15: return '=';
				     break;

		case 16: return '+';
					break;
		default: return button_num;
		}
	}
#elif (N_COL == 3)
	static uint8 Keypad_4x3_adjustSwitchNumber(uint8 button_num){
		switch (button_num){
		case 10 :return '*';
				break;
		case 11 :return 0;
				break;

		case 12 :return '#';
				break;
		default: return button_num;
		}
	}
#endif



