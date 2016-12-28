#ifndef __SPI_H
#define __SPI_H
#include "main.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//SPI 驱动函数	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/6/13 
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
/* defines */

#define     SDCARD_PORT_CLK        						RCC_AHB1Periph_GPIOB

#define     SDCARD_PORT                       GPIOB

#define     SDCARD_CS_PIN                     GPIO_Pin_12

#define	    SDCARD_CS_L                       GPIO_ResetBits(SDCARD_PORT , SDCARD_CS_PIN)
#define     SDCARD_CS_H                       GPIO_SetBits(SDCARD_PORT , SDCARD_CS_PIN)

#define  		SDCARD_SCK_PIN										GPIO_Pin_13//??SLK
#define     SDCARD_MISO_PIN                   GPIO_Pin_14
#define			SDCARD_MOSI_PIN										GPIO_Pin_15 

#define			SDCARD_SPI												SPI2

 				  	    													  
void SPIx_Init(void);			 //初始化SPI口
void SPIx_SetSpeed(u8 SpeedSet); //设置SPI速度   
u8 SPIx_ReadWriteByte(u8 TxData);//SPI总线读写一个字节
		 
#endif

