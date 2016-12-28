#ifndef __IR_H
#define __IR_H
#include "main.h"

#define IR_CODE_LEN 250

typedef struct{
//0   停止学习
//1   开始学习
//2   学习完成	
//u8 	OverTime;    //超时
	u8  LearnState;  //学习状态标记位
	u16 CodeCnt;     //学习次数记录
	u8  Len;         // 
	u8  LearnStart;  //学习开始标志位
	u8  Send;        //发送使能
	u16 SendIndex;   //发送时间片信息位置
  u16 SendCnt;    //用来记录发送波形持续时间
	u8  freqGenerator; //频率发生器 1 生成36KHZ方波，0 无效
	u8  SendTurnOver;//36Khz波形生成
	u16 Code[IR_CODE_LEN];   //学到的红外码时间片信息
	u16 CodeLen;     //学到的红外码长度
}IR_STRUCT;
void IR_Configuration(void);
void IR_Run(void);
void IR_Send(char* buff,u16 len);
void TIM6_Int_Init(u16 arr,u16 psc);
void TIM7_Int_Init(u16 arr,u16 psc);
void TIM12_Init(u16 arr,u16 psc);
void TIM12_Set(u8 sta);
void EXTI6_Int(u8 en);
void IR_EXTI_Init(void);
void IR_LearnEnable(u8 flag);
char* enCode(u16* code,char* encode,int lenth);
#endif


