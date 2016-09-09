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
//u32 testsram[250000] __attribute__((at(0X68000000)));//测试用数组
//外部内存测试(最大支持1M字节内存测试)	    
u32 fsmc_sram_test(void)
{  
	u32 i=0,s;  	  
	u8 temp=0;	   
	u8 sval=0;	//在地址0读到的数据	  				   
	//每隔4K字节,写入一个数据,总共写入256个数据,刚好是1M字节
	for(i=0;i<1024*1024;i+=4096)
	{
		FSMC_SRAM_WriteBuffer(&temp,i,1);
		temp++;
	}
	//依次读出之前写入的数据,进行校验		  
 	for(i=0;i<1024*1024;i+=4096) 
	{
  		FSMC_SRAM_ReadBuffer(&temp,i,1);
		if(i==0)sval=temp;
 		else if(temp<=sval)break;//后面读出的数据一定要比第一次读到的数据大.	   		   
		s=(u16)(temp-sval+1)*4;//显示内存容量  
 	}
	return s;
}	

void BSP_Init(void)
{
	NVIC_Configuration();	
	delay_init();
	
	FSMC_SRAM_Init();
	my_mem_init(SRAMEX);  	//初始化外部内存池	
	LED_Configuration();	
	TFTLCD_Init();	
//	BEEP_Configuration();
	Beep_Config();	
	MOTOR_Configuration();
	BLUTOOTH_Configuration();
//	Zigbee_Configuration();	//引脚冲突，暂时屏蔽
//	UltrasonicWave_Configuration();	//不好用，应该是产生中断太频繁了，建议单独使用一个任务
	KEY_init();
	DHT11_Init();
	LightIntensitySensor_Init();
	RC522_Init();
	IR_Configuration();
//	uart_init(115200);
}

