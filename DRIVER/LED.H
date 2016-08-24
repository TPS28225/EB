/***********************************************************************
文件名称：LED.h
功    能：led  IO初始化
编写时间：2013.4.25
编 写 人：
注    意：
***********************************************************************/

#ifndef _LED_H_
#define _LED_H_

void LED_Run(void);
void LED_Configuration(void);
void LED_PWM_Init(u32 arr,u32 psc);
#endif
