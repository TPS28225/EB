#include "main.h"



void soundsensor_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_AHB1PeriphClockCmd(SOUNDSENSOR_PORT_CLOCK, ENABLE);	 	//使能PE端口时钟
	
 	GPIO_InitStructure.GPIO_Pin =  SOUNDSENSOR_IN_PIN;			//PE10端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 		 				//输入
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
 	GPIO_Init(SOUNDSENSOR_IN_PORT, &GPIO_InitStructure);				 //初始化IO口
}

void soundsensor_measure(void)
{
	u8 Soundsensor_Counter=0;
	u8 Counter=0;
	//在10ms以内，监测一百次，如果检测到声音超阈值的次数超过50，则认为声音确实超过阈值了
	while(Counter<100)
	{
		Counter++;		
		if(!GPIO_ReadInputDataBit(SOUNDSENSOR_IN_PORT, SOUNDSENSOR_IN_PIN))Soundsensor_Counter++;
		delay_us(100);
	}	
	if(Soundsensor_Counter>5)INPUTDEVICE.sound_exceed_threshold=SET;
	else INPUTDEVICE.sound_exceed_threshold=RESET;
}

















