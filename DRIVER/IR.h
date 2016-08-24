#ifndef __IR_H
#define __IR_H
#include "main.h"

#define IR_CODE_LEN 250

typedef struct{
//0   ֹͣѧϰ
//1   ��ʼѧϰ
//2   ѧϰ���	
//u8 	OverTime;    //��ʱ
	u8  LearnState;  //ѧϰ״̬���λ
	u16 CodeCnt;     //ѧϰ������¼
	u8  Len;         // 
	u8  LearnStart;  //ѧϰ��ʼ��־λ
	u8  Send;        //����ʹ��
	u16 SendIndex;   //����ʱ��Ƭ��Ϣλ��
  u16 SendCnt;    //������¼���Ͳ��γ���ʱ��
	u8  freqGenerator; //Ƶ�ʷ����� 1 ����36KHZ������0 ��Ч
	u8  SendTurnOver;//36Khz��������
	u16 Code[IR_CODE_LEN];   //ѧ���ĺ�����ʱ��Ƭ��Ϣ
	u16 CodeLen;     //ѧ���ĺ����볤��
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


