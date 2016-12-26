#include "main.h"

 //////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//DHT11������ʪ�ȴ�������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/12
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//��λDHT11
void DHT11_Rst(void)	   
{ 	
	GPIO_InitTypeDef  GPIO_InitStructure;	
	GPIO_InitStructure.GPIO_Pin = DHT11_DQ_PIN;				 //PE4�˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
 	GPIO_Init(DHT11_DQ_PORT, &GPIO_InitStructure);				 //��ʼ��IO��
	
	GPIO_ResetBits(DHT11_DQ_PORT, DHT11_DQ_PIN); 	//����DQ
	delay_ms(20);    	//��������18ms
	GPIO_SetBits(DHT11_DQ_PORT, DHT11_DQ_PIN); 	//DQ=1 
	delay_us(30);     	//��������20~40us
}
//�ȴ�DHT11�Ļ�Ӧ
//����1:δ��⵽DHT11�Ĵ���
//����0:����
u8 DHT11_Check(void) 	   
{   
	u8 retry=0;
	
	GPIO_InitTypeDef  GPIO_InitStructure;	
	GPIO_InitStructure.GPIO_Pin = DHT11_DQ_PIN;				 //PE4�˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 		 //��������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
 	GPIO_Init(DHT11_DQ_PORT, &GPIO_InitStructure);				 //��ʼ��IO��
	
	while ((DHT11_DQ_IN==SET)&&retry<100)//DHT11������40~80us
	{
		retry++;
		delay_us(1);
	};
	
	if(retry>=100)return 1;
	else retry=0;
		
	while (!DHT11_DQ_IN&&retry<100)//DHT11���ͺ���ٴ�����40~80us
	{
		retry++;
		delay_us(1);
	};
	
	if(retry>=100)return 1;	    
	return 0;
}
//��DHT11��ȡһ��λ
//����ֵ��1/0
u8 DHT11_Read_Bit(void) 			 
{
 	u8 retry=0;
	while(DHT11_DQ_IN&&retry<100)//�ȴ���Ϊ�͵�ƽ
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!DHT11_DQ_IN&&retry<100)//�ȴ���ߵ�ƽ
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);//�ȴ�40us
	if(DHT11_DQ_IN)return 1;
	else return 0;		   
}
//��DHT11��ȡһ���ֽ�
//����ֵ������������
u8 DHT11_Read_Byte(void)    
{        
    u8 i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT11_Read_Bit();
    }						    
    return dat;
}
//��DHT11��ȡһ������
//temp:�¶�ֵ(��Χ:0~50��)
//humi:ʪ��ֵ(��Χ:20%~90%)
//����ֵ��0,����;1,��ȡʧ��
u8 DHT11_Read_Data(void)    
{        
 	u8 buf[5];
	u8 i;
	
	INPUTDEVICE.humidity=0;
	INPUTDEVICE.temperature=0;
	
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)//��ȡ40λ����
		{
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			if(buf[0]>100)	INPUTDEVICE.humidity=0;
				else INPUTDEVICE.humidity=buf[0];
			if(buf[2]>100)	INPUTDEVICE.humidity=0;
				else INPUTDEVICE.temperature=buf[2];
		}
	}else return 1;
	return 0;	    
}
//��ʼ��DHT11��IO�� DQ ͬʱ���DHT11�Ĵ���
//����1:������
//����0:����    	 
u8 DHT11_Init(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_AHB1PeriphClockCmd(DHT11_DQ_PORT_CLK, ENABLE);	 //ʹ��PE�˿�ʱ��
	
 	GPIO_InitStructure.GPIO_Pin = DHT11_DQ_PIN;				 //PE4�˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
 	GPIO_Init(DHT11_DQ_PORT, &GPIO_InitStructure);				 //��ʼ��IO��
	GPIO_SetBits(DHT11_DQ_PORT, DHT11_DQ_PIN);						 //PE4 �����
	
	DHT11_Rst();  //��λDHT11
	return DHT11_Check();//�ȴ�DHT11�Ļ�Ӧ
} 







