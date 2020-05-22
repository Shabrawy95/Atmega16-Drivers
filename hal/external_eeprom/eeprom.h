/*********************************************************************************************************************************
 *  Filename: eeprom.h
 *
 *  Description: header file for eeprom driver
 *
 *  Created on: Jan 24, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/



#ifndef EEPROM_H_
#define EEPROM_H_

#include "../../common/std_types.h"
#define E2ROM_ERROR 0
#define E2ROM_SUCCESS 1

/*********************************************************************************************************************************
 *                       									Function Prototypes                                                                                     *
 *********************************************************************************************************************************/
void EEPROM_init();
uint8 EEPROM_writeByte(uint16 u16addr, uint8 a_data);
uint8 EEPROM_writeData(uint16 u16addr, uint8* a_data, uint8 a_length);
uint8 EEPROM_readByte(uint16 u16addr, uint8* Ptr_data);
uint8 EEPROM_readData(uint16 u16addr, uint8* Ptr_data, uint8 a_length);


#endif /* EEPROM_H_ */
