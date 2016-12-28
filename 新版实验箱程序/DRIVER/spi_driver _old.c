/**
  ******************************************************************************
  * @file    spi_driver.c
  * $Author: wdluo $
  * $Revision: 17 $
  * $Date:: 2012-07-06 11:16:48 +0800 #$
  * @brief   SPI�ײ���������.
  ******************************************************************************
  * @attention
  *
  *<h3><center>&copy; Copyright 2009-2012, ViewTool</center>
  *<center><a href="http:\\www.viewtool.com">http://www.viewtool.com</a></center>
  *<center>All Rights Reserved</center></h3>
  * 
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi_driver.h"
#include "RC522.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  ʹ��SPIʱ��
  * @param  SPIx ��Ҫʹ�õ�SPI
  * @retval None
  */
static void SPI_RCC_Configuration(SPI_TypeDef* SPIx)
{
	if(SPIx==SPI3)
	{
    // Enable SPI and GPIO clocks
    RCC_APB1PeriphClockCmd(RC522_SPI_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(RC522_SPI_PORT_CLK, ENABLE);
		RCC_AHB1PeriphClockCmd(RC522_NSS_CLK, ENABLE);
	}
}
/**
  * @brief  ����ָ��SPI������
  * @param  SPIx ��Ҫʹ�õ�SPI
  * @retval None
  */
static void SPI_GPIO_Configuration(SPI_TypeDef* SPIx)
{
	GPIO_InitTypeDef 		GPIO_InitStructure;
	if(SPIx==SPI3)
	{					 					 
		GPIO_PinAFConfig(RC522_SPI_PORT,GPIO_PinSource3,GPIO_AF_SPI3);        
		GPIO_PinAFConfig(RC522_SPI_PORT,GPIO_PinSource4,GPIO_AF_SPI3); 
		GPIO_PinAFConfig(RC522_SPI_PORT,GPIO_PinSource5,GPIO_AF_SPI3);
//		GPIO_PinAFConfig(GPIOA,GPIO_PinSource15,GPIO_AF_SPI3);			
			////SPI�ڳ�ʼ�� Set PB3,4,5 as Output push-pull - SCK, MISO and MOSI
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Pin = RC522_SCK_PIN | RC522_MISO_PIN | RC522_MOSI_PIN;
		GPIO_Init(RC522_SPI_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Pin = RC522_NSS_PIN;
		GPIO_Init(RC522_NSS_PORT, &GPIO_InitStructure);
		GPIO_SetBits(RC522_NSS_PORT,RC522_NSS_PIN);		
	}
}
/**
  * @brief  �����ⲿSPI�豸����SPI��ز���
  * @param  SPIx ��Ҫʹ�õ�SPI
  * @retval None
  */
void SPI_Configuration(SPI_TypeDef* SPIx)//Ŀǰֻ֧��SPI3
{
	SPI_InitTypeDef SPI_InitStruct;

	SPI_RCC_Configuration(SPIx);
	SPI_GPIO_Configuration(SPIx);
	
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
	SPI_InitStruct.SPI_Direction= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Hard;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	SPI_Init(SPIx, &SPI_InitStruct);

	SPI_SSOutputCmd(SPIx, ENABLE);
	SPI_Cmd(SPIx, ENABLE);
}
/**
  * @brief  д1�ֽ����ݵ�SPI����
  * @param  SPIx ��Ҫʹ�õ�SPI
  * @param  TxData д�����ߵ�����
  * @retval ���ݷ���״̬
  *		@arg 0 ���ݷ��ͳɹ�
  * 	@arg -1 ���ݷ���ʧ��
  */
int32_t SPI_WriteByte(SPI_TypeDef* SPIx, uint16_t TxData)
{
	uint8_t retry=0;				 
	while((SPIx->SR&SPI_I2S_FLAG_TXE)==0)				//�ȴ���������	
	{
		retry++;
		if(retry>200)return -1;
	}			  
	SPIx->DR=TxData;	 	  				//����һ��byte 
	retry=0;
	while((SPIx->SR&SPI_I2S_FLAG_RXNE)==0) 				//�ȴ�������һ��byte  
	{
		retry++;
		if(retry>200)return -1;
	}  
	SPIx->DR;						    
	return 0;          				//�����յ�������
}


/**
  * @brief  ��SPI���߶�ȡ1�ֽ�����
  * @param  SPIx ��Ҫʹ�õ�SPI
  * @param  p_RxData ���ݴ����ַ
  * @retval ���ݶ�ȡ״̬
  *		@arg 0 ���ݶ�ȡ�ɹ�
  * 	@arg -1 ���ݶ�ȡʧ��
  */
int32_t SPI_ReadByte(SPI_TypeDef* SPIx, uint16_t *p_RxData)
{
	uint8_t retry=0;				 
	while((SPIx->SR&SPI_I2S_FLAG_TXE)==0)				//�ȴ���������	
	{
		retry++;
		if(retry>200)return -1;
	}			  
	SPIx->DR=0xFF;	 	  				//����һ��byte 
	retry=0;
	while((SPIx->SR&SPI_I2S_FLAG_RXNE)==0) 				//�ȴ�������һ��byte  
	{
		retry++;
		if(retry>200)return -1;
	}
	*p_RxData = SPIx->DR;  						    
	return 0;          				//�����յ�������
}
/**
  * @brief  ��SPI����д���ֽ�����
  * @param  SPIx ��Ҫʹ�õ�SPI
  * @param  p_TxData �������ݻ������׵�ַ
  * @param	sendDataNum ���������ֽ���
  * @retval ���ݷ���״̬
  *		@arg 0 ���ݷ��ͳɹ�
  * 	@arg -1 ���ݷ���ʧ��
  */
int32_t SPI_WriteNBytes(SPI_TypeDef* SPIx, uint8_t *p_TxData,uint32_t sendDataNum)
{
	uint32_t retry=0;
	while(sendDataNum--){
		while((SPIx->SR&SPI_I2S_FLAG_TXE)==0)				//�ȴ���������	
		{
			retry++;
			if(retry>20000)return -1;
		}			  
		SPIx->DR=*p_TxData++;	 	  				//����һ��byte 
		retry=0;
		while((SPIx->SR&SPI_I2S_FLAG_RXNE)==0) 				//�ȴ�������һ��byte  
		{
			SPIx->SR = SPIx->SR;
			retry++;
			if(retry>20000)return -1;
		} 
		SPIx->DR;
	}
	return 0;
}
/**
  * @brief  ��SPI���߶�ȡ���ֽ�����
  * @param  SPIx ��Ҫʹ�õ�SPI
  * @param  p_RxData ���ݴ����ַ
  * @param	readDataNum ��ȡ�����ֽ���
  * @retval ���ݶ�ȡ״̬
  *		@arg 0 ���ݶ�ȡ�ɹ�
  * 	@arg -1 ���ݶ�ȡʧ��
  */
int32_t SPI_ReadNBytes(SPI_TypeDef* SPIx, uint8_t *p_RxData,uint32_t readDataNum)
{
	uint32_t retry=0;
	while(readDataNum--){
		SPIx->DR = 0xFF;
		while(!(SPIx->SR&SPI_I2S_FLAG_TXE)){
			retry++;
			if(retry>20000)return -1;
		}
		retry = 0;
		while(!(SPIx->SR&SPI_I2S_FLAG_RXNE)){
			retry++;
			if(retry>20000)return -1;
		}
		*p_RxData++ = SPIx->DR;
	}	
	return 0;
}

/*********************************END OF FILE**********************************/

