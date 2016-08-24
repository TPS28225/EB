#ifndef __LCD12864_H
#define __LCD12864_H

/* includes */
#include "main.h"

/* defines */

#define     LCD12864_PORT_CLK        						RCC_AHB1Periph_GPIOB

#define     LCD12864_PORT                       GPIOB

#define     LCD12864_RST_PIN                    GPIO_Pin_14

#define     LCD12864_RST_L                      GPIO_ResetBits(LCD12864_PORT , LCD12864_RST_PIN)
#define     LCD12864_RST_H                      GPIO_SetBits(LCD12864_PORT , LCD12864_RST_PIN)

#define     LCD12864_CS_PIN                     GPIO_Pin_12

#define	    LCD12864_CS_L                       GPIO_ResetBits(LCD12864_PORT , LCD12864_CS_PIN)
#define     LCD12864_CS_H                       GPIO_SetBits(LCD12864_PORT , LCD12864_CS_PIN)

#define  		LCD12864_SCK_PIN										GPIO_Pin_13//对应SLK
#define			LCD12864_SDA_PIN										GPIO_Pin_15   
#define			LCD12864_SPI												SPI2

//lcd12864驱动IC驱动代码
//驱动方式:SPI
//版本:V0.1

//2010-6-3

//lcd12864模式设置
//4线串行模式

	    						  
//lcd12864控制用函数
 void LCD12864_Init(void);                          //LCD初始化
// void LCD12864_ShowString(char *chn);
void LcmClearTXT( void );
void LcmClearBMP( void );
void PutStr(unsigned char row,unsigned char col,char *puts);
void PutBMP(const char *puts);
void LCD12864_Run(char *pchar);
#endif
