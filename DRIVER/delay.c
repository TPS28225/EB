#include "delay.h" 
#include "main.h"

#define TIM_PERIOD 0xffffffff

void delay_init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(DELAY_TIMER_CLK, ENABLE); //ʱ��ʹ��
	TIM_TimeBaseStructure.TIM_Period = TIM_PERIOD; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������
	TIM_TimeBaseStructure.TIM_Prescaler =(60-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  1Mhz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���¼���ģʽ
	TIM_TimeBaseInit(DELAY_TIMER, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	TIM_SetCounter(DELAY_TIMER, 0);
	TIM_ARRPreloadConfig(DELAY_TIMER, ENABLE);
	TIM_Cmd(DELAY_TIMER, ENABLE);  	//ʹ��TIMx	
	
	NVIC_InitStructure.NVIC_IRQChannel = DELAY_TIMER_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ClearITPendingBit(DELAY_TIMER, TIM_IT_Update);  //���TIMx�����жϱ�־     	
	TIM_ITConfig(DELAY_TIMER,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIMx�ж�,��������ж�	
}								    

//void delay_us(u16 nus)
//{
//	TIM_SetCounter(DELAY_TIMER, 0);
//	TIM_Cmd(DELAY_TIMER, ENABLE);    //����ʱ��			
//	while(TIM_GetCounter(DELAY_TIMER)<=nus);
//	TIM_Cmd(DELAY_TIMER, DISABLE);    //�ر�ʱ��	
//}


//void delay_ms(u32 nms)
//{	
//	TIM_SetCounter(DELAY_TIMER, 0);
//	TIM_Cmd(DELAY_TIMER, ENABLE);    //����ʱ��			
////	while(TIM_GetCounter(DELAY_TIMER)<=nms*1000);
//	while(nms--)
//	{
//		while(TIM_GetCounter(DELAY_TIMER)<=1000);
//		TIM_SetCounter(DELAY_TIMER,0);
//	}
//	TIM_Cmd(DELAY_TIMER, DISABLE);   //�ر�ʱ��		
//}



void delay_us(u32 nus)
{
	u32 Start_time;	
	Start_time=TIM_GetCounter(DELAY_TIMER);
	if((TIM_PERIOD-Start_time)<=(nus+100))//��ӵ�100us��Ϊ������һ�����ʱ�䣬��û��̫�������
	{
		TIM_SetCounter(DELAY_TIMER,0);
		Start_time=0;
	}
	while((TIM_GetCounter(DELAY_TIMER)-Start_time)<=nus);
}

void delay_ms(u32 nms)
{
	u32 Start_time;
	Start_time=TIM_GetCounter(DELAY_TIMER);

	if((TIM_PERIOD-Start_time)<=(nms*1000+100))//��ӵ�100us��Ϊ������һ�����ʱ�䣬��û��̫�������
	{
		TIM_SetCounter(DELAY_TIMER,0);
		Start_time=0;
	}
	while((TIM_GetCounter(DELAY_TIMER)-Start_time)<=(nms*1000));
}


/***********************************************************************
��������:��ʱ��2���жϷ������ͳ�ʼ��
��    �ܣ�
���������
���������
��дʱ�䣺
�� д �ˣ�
ע    �⣺
***********************************************************************/  
void TIM2_IRQHandler(void)
{ 	
	if(TIM_GetITStatus(DELAY_TIMER, TIM_IT_Update) != RESET)//�Ǹ����ж�
	{	 			   
		
		TIM_ClearITPendingBit(DELAY_TIMER, TIM_IT_Update);  //���TIMx�����жϱ�־     
	}	    
}








