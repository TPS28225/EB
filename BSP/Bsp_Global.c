/***********************************************************************
�ļ����ƣ�
��    �ܣ�
��дʱ�䣺
�� д �ˣ�
ע    �⣺
***********************************************************************/
#include "main.h" 
#include "malloc.h"	
/*
 * ���ܣ�
 *       �弶��ʼ��
 * ������
 *       ��
 * ���أ�
 *       ��
 * ˵����
 *       ������ģ���г�ʼ���ľ���ʹ��ģ���ʼ��
 */
//u32 testsram[250000] __attribute__((at(0X68000000)));//����������
//�ⲿ�ڴ����(���֧��1M�ֽ��ڴ����)	    
u32 fsmc_sram_test(void)
{  
	u32 i=0,s;  	  
	u8 temp=0;	   
	u8 sval=0;	//�ڵ�ַ0����������	  				   
	//ÿ��4K�ֽ�,д��һ������,�ܹ�д��256������,�պ���1M�ֽ�
	for(i=0;i<1024*1024;i+=4096)
	{
		FSMC_SRAM_WriteBuffer(&temp,i,1);
		temp++;
	}
	//���ζ���֮ǰд�������,����У��		  
 	for(i=0;i<1024*1024;i+=4096) 
	{
  		FSMC_SRAM_ReadBuffer(&temp,i,1);
		if(i==0)sval=temp;
 		else if(temp<=sval)break;//�������������һ��Ҫ�ȵ�һ�ζ��������ݴ�.	   		   
		s=(u16)(temp-sval+1)*4;//��ʾ�ڴ�����  
 	}
	return s;
}	

void BSP_Init(void)
{
	NVIC_Configuration();	
	delay_init();
	
	FSMC_SRAM_Init();
	my_mem_init(SRAMEX);  	//��ʼ���ⲿ�ڴ��	
	LED_Configuration();	
	TFTLCD_Init();	
//	BEEP_Configuration();
	Beep_Config();	
	MOTOR_Configuration();
	BLUTOOTH_Configuration();
//	Zigbee_Configuration();	//���ų�ͻ����ʱ����
//	UltrasonicWave_Configuration();	//�����ã�Ӧ���ǲ����ж�̫Ƶ���ˣ����鵥��ʹ��һ������
	KEY_init();
	DHT11_Init();
	LightIntensitySensor_Init();
	RC522_Init();
	IR_Configuration();
//	uart_init(115200);
}

