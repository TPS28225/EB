#ifndef _LIGHTINTENSITY_H
#define _LIGHTINTENSITY_H
#include "main.h"

#define	  SLAVEADDRESS   0x46 //����������IIC�����еĴӵ�ַ,����ALT  ADDRESS��ַ���Ų�ͬ�޸�
															//ALT  ADDRESS���Žӵ�ʱ��ַΪ0x46

void 	LightIntensitySensor_Init(void);
u8	LightIntensitySensor_measure(void);                             //�����Ķ�ȡ�ڲ��Ĵ�������

#endif






































