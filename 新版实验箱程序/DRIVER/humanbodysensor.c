#include "main.h"


extern INPUTDEVICE_MEASURE INPUTDEVICE;

void humanbodysensor_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_AHB1PeriphClockCmd(HUMANBODYSENSOR_PORT_CLOCK, ENABLE);	//使能PD端口时钟
	
 	GPIO_InitStructure.GPIO_Pin =  HUMANBODYSENSOR_IN_PIN;			//PD8端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 		 						//输入
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
 	GPIO_Init(HUMANBODYSENSOR_IN_PORT, &GPIO_InitStructure);	  //初始化IO口
}

void humanbodysensor_measure(void)
{
	u8 Humanbodysensor_Counter=0;
	u8 Counter=0;
	while(Counter<100)
	{
		Counter++;		
		if(!GPIO_ReadInputDataBit(HUMANBODYSENSOR_IN_PORT, HUMANBODYSENSOR_IN_PIN))Humanbodysensor_Counter++;
		delay_us(100);
	}	
	if(Humanbodysensor_Counter>5)INPUTDEVICE.exist_people=SET;
	else INPUTDEVICE.exist_people=RESET;
}
















