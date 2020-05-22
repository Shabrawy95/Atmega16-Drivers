/*********************************************************************************************************************************
 *  Filename: usart.h
 *
 *  Description: header file for TWI driver
 *
 *  Created on: Jan 24, 2020
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/

#ifndef TWI_H_
#define TWI_H_
#include "../../common/std_types.h"
#include "../../common/micro_config.h"
#include "../../common/common_macros.h"
//#define BITRATE(SCL_FREQ, PRESCALE) (uint8)(((F_CPU)-(16*SCL_FREQ))/(2*SCL_FREQ*pow(4, PRESCALE)))
#define BITRATE(SCL_FREQ, PRESCALE) (uint8)(((F_CPU)-(16*SCL_FREQ))/(2*SCL_FREQ*(1<<(2*PRESCALE))))
/*(1<<2*prescaler) = 4 power prescaler
 * 0000 0001 <<2*(0) = 1 which is equal to 4 power 0
 * 0000 0001 <<2(1) = 4 which is equal to 4 power 1
 * 0000 0001 <<2(2) -> 0001 0000 which is equal to 16 i.e 4 power 2
 * 0000 0001 <<2(3) -> 0100 0000 which is equal to 64 which is 4 power 3*/
#define TWI_WRITE 0
#define TWI_READ 1

/* I2C Status Bits in the TWSR Register, MASTER MODE*/
#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_W_NACK  0x20 // Master transmit ( slave address + Write request ) to slave + Nack received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MT_DATA_NACK   0x30 // Master transmit data and NACK has been received from Slave.
#define TW_MASTER_LOST_ARBITRATION 0x38 /*Master loses arbitration and becomes slave*/
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_SLA_R_NACK  0x48 // Master transmit ( slave address + Read request ) to slave + Nack received from slave
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave

/* I2C Status Bits in the TWSR Register, SLAVE RECEIVER MODE*/

#define TW_SLAVER_SLA_W_ACK 0x60 /*slave received its own address, write mode, and return acked*/
#define TW_SLAVER_LOSES_ARB_THEN_SLA_W_ACK 0x68 /*slave was master then lost arbitration and imeddiately was adressed in write mode*/
#define TW_SLAVER_GEN_CALL_ACK 0x70 /*slave acknowledged general call*/
#define TW_SLAVER_LOSES_ARB_THEN_GEN_CALL_ACK 0x78 /*slave was master then lost arbitration and rpelied with ack*/
#define TW_SLAVER_DATA_ACK 0x80 /*slave received data and sent ack to master*/
#define TW_SLAVER_DATA_NACK 0x88 /*slave received data but didn't send ack to master*/
#define TW_SLAVER_DATA_GEN_CALL_ACK 0x90 /*slave received data after general call and sent ack*/
#define TW_SLAVER_DATA_GEN_CALL_NACK 0x98/*slave received data after general call and but doesn't ack*/
#define TWI_SLAVER_STOP_OR_REP_START 0xA0

/* I2C Status Bits in the TWSR Register, SLAVE Transmitter MODE*/

#define TW_SLAVET_SLA_R_ACK 0xA8 /*slave received its own address, read mode, and return acked*/
#define TW_SLAVET_LOSES_ARB_THEN_SLA_R_ACK 0xB0 /*slave was master then lost arbitration and imeddiately was adressed in read mode*/
#define TW_SLAVET_DATA_ACK 0xB8 /*slave Transmitted data and received ack*/
#define TW_SLAVET_DATA_NACK 0xC0 /*slave transmitted data but didn't receive ack*/
#define TW_SLAVET_LAST_ACK 0xC8

/*********************************************************************************************************************************
 *                       									Type definitions                                                                                      *
 *********************************************************************************************************************************/
typedef enum{
	TWI_INT_DISABLED, TWI_INT_ENABLED
}TWI_Interrupt;

typedef enum{
	TWI_PRESCALE_1, TWI_PRESCALE_4, TWI_PRESCALE_16, TWI_PRESCALE_64
}TWI_Prescaler;

typedef enum{
	TWI_GC_DISABLED, TWI_GC_ENABLED
}TWI_GeneralCall;
typedef struct {
	TWI_Interrupt interrupt;
	TWI_Prescaler prescale;
	TWI_GeneralCall gen_call; /*for general call when operating as a slave*/
	uint32 scl_freq;
	uint8 address;
}TWI_ConfigType;
/*********************************************************************************************************************************
 *                       									Function Prototypes                                                                                     *
 *********************************************************************************************************************************/
void TWI_Init(TWI_ConfigType* config_Ptr);
void TWI_Start(void);
void TWI_Stop(void);
void TWI_Listen(void);
void TWI_write(uint8 a_data);
uint8 TWI_Read_With_Ack(void);
uint8 TWI_Read_With_Nack(void);
uint8 TWI_Get_Status(void);

#endif /* TWI_H_ */
