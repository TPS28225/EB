/***********************************************************************
文件名称：
功    能：
编写时间：
编 写 人：
注    意：
***********************************************************************/
#include "main.h" 
#include "malloc.h"	
/*
 * 功能：
 *       板级初始化
 * 参数：
 *       无
 * 返回：
 *       无
 * 说明：
 *       可用与模块中初始化的尽量使用模块初始化
 */
void BSP_Init(void)
{
	NVIC_Configuration();	
	delay_init();
	FSMC_SRAM_Init();
	my_mem_init(SRAMEX);  	//初始化外部内存池	
	LED_Configuration();
	TFTLCD_Init();
//	BEEP_Configuration();//已经在别的地方初始化
	MOTOR_Configuration();
	BLUTOOTH_Configuration();
//	Zigbee_Configuration();	//引脚冲突，暂时屏蔽
	UltrasonicWave_Configuration();	
	KEY_init();
	DHT11_Init();
	LightIntensitySensor_Init();
	RC522_Init();
	IR_Configuration();
	uart_init(115200);
}

