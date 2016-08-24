#include "main.h"

const unsigned char AC_TABLE[]={
0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,
0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,
0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,
0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,
};
extern const char gImage_zhzk[800];
void LCD_wr(u8 lcd_com,u8 lcd_data)                                         //写入LCD数据或命令
{
	u8 lcd_data_msb,lcd_data_lsb;
	lcd_data_msb=0xf0&lcd_data;
	lcd_data_lsb=(0x0f&lcd_data)<<4;
	if(lcd_com==0)                                        //写命令
	{
		while(SPI_I2S_GetFlagStatus(LCD12864_SPI, SPI_I2S_FLAG_TXE)==RESET);        //等待 LCD12864_SPI 发送缓冲空
		SPI_I2S_SendData(LCD12864_SPI, 0xf8);                        // LCD12864_SPI 发送数据--命令指令-- 
	}
	if(lcd_com==1)                                        //写数据
	{
		while(SPI_I2S_GetFlagStatus(LCD12864_SPI, SPI_I2S_FLAG_TXE)==RESET);                //等待 LCD12864_SPI 发送缓冲空
		SPI_I2S_SendData(LCD12864_SPI, 0xfa);                    //LCD12864_SPI 发送数据--数据指令--
	}
	delay_us(85);
	while(SPI_I2S_GetFlagStatus(LCD12864_SPI, SPI_I2S_FLAG_TXE)==RESET);                //等待 LCD12864_SPI 接收数据完毕
	SPI_I2S_SendData(LCD12864_SPI, lcd_data_msb);                   //LCD12864_SPI 发送高4位数据
	delay_us(85);
	while(SPI_I2S_GetFlagStatus(LCD12864_SPI, SPI_I2S_FLAG_TXE)==RESET);                //Wait for LCD12864_SPI Tx buffer empty
	SPI_I2S_SendData(LCD12864_SPI, lcd_data_lsb);            // LCD12864_SPI 发送低4位数据
	delay_us(85);
} 
//void LCD12864_ShowString(char *chn)                          
//{
//	u8 i,j;
//	LCD_wr(0,0x30);
//	LCD_wr(0,0x80);
//	for(j=0;j<4;j++)
//	{
//		for (i=0;i<16;i++)
//		{		
//			if(chn[j*16+i]==0)break;
//			LCD_wr(1,chn[j*16+i]);
//		}
//		if(i!=16)	break;	
//	}
//} 

void LcmClearTXT( void )
{
	unsigned char i;
	LCD_wr(0,0x30);
	LCD_wr(0,0x80);
	for(i=0;i<64;i++)
	LCD_wr(1,0x20);
}
void LcmClearBMP( void )
{
	unsigned char i,j;
	LCD_wr(0,0x34);
	LCD_wr(0,0x36);
	for(i=0;i<32;i++)
	{
		LCD_wr(0,0x80|i);
		LCD_wr(0,0x80);
		for(j=0;j<32;j++)
		LCD_wr(1,0);
	}
}
void PutStr(unsigned char row,unsigned char col,char *puts)
{
	LCD_wr(0,0x30);
	LCD_wr(0,AC_TABLE[8*row+col]);
	while(*puts != '\0')
	{
		if(col==8)
		{
					 col=0;
					 row++;
		}
		if(row==4) row=0;
		LCD_wr(0,AC_TABLE[8*row+col]);
		LCD_wr(1,*puts);
		puts++;
		LCD_wr(1,*puts);
		puts++;
		col++;
	}
}
void PutBMP(const char *puts)
{
	unsigned int x=0;
	unsigned char i,j;
	LCD_wr(0,0x34);
	LCD_wr(0,0x36);
	
	for(i=7;i<16;i++) 
	{
		LCD_wr(0,0x80+i);
		LCD_wr(0,0x80); 
		for(j=0;j<16;j++)    
		{                     
		 LCD_wr(1,puts[x]);
		 x++;
		}
	}

	for(i=0;i<16;i++) 
	{
		LCD_wr(0,0x90+i);
		LCD_wr(0,0x80); 
		for(j=0;j<16;j++)    
		{                     
		 LCD_wr(1,puts[x]);
		 x++;
		}
	}

	for(i=0;i<16;i++) 
	{
		LCD_wr(0,0x80+i);
		LCD_wr(0,0x88); 
		for(j=0;j<16;j++)    
		{                     
		 LCD_wr(1,puts[x]);
		 x++;
		}
	}

	for(i=0;i<9;i++) 
	{
		LCD_wr(0,0x90+i);
		LCD_wr(0,0x98); 
		for(j=0;j<16;j++)    
		{                     
		 LCD_wr(1,puts[x]);
		 x++;
		}
	}	

}
/**********************SPI初始化**********************/
void SPI_LCD12864_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(LCD12864_PORT_CLK, ENABLE);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	GPIO_PinAFConfig(LCD12864_PORT,GPIO_PinSource13,GPIO_AF_SPI2);        
	GPIO_PinAFConfig(LCD12864_PORT,GPIO_PinSource15,GPIO_AF_SPI2);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = LCD12864_SCK_PIN | LCD12864_SDA_PIN;
	GPIO_Init(LCD12864_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = LCD12864_RST_PIN | LCD12864_CS_PIN ;
	GPIO_Init(LCD12864_PORT, &GPIO_InitStructure);	

	/* LCD12864_SPI Config -------------------------------------------------------------*/
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(LCD12864_SPI, &SPI_InitStructure);
	/* Enable LCD12864_SPI */
	SPI_Cmd(LCD12864_SPI, ENABLE);
}
/*********************12864初始化***********************/
 void LCD12864_Init(void)                          //LCD初始化
{
	SPI_LCD12864_Init();
	LCD12864_RST_L;
	delay_ms(100); 
	LCD12864_RST_H;                          // 复位LCD
	LCD12864_CS_H;

	LCD_wr(0,0x30);                  //30---基本指令动作 
	LCD_wr(0,0x01);                  //清屏，地址指针指向00H
	LCD_wr(0,0x06);                  //光标的移动方向
	LCD_wr(0,0x0c);                  //开显示，关游标
   
	LcmClearBMP( );
	PutBMP(gImage_zhzk);	
 }

void LCD12864_Run(char *pchar)
{
	static u8 i=0;
	if(i==0)
	{
		LcmClearTXT();
		PutStr(0,0,pchar);
		i++;
	}
}


