#include "lcd.h"
#include "stdlib.h"
#include "usart.h"
#include "delay.h"	 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STM32F103RBT6,主频72M  单片机工作电压3.3V
//QDtech-TFT液晶驱动 for STM32 IO模拟
//xiao冯@ShenZhen QDtech co.,LTD
//公司网站:www.qdtech.net
//淘宝网站：http://qdtech.taobao.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-23594567 
//手机:15989313508（冯工） 
//邮箱:QDtech2008@gmail.com 
//Skype:QDtech2008
//技术交流QQ群:324828016
//创建日期:2013/5/13
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////	
/****************************************************************************************************
//=======================================液晶屏数据线接线==========================================//
STM32 PB组接液晶屏DB0~DB16,举例依次为DB0接PB0,..DB15接PB15.   
//=======================================液晶屏控制线接线==========================================//
//LCD_CS	接PC9	//片选信号
//LCD_RS	接PC8	//寄存器/数据选择信号
//LCD_WR	接PC7	//写信号
//LCD_RD	接PC6	//读信号
//LCD_RST	接PC5	//复位信号
//LCD_LED	接PC10	//背光控制信号(高电平点亮)
//=========================================触摸屏触接线=========================================//
//不使用触摸或者模块本身不带触摸，则可不连接
//MO(MISO)	接PC2	//SPI总线输出
//MI(MOSI)	接PC3	//SPI总线输入
//PEN		接PC1	//触摸屏中断信号
//TCS		接PC13	//触摸IC片选
//CLK		接PC0	//SPI总线时钟
**************************************************************************************************/	
	   
//管理LCD重要参数
//默认为竖屏
_lcd_dev lcddev;

//画笔颜色,背景颜色
u16 POINT_COLOR = 0x0000,BACK_COLOR = 0xFFFF;  
u16 DeviceCode;	 


//******************************************************************
//函数名：  LCD_WR_REG
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    向液晶屏总线写入写16位指令
//输入参数：Reg:待写入的指令值
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_WR_REG(u8 data)
{ 
	LCD_RS_CLR;//写地址  
 	LCD_CS_CLR; 
	 
	LCD_WR_CLR; 
	DATAOUT(data);
	LCD_WR_SET; 
 	LCD_CS_SET; 	
}

//******************************************************************
//函数名：  LCD_WR_DATA
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    向液晶屏总线写入写16位数据
//输入参数：Data:待写入的数据
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_WR_DATA(u16 data)
{
	LCD_RS_SET;
	LCD_CS_CLR;
	
	LCD_WR_CLR;
	DATAOUT(data);
	LCD_WR_SET;
	LCD_CS_SET;

}
//******************************************************************
//函数名：  LCD_DrawPoint_16Bit
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    8位总线下如何写入一个16位数据
//输入参数：(x,y):光标坐标
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_DrawPoint_16Bit(u16 color)
{
	LCD_WR_DATA(color);

}

//******************************************************************
//函数名：  LCD_WriteReg
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    写寄存器数据
//输入参数：LCD_Reg:寄存器地址
//			LCD_RegValue:要写入的数据
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{	
	LCD_WR_REG(LCD_Reg);  
	LCD_WR_DATA(LCD_RegValue);	    		 
}	   
	 
//******************************************************************
//函数名：  LCD_WriteRAM_Prepare
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    开始写GRAM
//			在给液晶屏传送RGB数据前，应该发送写GRAM指令
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
}	 

//******************************************************************
//函数名：  LCD_DrawPoint
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    在指定位置写入一个像素点数据
//输入参数：(x,y):光标坐标
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);//设置光标位置 
#if LCD_USE8BIT_MODEL==1
	LCD_CS_CLR;
	LCD_RD_SET;
	LCD_RS_SET;//写地址  	 
	DATAOUT(POINT_COLOR>>8);	
	LCD_WR_CLR;
	LCD_WR_SET;	
	DATAOUT(POINT_COLOR);	
	LCD_WR_CLR;
	LCD_WR_SET;	 
	LCD_CS_SET;
#else
	LCD_WR_DATA(POINT_COLOR); 
#endif


}

//从ILI93xx读出的数据为GBR格式，而我们写入的时候为RGB格式。
//通过该函数转换
//c:GBR格式的颜色值
//返回值：RGB格式的颜色值
u16 LCD_BGR2RGB(u16 c)
{
	u16  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
}		 
//读取个某点的颜色值	 
//x,y:坐标
//返回值:此点的颜色
u16 LCD_ReadPoint(u16 x,u16 y)
{
 	u16 r;	
	if(x>=lcddev.width||y>=lcddev.height)return 0;	//超过了范围,直接返回		   
	LCD_SetCursor(x,y);
	LCD_WR_REG(0x2E);      		 		//其他IC发送读GRAM指令
	GPIOB->CRL=0X88888888; //PB0-7  上拉输入
	GPIOB->CRH=0X88888888; //PB8-15 上拉输入
	GPIOB->ODR=0XFFFF;     //全部输出高

	LCD_RS_SET;
	LCD_CS_CLR;

 	//dummy READ
	LCD_RD_CLR;					   
	delay_us(1);//延时1us					   
 	r=DATAIN;  	//实际坐标颜色
	LCD_RD_SET;
	
	LCD_RD_CLR;					   
	delay_us(1);//延时1us					   
 	r=DATAIN;  	//实际坐标颜色
	LCD_RD_SET;
	
	LCD_CS_SET;
	GPIOB->CRL=0X33333333; 		//PB0-7  上拉输出
	GPIOB->CRH=0X33333333; 		//PB8-15 上拉输出
	GPIOB->ODR=0XFFFF;    		//全部输出高  


	return (r);
}

//读取个某点的颜色值	 
//x,y:坐标
//返回值:此点的颜色
u16 LCD_ID(void)
{
 	u16 r;
	
	//LCD_SetCursor(0,0);
	LCD_WR_REG(0xBF);      		 		//其他IC发送读GRAM指令
	GPIOB->CRL=0X88888888; //PB0-7  上拉输入
	GPIOB->CRH=0X88888888; //PB8-15 上拉输入
	GPIOB->ODR=0XFFFF;     //全部输出高

	LCD_RS_SET;
	LCD_CS_CLR;

 	//dummy READ
	LCD_RD_CLR;					   
	delay_us(1);//延时1us					   
 	r=DATAIN;  	//实际坐标颜色
	LCD_RD_SET;
	
	LCD_RD_CLR;					   
	delay_us(1);//延时1us					   
 	r=DATAIN;  	//实际坐标颜色
	LCD_RD_SET;
	
	LCD_RD_CLR;					   
	delay_us(1);//延时1us					   
 	r=DATAIN;  	//0x62
	LCD_RD_SET;
	
	LCD_RD_CLR;					   
	delay_us(1);//延时1us					   
 	r=DATAIN;  	//0x83
	LCD_RD_SET;
	
	LCD_RD_CLR;					   
	delay_us(1);//延时1us					   
 	r=(r<<8)|DATAIN;  	//0x83
	LCD_RD_SET;
	
	LCD_CS_SET;
	GPIOB->CRL=0X33333333; 		//PB0-7  上拉输出
	GPIOB->CRH=0X33333333; 		//PB8-15 上拉输出
	GPIOB->ODR=0XFFFF;    		//全部输出高  


	return (r);
}
//******************************************************************
//函数名：  LCD_Clear
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    LCD全屏填充清屏函数
//输入参数：Color:要清屏的填充色
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_Clear(u16 Color)
{
	u32 index=0; 
u32 total=0; 	
total=lcddev.width*lcddev.height;  
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);	
	LCD_RS_SET;
	LCD_CS_CLR;
	
	
	for(index=0;index<total;index++)
	{
		//LCD_WR_DATA(Color);		
DATAOUT(Color);
	LCD_WR_CLR;
	LCD_WR_SET;		
	}
//LCD_CS_SET;
	
} 

//******************************************************************
//函数名：  LCD_GPIOInit
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    液晶屏IO初始化，液晶初始化前要调用此函数
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE); 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5;	   //GPIO_Pin_10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure); //GPIOC	
	GPIO_SetBits(GPIOC,GPIO_Pin_10|GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;	//  
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //GPIOB
	GPIO_SetBits(GPIOB,GPIO_Pin_All);	 
}

//******************************************************************
//函数名：  LCD_Reset
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    LCD复位函数，液晶初始化前要调用此函数
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_RESET(void)
{
	LCD_RST_CLR;
	delay_ms(100);	
	LCD_RST_SET;
	delay_ms(50);
}
 	 
//******************************************************************
//函数名：  LCD_Init
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    LCD初始化
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_Init(void)
{  
     										 
	LCD_GPIOInit();
 	LCD_RESET();
	//LCD_RD_SET;

		
	LCD_WR_REG(0xEE);//Set EQ  
	LCD_WR_DATA(0x02);  
	LCD_WR_DATA(0x01);  
	LCD_WR_DATA(0x02);  
	LCD_WR_DATA(0x01);  

	LCD_WR_REG(0xED);//Set DIR TIM  
	LCD_WR_DATA(0x00);  
	LCD_WR_DATA(0x00);  
	LCD_WR_DATA(0x9A);  
	LCD_WR_DATA(0x9A);  
	LCD_WR_DATA(0x9B);  
	LCD_WR_DATA(0x9B);  
	LCD_WR_DATA(0x00);  
	LCD_WR_DATA(0x00);  
	LCD_WR_DATA(0x00);  
	LCD_WR_DATA(0x00);  
	LCD_WR_DATA(0xAE);  
	LCD_WR_DATA(0xAE);  
	LCD_WR_DATA(0x01);  
	LCD_WR_DATA(0xA2);  
	LCD_WR_DATA(0x00);  

	LCD_WR_REG(0xB4);//Set RM, DM  
	LCD_WR_DATA(0x00);//  

	LCD_WR_REG(0xC0); //Set Panel Driving
	LCD_WR_DATA(0x00); //REV SM GS
	LCD_WR_DATA(0x3B); // NL[5:0]  
	LCD_WR_DATA(0x00); //SCN[6:0]  
	LCD_WR_DATA(0x02); //NDL 0 PTS[2:0]
	LCD_WR_DATA(0x11); //PTG ISC[3:0]  

	LCD_WR_REG(0xC1);//
	LCD_WR_DATA(0x10);//line inversion

	LCD_WR_REG(0xC8);//Set Gamma  
	LCD_WR_DATA(0x00); //KP1,KP0
	LCD_WR_DATA(0x46); //KP3,KP2
	LCD_WR_DATA(0x12); //KP5,KP4
	LCD_WR_DATA(0x20); //RP1,RP0
	LCD_WR_DATA(0x0c); //VRP0 01
	LCD_WR_DATA(0x00); //VRP1
	LCD_WR_DATA(0x56); //KN1,KN0
	LCD_WR_DATA(0x12); //KN3,KN2
	LCD_WR_DATA(0x67); //KN5,KN4
	LCD_WR_DATA(0x02); //RN1,RN0
	LCD_WR_DATA(0x00); //VRN0
	LCD_WR_DATA(0x0c); //VRN1 01

	LCD_WR_REG(0xD0);//Set Power  
	LCD_WR_DATA(0x44);//DDVDH :5.28
	LCD_WR_DATA(0x42); // BT VGH:15.84 VGL:-7.92
	LCD_WR_DATA(0x06);//VREG1 4.625V

	LCD_WR_REG(0xD1);//Set VCOM  
	LCD_WR_DATA(0x43); //VCOMH
	LCD_WR_DATA(0x16);

	LCD_WR_REG(0xD2);  
	LCD_WR_DATA(0x04);  
	LCD_WR_DATA(0x22); //12

	LCD_WR_REG(0xD3);  
	LCD_WR_DATA(0x04);  
	LCD_WR_DATA(0x12);  

	LCD_WR_REG(0xD4);  
	LCD_WR_DATA(0x07);  
	LCD_WR_DATA(0x12);  

	LCD_WR_REG(0xE9); //Set Panel
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0xC5); //Set Frame rate
	LCD_WR_DATA(0x08); //61.51Hz

	LCD_WR_REG(0X0036);
	LCD_WR_DATA(0X000a);

	LCD_WR_REG(0X003A);
	LCD_WR_DATA(0X0055);

	LCD_WR_REG(0X002A);
	LCD_WR_DATA(0X0000);
	LCD_WR_DATA(0X0000);
	LCD_WR_DATA(0X0001);
	LCD_WR_DATA(0X003F);

	LCD_WR_REG(0X002B);
	LCD_WR_DATA(0X0000);
	LCD_WR_DATA(0X0000);
	LCD_WR_DATA(0X0001);
	LCD_WR_DATA(0X00E0);
	delay_ms(20);

	LCD_WR_REG(0x11);//Sleep Out  
	delay_ms(120);  

	LCD_WR_REG(0x35);
	LCD_WR_DATA(0x00);//TE ON

	LCD_WR_REG(0x29); //Display On
	delay_ms(5);
	

	LCD_SetParam();//设置LCD参数	 
	LCD_Clear(WHITE);
}
  		  
//******************************************************************
//函数名：  LCD_SetWindows
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    设置显示窗口
//输入参数：(xStar,yStar):窗口左上角起始坐标
//	 	   	(xEnd,yEnd):窗口右下角结束坐标
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{	
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA(xStar>>8);
	LCD_WR_DATA(xStar);		
	LCD_WR_DATA(xEnd>>8);
	LCD_WR_DATA(xEnd);

	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA(yStar>>8);
	LCD_WR_DATA(yStar);		
	LCD_WR_DATA(yEnd>>8);
	LCD_WR_DATA(yEnd);

	LCD_WriteRAM_Prepare();	//开始写入GRAM		
//delay_us(1);	
}   

//******************************************************************
//函数名：  LCD_SetCursor
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    设置光标位置
//输入参数：Xpos:横坐标
//			Ypos:纵坐标
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	  	    			
	LCD_SetWindows(Xpos,Ypos,Xpos+1,Ypos+1);		
} 

//******************************************************************
//函数名：  LCD_SetParam
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    设置LCD参数，方便进行横竖屏模式切换
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_SetParam(void)
{ 
	lcddev.setxcmd=0x2A;
	lcddev.setycmd=0x2B;
	lcddev.wramcmd=0x2C;
#if USE_HORIZONTAL==1	//使用横屏	  
	lcddev.dir=1;//横屏
	lcddev.width=480;
	lcddev.height=320;			
	LCD_WriteReg(0x36,0x3B);//BGR==1,MY==1,MX==0,MV==1  63
#else//竖屏
	lcddev.dir=0;//竖屏				 	 		
	lcddev.width=320;
	lcddev.height=480;	
	LCD_WriteReg(0x36,0X0A);//BGR==1,MY==0,MX==0,MV==0
#endif
}	  


