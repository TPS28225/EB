#ifndef __DHT11_H
#define __DHT11_H 
#include "main.h"  
 
#define DHT11_DQ_PORT			GPIOE
#define DHT11_DQ_PIN			GPIO_Pin_4
#define DHT11_DQ_PORT_CLK	RCC_AHB1Periph_GPIOE
#define DHT11_DQ_IN				(GPIO_ReadInputDataBit(DHT11_DQ_PORT, DHT11_DQ_PIN))

u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(void);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11    
#endif















