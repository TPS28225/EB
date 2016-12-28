#include "main.h"


extern INPUTDEVICE_MEASURE INPUTDEVICE;

void humanbodysensor_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_AHB1PeriphClockCmd(HUMANBODYSENSOR_PORT_CLOCK, ENABLE);	//ʹ��PD�˿�ʱ��
	
 	GPIO_InitStructure.GPIO_Pin =  HUMANBODYSENSOR_IN_PIN;			//PD8�˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 		 						//����
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
 	GPIO_Init(HUMANBODYSENSOR_IN_PORT, &GPIO_InitStructure);	  //��ʼ��IO��
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
















