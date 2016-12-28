#ifndef __SPI_H
#define __SPI_H
#include "main.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//SPI ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/6/13 
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
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

 				  	    													  
void SPIx_Init(void);			 //��ʼ��SPI��
void SPIx_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
u8 SPIx_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�
		 
#endif

