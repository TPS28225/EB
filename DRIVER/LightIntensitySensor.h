#ifndef _LIGHTINTENSITY_H
#define _LIGHTINTENSITY_H
#include "main.h"

#define	  SLAVEADDRESS   0x46 //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改
															//ALT  ADDRESS引脚接地时地址为0x46

void 	LightIntensitySensor_Init(void);
u8	LightIntensitySensor_measure(void);                             //连续的读取内部寄存器数据

#endif






































