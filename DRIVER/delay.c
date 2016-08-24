#include "delay.h" 
#include "main.h"

#define TIM_PERIOD 0xffffffff

void delay_init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(DELAY_TIMER_CLK, ENABLE); //时钟使能
	TIM_TimeBaseStructure.TIM_Period = TIM_PERIOD; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到
	TIM_TimeBaseStructure.TIM_Prescaler =(60-1); //设置用来作为TIMx时钟频率除数的预分频值  1Mhz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向下计数模式
	TIM_TimeBaseInit(DELAY_TIMER, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_SetCounter(DELAY_TIMER, 0);
	TIM_ARRPreloadConfig(DELAY_TIMER, ENABLE);
	TIM_Cmd(DELAY_TIMER, ENABLE);  	//使能TIMx	
	
	NVIC_InitStructure.NVIC_IRQChannel = DELAY_TIMER_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ClearITPendingBit(DELAY_TIMER, TIM_IT_Update);  //清除TIMx更新中断标志     	
	TIM_ITConfig(DELAY_TIMER,TIM_IT_Update,ENABLE ); //使能指定的TIMx中断,允许更新中断	
}								    

//void delay_us(u16 nus)
//{
//	TIM_SetCounter(DELAY_TIMER, 0);
//	TIM_Cmd(DELAY_TIMER, ENABLE);    //开启时钟			
//	while(TIM_GetCounter(DELAY_TIMER)<=nus);
//	TIM_Cmd(DELAY_TIMER, DISABLE);    //关闭时钟	
//}


//void delay_ms(u32 nms)
//{	
//	TIM_SetCounter(DELAY_TIMER, 0);
//	TIM_Cmd(DELAY_TIMER, ENABLE);    //开启时钟			
////	while(TIM_GetCounter(DELAY_TIMER)<=nms*1000);
//	while(nms--)
//	{
//		while(TIM_GetCounter(DELAY_TIMER)<=1000);
//		TIM_SetCounter(DELAY_TIMER,0);
//	}
//	TIM_Cmd(DELAY_TIMER, DISABLE);   //关闭时钟		
//}



void delay_us(u32 nus)
{
	u32 Start_time;	
	Start_time=TIM_GetCounter(DELAY_TIMER);
	if((TIM_PERIOD-Start_time)<=(nus+100))//多加的100us是为了留出一点空余时间，并没有太大的意义
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

	if((TIM_PERIOD-Start_time)<=(nms*1000+100))//多加的100us是为了留出一点空余时间，并没有太大的意义
	{
		TIM_SetCounter(DELAY_TIMER,0);
		Start_time=0;
	}
	while((TIM_GetCounter(DELAY_TIMER)-Start_time)<=(nms*1000));
}


/***********************************************************************
函数名称:定时器2的中断服务函数和初始化
功    能：
输入参数：
输出参数：
编写时间：
编 写 人：
注    意：
***********************************************************************/  
void TIM2_IRQHandler(void)
{ 	
	if(TIM_GetITStatus(DELAY_TIMER, TIM_IT_Update) != RESET)//是更新中断
	{	 			   
		
		TIM_ClearITPendingBit(DELAY_TIMER, TIM_IT_Update);  //清除TIMx更新中断标志     
	}	    
}








