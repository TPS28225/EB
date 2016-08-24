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
void BSP_Init(void)
{
	NVIC_Configuration();	
	delay_init();
	FSMC_SRAM_Init();
	my_mem_init(SRAMEX);  	//��ʼ���ⲿ�ڴ��	
	LED_Configuration();
	TFTLCD_Init();
//	BEEP_Configuration();//�Ѿ��ڱ�ĵط���ʼ��
	MOTOR_Configuration();
	BLUTOOTH_Configuration();
//	Zigbee_Configuration();	//���ų�ͻ����ʱ����
	UltrasonicWave_Configuration();	
	KEY_init();
	DHT11_Init();
	LightIntensitySensor_Init();
	RC522_Init();
	IR_Configuration();
	uart_init(115200);
}

