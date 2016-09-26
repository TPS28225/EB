/******************** (C) 1209 Lab **************************
 * 文件名  : UltrasonicWave.c
 * 描述    ：超声波测距模块，UltrasonicWave_Configuration（）函数
             初始化超声模块，UltrasonicWave_StartMeasure（）函数
			 启动测距，并将测得的数据通过串口1打印出来         
 * 实验平台：Mini STM32开发板  STM32F103RBT6
 * 硬件连接：------------------
 *          | PC8  - TRIG      |
 *          | PC7  - ECHO      |
 *           ------------------
 * 库版本  ：ST3.5.0
 *
 * 作者    ：Lee 
*********************************************************************************/

#include "main.h"
#include "UltrasonicWave.h"
FlagStatus ECHO_COUNT_START = RESET;
FlagStatus ECHO_PIN_STATE = RESET; 
/*
 * 函数名：UltrasonicWave_Configuration
 * 描述  ：超声波模块的初始化
 * 输入  ：无
 * 输出  ：无	
 */
void UltrasonicWave_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	EXTI_InitTypeDef EXTI_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(TRIG_PORT_CLK, ENABLE); 						 			
	GPIO_InitStructure.GPIO_Pin = TRIG_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(TRIG_PORT, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(ECHO_PORT_CLK, ENABLE); 
	GPIO_InitStructure.GPIO_Pin = ECHO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(ECHO_PORT, &GPIO_InitStructure);	

	RCC_APB2PeriphClockCmd(UltrasonicWave_EXIT_CLK, ENABLE);	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource11);
	
		/* 配置 EXTI LineXXX */
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line11);  //清除EXTI15_10线路挂起位
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x05;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	RCC_APB2PeriphClockCmd(UltrasonicWave_TIMER_CLK, ENABLE); //时钟使能
	TIM_TimeBaseStructure.TIM_Period = 60000-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =(1200-1); //设置用来作为TIMx时钟频率除数的预分频值  100Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(UltrasonicWave_TIMER, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_SetCounter(UltrasonicWave_TIMER,0);
	TIM_Cmd(UltrasonicWave_TIMER, DISABLE);			                                 //定时器失能
}

/*
 * 函数名：UltrasonicWave_StartMeasure
 * 描述  ：开始测距，发送一个>10us的脉冲，然后测量返回的高电平时间
 * 输入  ：无
 * 输出  ：无	
 */
void UltrasonicWave_StartMeasure(void)
{	
	if(ECHO_COUNT_START == RESET)
	{
		INPUTDEVICE.Distance=0;
		GPIO_SetBits(TRIG_PORT,TRIG_PIN);//送>10US的高电平ltrasonicWave_PORT,TRIG_PIN这两个在define中有?
		delay_us(20);		                      //延时20US
		GPIO_ResetBits(TRIG_PORT,TRIG_PIN);
		delay_us(30);	
	}
}
extern u16 RFTimeBuff[200];
void EXTI15_10_IRQHandler(void)
{
	OS_CPU_SR cpu_sr;
	float UltrasonicWave_Distance=0;      //计算出的距离  
	OS_ENTER_CRITICAL();    // 关中断                               
	OSIntNesting++;	   		//中断嵌套层数，通知ucos
	OS_EXIT_CRITICAL();	   	//开中断
	if(EXTI_GetITStatus(EXTI_Line11) != RESET)
	{
    ECHO_PIN_STATE=(FlagStatus)GPIO_ReadInputDataBit(ECHO_PORT, ECHO_PIN); 
		
		if((ECHO_PIN_STATE==SET)&&ECHO_COUNT_START == RESET)                
		{
			ECHO_COUNT_START = SET;
			TIM_SetCounter(UltrasonicWave_TIMER,0); 
			TIM_Cmd(UltrasonicWave_TIMER, ENABLE);    //开启时钟			
		}
		else if((ECHO_PIN_STATE==RESET)&&(ECHO_COUNT_START == SET))                
		{
			ECHO_COUNT_START = RESET;
			TIM_Cmd(UltrasonicWave_TIMER, DISABLE);   
			UltrasonicWave_Distance = TIM_GetCounter(UltrasonicWave_TIMER)*0.17;									 //计算距离&&UltrasonicWave_Distance<150
		}		
		else if((ECHO_PIN_STATE==SET)&&(ECHO_COUNT_START == SET))
 		{	
			ECHO_COUNT_START = RESET;						
			TIM_Cmd(UltrasonicWave_TIMER, DISABLE);			                                 //定时器2失能
			TIM_SetCounter(UltrasonicWave_TIMER,0);
		}
		else if((ECHO_PIN_STATE==RESET)&&(ECHO_COUNT_START == RESET))
 		{	
			ECHO_COUNT_START = RESET;
			TIM_Cmd(UltrasonicWave_TIMER, DISABLE);			                                 //定时器2失能
			TIM_SetCounter(UltrasonicWave_TIMER,0);
		}

		if(UltrasonicWave_Distance>0)
		{
			if(UltrasonicWave_Distance>2000)INPUTDEVICE.Distance=2000;
			else INPUTDEVICE.Distance = UltrasonicWave_Distance;

		}
			
		EXTI_ClearITPendingBit(EXTI_Line11);  //清除EXTI11线路挂起位
	}
	
	if(EXTI_GetITStatus(RF_RX_EXIT_LINE) != RESET)
	{
		EXTI_ClearITPendingBit(RF_RX_EXIT_LINE);  //清除LINE10上的中断标志位 
		TIM14_Set(0);              //关闭定时器
		if(Rf.ZaboFlag==1)       //使能滤波
		{
			if(Rf.Count >= RF_CONT)     //判断数据上报是否完成，完成继续，未完成退出等待完成
				return;
					
			Rf.TimeVal=TIM14->CNT;
			if((Rf.TimeVal>3000)&&(Rf.TimeVal<14000))  //判断是否为同步头
			{
				if(Rf.HeadFlag==0)
					Rf.HeadFlag=1;                  //接收到1次同步头
				else if(Rf.HeadFlag==1)
				{
					Rf.HeadFlag=0;               //接收到2次同步头
					Rf.ZaboFlag=0;							//滤波结束
					Rf.Count=0;		
					RFTimeBuff[Rf.Count]=TIM14->CNT;
					Rf.Count++;
				}
			}
		}else if(Rf.ZaboFlag==0)
		{
			/*
			if((TIM14->CNT) < 50)
			{
			  TIM14->CNT += RFTimeBuff[Rf.Count - 1];
				Rf.Count --;
			}
			else
			*/
			{
				RFTimeBuff[Rf.Count]=TIM14->CNT;
				//接收数据过程中如果收到高低电平时间超出范围则认为该码无效
				if(RFTimeBuff[Rf.Count]<150 || RFTimeBuff[Rf.Count]>15000)				
				{
					Rf.ZaboFlag=1;
					Rf.Count=0;
					TIM14_Set(1);
					return;
				}
				Rf.Count++;
				if(Rf.Count >= RF_CONT)   //接收数据超过150个，接收完成，使能上报
				{
					Rf.State=1;
					Rf.ZaboFlag=1;
					TIM14_Set(1);
					return;
				}
			}
		}
		TIM14_Set(1);
	}
	OSIntExit();//中断退出，通知ucos，（该句必须加）	
}

/******************* (C) 1209 Lab *****END OF FILE************/
