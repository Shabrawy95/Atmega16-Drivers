/*********************************************************************************************************************************
 *  Filename: spi.h
 *
 *  Description: header file for spi driver
 *
 *  Created on: Jan 04, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/

#ifndef SPI_H_
#define SPI_H_
#include "../../common/std_types.h"
#include "../../common/micro_config.h"
#include "../../common/common_macros.h"

//#define SPI_INTERRUPT /*in case of interrupt only for polling leave it empty*/
#define SPI_DATA_PORT DDRB
#define SPI_FRAME_ERROR 0xFF



/*********************************************************************************************************************************
 *                       									Type definitions                                                                                      *
 *********************************************************************************************************************************/

typedef enum{
	SPI_INT_DISABLED, SPI_INT_ENABLED
}SPI_Interrupt;

typedef enum{
	SPI_MSB_FIRST, SPI_LSB_FIRST
}SPI_DataOrder;


/*MODE 0: CPOL 0 CPHA 0
 * MODE 1: CPOL 0 CPHA 1
 * MODE 2: CPOL 1 CPHA 0
 * MODE 3: CPOL 1 CPHA 1 */
typedef enum{
	SPI_MODE_0, SPI_MODE_1, SPI_MODE_2, SPI_MODE_3
}SPI_MODE;


typedef enum{
	SPI_F_CPU_4, SPI_F_CPU_16, SPI_F_CPU_64, SPI_F_CPU_128, SPI_F_CPU_2,
	SPI_F_CPU_8, SPI_F_CPU_32, SPI_F_CPU_64_2X /*2x for getting FCPU/64 using double speed mode*/

}SPI_Clock;

typedef struct{
	SPI_Interrupt interrupt;
	SPI_Clock clock;
	SPI_MODE mode;
	SPI_DataOrder dataOrder;

}SPI_ConfigType;

/*********************************************************************************************************************************
 *                       									Function Prototypes                                                                                     *
 *********************************************************************************************************************************/
void SPI_initMaster(SPI_ConfigType *config_Ptr);
void SPI_initSlave(SPI_ConfigType *config_Ptr);
void SPI_sendByte(const uint8 a_data);
void SPI_sendString(const uint8 *Str);
uint8 SPI_receiveByte(void);
void SPI_receiveString(uint8 *Str);



#endif /* SPI_H_ */
