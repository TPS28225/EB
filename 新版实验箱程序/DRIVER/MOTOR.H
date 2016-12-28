/***********************************************************************
文件名称：LED.h
功    能：led  IO初始化
编写时间：2013.4.25
编 写 人：
注    意：
***********************************************************************/

#ifndef _MOTOR_H_
#define _MOTOR_H_
#include "main.h"

#define MOTOR_GPIO  GPIOA
#define MOTOR_PIN   GPIO_Pin_12

#define MOTOR_ON    GPIO_ResetBits(MOTOR_GPIO,MOTOR_PIN)
#define MOTOR_OFF   GPIO_SetBits(MOTOR_GPIO,MOTOR_PIN)


void MOTOR_Run(void);
void MOTOR_Configuration(void);	
void MOTOR_PWM_Init(u32 arr,u32 psc);
#endif
