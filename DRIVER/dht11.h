#ifndef __DHT11_H
#define __DHT11_H 
#include "main.h"  
 
#define DHT11_DQ_PORT			GPIOE
#define DHT11_DQ_PIN			GPIO_Pin_4
#define DHT11_DQ_PORT_CLK	RCC_AHB1Periph_GPIOE
#define DHT11_DQ_IN				(GPIO_ReadInputDataBit(DHT11_DQ_PORT, DHT11_DQ_PIN))

u8 DHT11_Init(void);//初始化DHT11
u8 DHT11_Read_Data(void);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11    
#endif















