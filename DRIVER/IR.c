#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "key.h"
/***********************************************************************

***********************************************************************/
IR_STRUCT IR;
u16 Timeval[IR_CODE_LEN];
int IR_LearnState=0;
extern u8 SOUND_Counter;
char IR_CODE[IR_CODE_LEN]="A:100;B:200;C:300;D:400;CODE:ABCDABCD;";


//void IR_Run(void)
//{
//	enCode(Timeval,INPUTDEVICE.IR_Code,71);
//}

void IR_Run(void)
{
	if(OUTPUTDEVICE.IR_State == 1)
	{
		//IR_Send(IR_CODE,strlen(IR_CODE));
		IR_Send(OUTPUTDEVICE.IR_Code,strlen(OUTPUTDEVICE.IR_Code));
		OUTPUTDEVICE.IR_State = 0;
	}
	else if(OUTPUTDEVICE.IR_State == 2)
	{
		IR_LearnEnable(1);
		OUTPUTDEVICE.IR_State = 0;
	}
	else if(OUTPUTDEVICE.IR_State == 3) 
	{
		IR_LearnEnable(0);
		OUTPUTDEVICE.IR_State = 0;
	}
	
	
	if(IR.LearnState == 0)
	{
		INPUTDEVICE.IR_State = 0;
//		memset(INPUTDEVICE.IR_Code,0,IRCODE_ARRY_NUM);
	}
	else if(IR.LearnState == 1)
	{
		INPUTDEVICE.IR_State = 4;
//		memset(INPUTDEVICE.IR_Code,0,IRCODE_ARRY_NUM);		
	}
	else if(IR.LearnState == 2)
	{
		INPUTDEVICE.IR_State = 5;	
		enCode(Timeval,INPUTDEVICE.IR_Code,IR.Len);
	}
}
void IR_Configuration(void)
{
	IR_EXTI_Init();
	TIM7_Int_Init(417,1);  
  TIM6_Int_Init(9,59);
	
	
	TIM12_Init(60000-1,59);
	TIM12_Set(0);
	EXTI6_Int(0);
}

void IR_Send(char* buff,u16 len)
{
	int i=0;
	char *buffPtr = buff;
	int codeBook[26] = {0};
	
	int codeLen;
	char pattern[3] = "A:";
	char * codePtr= strstr(buffPtr, "CODE:") + 5;
	char * pos = strstr(buffPtr, pattern);
		
	codeLen = len - (codePtr - buff);
	while((pos < codePtr-5) && (pos != 0))
	{	
		codeBook[pattern[0] - 'A'] = atoi(pos+2);
		pattern[0] ++ ;
		
		pos = strstr(buffPtr, pattern);
	}
	while((*codePtr) != ';' && (i<codeLen))
	{
		 IR.Code[i++]=codeBook[(*codePtr++) - 'A'];
	}
	IR.CodeLen=codeLen; 
	IR.freqGenerator=1;
	IR.SendIndex=0;
	IR.SendCnt=0;
	IR.Send=1;   
}
/***********************************************************************
发送时长控制函数
***********************************************************************/ 
void TIM6_DAC_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)  
	{
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  
		if(IR.Send==1)
		{
			if(IR.SendIndex<IR.CodeLen)
			{
				if(IR.SendCnt*10<IR.Code[IR.SendIndex])
				{
					IR.SendCnt++;
				}
				else
				{
					IR.freqGenerator=!IR.freqGenerator;
					IR.SendCnt=1;
					IR.SendIndex++;
				}
			}
			else
			{
				IR.Send=0;
				GPIO_ResetBits(GPIOG, GPIO_Pin_7);
			}
		}	
	}
}
/***********************************************************************
36KHZ方波初始化中断服务函数
***********************************************************************/ 
void TIM7_IRQHandler(void)
{	
	if (TIM_GetITStatus(TIM7,TIM_IT_Update) != RESET) 
	{
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update); 
		IR.SendTurnOver=!IR.SendTurnOver;		
		if(IR.Send==1)
		{
			if(IR.freqGenerator)
			{
				if(IR.SendTurnOver)
				{
					GPIO_SetBits(GPIOG, GPIO_Pin_7);
				}
				else
				{
					GPIO_ResetBits(GPIOG, GPIO_Pin_7);
				}
			}
			else
			{
				GPIO_ResetBits(GPIOG, GPIO_Pin_7);
			}
		}
  }			
}

/***********************************************************************
定时器初始化
定时器3：记录发送波长
定时器4：36KHZ波形发生器
***********************************************************************/ 

void TIM6_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
 
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	
	TIM_Cmd(TIM6, ENABLE);				 
}
void TIM7_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStructure);
 
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);

	TIM_Cmd(TIM7, ENABLE); 	
}
void IR_LearnEnable(u8 flag)
{
	if(flag)
	{
		if(IR.LearnState == 0)
		{
			IR.LearnState=1;
			TIM12_Set(1);
			EXTI6_Int(1);
			
			IR.CodeCnt=0;
			IR.LearnStart=0;	
		}			
	}
	else
	{
		IR.LearnState=0;
		TIM12_Set(0);
		EXTI6_Int(0);
	}
}
void IR_EXTI_Init(void)
{
 	EXTI_InitTypeDef EXTI_InitStructure;	
	GPIO_InitTypeDef GPIO_InitStructure; 
  NVIC_InitTypeDef NVIC_InitStructure;
	 
 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);            
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;           
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(GPIOG ,&GPIO_InitStructure); 
	GPIO_ResetBits(GPIOG, GPIO_Pin_7);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource6);

			/* 配置 EXTI LineXXX */
	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line6);  
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI6_Int(u8 en)
{
    EXTI->PR=1<<6;  
    if(en)EXTI->IMR|=1<<6;
    else EXTI->IMR&=~(1<<6);
}

void EXTI9_5_IRQHandler(void)
{
	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL();    // 关中断                               
	OSIntNesting++;	   		//中断嵌套层数，通知ucos
	OS_EXIT_CRITICAL();	   	//开中断
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line6);  
		TIM12_Set(0);            
		if(IR.LearnState==1)
		{
			if(IR.LearnStart==0)
			{
				IR.LearnStart=1;
			}
			else
			{
				Timeval[IR.CodeCnt++]=TIM12->CNT;
			}
			if(IR.CodeCnt>=IR_CODE_LEN)
			{
				IR.LearnState=2; 
				IR.Len=IR.CodeCnt;
				IR.CodeCnt=0;
				IR.LearnStart=0; 
			}
		}
		TIM12_Set(1);
	}
	if(EXTI_GetITStatus(EXTI_Line7) != RESET)
	{
    SOUND_Counter++;
		EXTI_ClearITPendingBit(EXTI_Line7);  //清除EXTI7线路挂起位
	}
	OSIntExit();//中断退出，通知ucos，（该句必须加）			
}

void TIM8_BRK_TIM12_IRQHandler(void)
{ 	
	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL();    // 关中断                               
	OSIntNesting++;	   		//中断嵌套层数，通知ucos
	OS_EXIT_CRITICAL();	   	//开中断	
	if(TIM_GetITStatus(TIM12, TIM_IT_Update) != RESET)
	{	
		TIM_ClearITPendingBit(TIM12, TIM_IT_Update);  
		if(IR.LearnState==1)
		{
			if(IR.CodeCnt>20)
			{
				IR.LearnState=2; 
				IR.Len=IR.CodeCnt;
				IR.CodeCnt=0;
				IR.LearnStart=0;
			}
			else
			{
				IR.LearnState=1; //等待接收红外码
				IR.CodeCnt=0;
				IR.LearnStart=0;
			}
		}
		TIM12_Set(1);
	}
	OSIntExit();//中断退出，通知ucos，（该句必须加）				
}
//学习超时定时器
void TIM12_Set(u8 sta)
{
	if(sta)
	{       
		TIM_SetCounter(TIM12,0); 
		TIM_Cmd(TIM12, ENABLE);  
	}else TIM_Cmd(TIM12, DISABLE); 
}
void TIM12_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);     
	
	TIM_TimeBaseInitStructure.TIM_Period = arr;  
	TIM_TimeBaseInitStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  

	TIM_TimeBaseInit(TIM12, &TIM_TimeBaseInitStructure); 
 
	TIM_ITConfig(TIM12,TIM_IT_Update,ENABLE ); 		

	NVIC_InitStructure.NVIC_IRQChannel = TIM8_BRK_TIM12_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}

typedef struct irCode{
	int count;
	long int value;	
}irEncode;

//红外编码
char* enCode(u16* code,char* encode,int lenth)
{
	int max=0,ave=0;
	int i=0,j=0,index=0;
	char encodeChar = 'A';
	char temp[10]={0};
	irEncode irencode[101]={0};
	int iraverage[101]={0};
	char iraverageIndex = 0;	
	
	
	for(i=0;i<lenth;i++)
	{
		if(max < code[i])
			max = code[i];
	}
	ave = max / 100;
	for(i=0;i<lenth;i++)
	{
		index = code[i]/ave;
		irencode[index].value += code[i];
		irencode[index].count++;
	}
	for(i=0;i<101;i++)
	{
		if(irencode[i].count != 0)
			irencode[i].value /= irencode[i].count;
	}	
	for(i=0;i<101;i++)
	{
		if(irencode[i].count != 0)
		{
			for(j=i+1;j<101;j++)
			{
				if(irencode[j].count!=0)
				{
					if(irencode[j].value - irencode[i].value < ave)
					{
						iraverage[iraverageIndex]=(irencode[j].value*irencode[j].count+irencode[i].value*irencode[i].count)/(irencode[i].count+irencode[j].count);
						i=j;
					}
					else
					{
						iraverage[iraverageIndex]=irencode[i].value;
						i=j-1;
					}
					iraverageIndex++;
					break;
				}
			}
			if(j==101)
			{
				iraverage[iraverageIndex]=irencode[i].value;			
			}
		}
	}
	sprintf(encode,"");
	for(i=0;i<iraverageIndex;i++)
	{
		if(i==iraverageIndex-1)
		{
			sprintf(temp,"%c:%d;",encodeChar+i,iraverage[i]);
		}
		else
		{
			sprintf(temp,"%c:%d,",encodeChar+i,iraverage[i]);
		}		
		strcat(encode,temp);		
	}
	sprintf(temp,"CODE:");
	strcat(encode,temp);	
	for(i=0;i<lenth;i++)
	{
		for(j=0;j<iraverageIndex;j++)
		{
			if(code[i]<=iraverage[j])
			{
				if(j==0)
				{
					sprintf(temp,"%c",'A'+j);
				}
				else if((code[i]-iraverage[j-1])>(iraverage[j]-code[i]))
				{
					sprintf(temp,"%c",'A'+j);
				}
				else
				{
					sprintf(temp,"%c",'A'+j-1);
				}
				strcat(encode,temp);
				break;
			}
		}
		if(j==iraverageIndex)
		{
			sprintf(temp,"%c",'A'+j-1);
			strcat(encode,temp);
		}
	}
	return encode;
}

