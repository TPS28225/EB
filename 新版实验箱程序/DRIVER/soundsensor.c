#include "main.h"



void soundsensor_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_AHB1PeriphClockCmd(SOUNDSENSOR_PORT_CLOCK, ENABLE);	 	//ʹ��PE�˿�ʱ��
	
 	GPIO_InitStructure.GPIO_Pin =  SOUNDSENSOR_IN_PIN;			//PE10�˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 		 				//����
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
 	GPIO_Init(SOUNDSENSOR_IN_PORT, &GPIO_InitStructure);				 //��ʼ��IO��
}

void soundsensor_measure(void)
{
	u8 Soundsensor_Counter=0;
	u8 Counter=0;
	//��10ms���ڣ����һ�ٴΣ������⵽��������ֵ�Ĵ�������50������Ϊ����ȷʵ������ֵ��
	while(Counter<100)
	{
		Counter++;		
		if(!GPIO_ReadInputDataBit(SOUNDSENSOR_IN_PORT, SOUNDSENSOR_IN_PIN))Soundsensor_Counter++;
		delay_us(100);
	}	
	if(Soundsensor_Counter>5)INPUTDEVICE.sound_exceed_threshold=SET;
	else INPUTDEVICE.sound_exceed_threshold=RESET;
}

















