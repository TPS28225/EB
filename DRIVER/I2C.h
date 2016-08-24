#ifndef __I2C_H__
#define __I2C_H__
#include "main.h"

#define FALSE 0
#define TRUE  1

#define SCL_PORT 	GPIOF
#define SCL_PIN 	GPIO_Pin_8
#define SDA_PORT 	GPIOF
#define SDA_PIN 	GPIO_Pin_9
#define I2C_PORT_CLOCK 	RCC_AHB1Periph_GPIOF

#define SCL_H         GPIO_SetBits(SCL_PORT,SCL_PIN)  
#define SCL_L         GPIO_ResetBits(SCL_PORT,SCL_PIN) 

#define SDA_H         GPIO_SetBits(SDA_PORT,SDA_PIN) 
#define SDA_L         GPIO_ResetBits(SDA_PORT,SDA_PIN) 

#define SCL_read      GPIO_ReadInputDataBit(SCL_PORT,SCL_PIN) 
#define SDA_read      GPIO_ReadInputDataBit(SDA_PORT,SDA_PIN) 

void I2C_INIT(void);
void I2C_delay(void);
void delay5ms(void);
uint16_t I2C_Start(void);
void I2C_Stop(void);
void I2C_Ack(void); 
void I2C_NoAck(void);
uint16_t I2C_WaitAck(void);
void I2C_SendByte(unsigned char SendByte);
unsigned char I2C_ReadByte(void);
uint16_t I2C_Single_Write_data(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
uint16_t I2C_Single_Write(unsigned char SlaveAddress,unsigned char REG_Address);	
unsigned char I2C_Single_Read(unsigned char SlaveAddress,unsigned char REG_Address);


#endif // __MYI2C_H__
