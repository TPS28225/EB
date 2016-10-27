#include "main.h"
/***********************************************************************
驱动名称：H34B  H3V4F
功能描述：射频收发   基于EV1527编码
用到外设：外部中断2       IO:PC2 中断优先级 0-2
					定时器5                中断优先级 0-3
					定时器3PWM输出  IO:PA7 中断优先级 2-1
时    间: 2015/12/15
***********************************************************************/
RF_STRUCT Rf;

u16 RFTimeBuff[200];

int RF_StatusCheck()
{
  if(Rf.SendEnable==0)
	{
		return  0;
	}
	else
	{
	
		return  1;
	}
} 
/***********************************************************************
函数名称: RF_H3V4F_Rev 函数
功    能: 接收射频波形，并对其进行解码
输入参数：*buff 接收数据的数组，没次接收3组数据，每组数据3个字节
输出参数：无
编写时间：
编 写 人：
注    意：
***********************************************************************/
u8 RF_H3V4F_Rev(u32 *data)
{
	u16 i=0,j=8,k=0;
	u8 buff[9];
	u32 decOut[3];
	
	if(Rf.State==1)
	{
		for(i=1;i<49;i+=2)
		{
			if(RFTimeBuff[i]<RFTimeBuff[i+1])
			{
				buff[k] &= ~(1<<(j-1));
			}
			else 
			{  
				buff[k] |= (1<<(j-1));
			}  
			j--;
			if(j==0) j=8,k++;
		}
//		decOut[0] = buff[0];
//		decOut[1] = buff[1];
//		decOut[2] = buff[2];
//	 
//		Rf.State = 0;
//	  Rf.Count = 0;
//		return 1;
		#if 1
		for(i=51;i<99;i+=2)
		{
			if(RFTimeBuff[i]<RFTimeBuff[i+1])
			{
				buff[k] &= ~(1<<(j-1));
			}
			else 
			{
				buff[k] |= (1<<(j-1));
			}
			j--;
			if(j==0) j=8,k++;
		}
		for(i=101;i<149;i+=2)
		{
			if(RFTimeBuff[i]<RFTimeBuff[i+1])
			{
				buff[k] &= ~(1<<(j-1));
			}
			else 
			{
				buff[k] |= (1<<(j-1));
			}
			j--;
			if(j==0) j=8,k++;
		}
		
		if(((buff[0] == buff[3]) && (buff[1] == buff[4]) && (buff[2] == buff[5]))
		 ||((buff[0] == buff[6]) && (buff[1] == buff[7]) && (buff[2] == buff[8])))
		 {
				decOut[0] = buff[0];
				decOut[1] = buff[1];
				decOut[2] = buff[2];
			 
				*data=(decOut[0]<<16)+(decOut[1]<<8)+decOut[2];//可能出错
				Rf.State = 0;
			  Rf.Count = 0;
				return 1;
		 }
		 else if((buff[3] == buff[6]) && (buff[4] == buff[7]) && (buff[5] == buff[8]))
		 {
				decOut[0] = buff[3];
				decOut[1] = buff[4];
				decOut[2] = buff[5];
			 		 
				*data=(decOut[0]<<16)+(decOut[1]<<8)+decOut[2];//可能出错
				Rf.State = 0;
			  Rf.Count = 0;
				return 1;
		 }
		 else
		 {
				decOut[0] = 0;
				decOut[1] = 0;
				decOut[2] = 0;
			 
				data=0;
				Rf.State = 0;
			  Rf.Count = 0;
				return 0;
		 }
		#endif
	}else
		data=0;
		return 0;
}

/***********************************************************************
函数名称: RF_H34B_Send   
功    能：H34B的发射函数，主要是使能定期器PWM输出波形，
					具体波形生成在中断服务函数
输入参数：RF_ENCODE_DATA   要发送的24位码   高8位无意义
输出参数：无
编写时间：
编 写 人：
注    意：
***********************************************************************/ 
void RF_H34B_Send(u32 data)
{
//	CC1101EV1527Init();
//	halSpiStrobe(CCxxx0_STX);
	TIM13_Set(1);
	TIM14_Set(0);
	Rf.SendData=data;
	Rf.SendEnable=1;
}
/***********************************************************************
函数名称: 射频初始化
功    能：外部中断2的配置初始化  IO: PC2
输入参数：无
输出参数：无
编写时间：
编 写 人：
注    意：中断优先级  0-2
***********************************************************************/  
void RF_EXTI_Init(void)
{
 	EXTI_InitTypeDef EXTI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RF_RX_PORT_CLK, ENABLE);
  RCC_AHB1PeriphClockCmd(RF_TX_PORT_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource10);

	GPIO_InitStructure.GPIO_Pin = RF_TX_PIN;           
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(RF_TX_PORT, &GPIO_InitStructure); 	

	GPIO_InitStructure.GPIO_Pin = RF_RX_PIN;           
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(RF_RX_PORT, &GPIO_InitStructure); 	
	
  EXTI_InitStructure.EXTI_Line=RF_RX_EXIT_LINE;	
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}
/***********************************************************************
函数名称: 外部中断10服务程序
功能描述：主要是接收射频波形，记录时间片信息
输入参数：无
输出参数：无
编写时间：
编 写 人：
注    意：1.进入中断先关闭定时器，出中断开启定时器		
					2.先滤波，当判断收到两次同步头时，开始记录数据
***********************************************************************/  
//在UltrasonicWave.c中

/***********************************************************************
函数名称:定时器14的中断服务函数和初始化
功    能：一旦定时器5进入中断，清除同步头的数据，从头开始计数
输入参数：
输出参数：
编写时间：
编 写 人：
注    意：定时器14的设置主要是为接收波形服务，初始化时50ms进入中断
					一旦进入中断，接收波形从新开始
					中断优先级  0-3
***********************************************************************/  
void TIM8_TRG_COM_TIM14_IRQHandler(void)
{ 	
	if(TIM_GetITStatus(RF_RX_TIMER, TIM_IT_Update) != RESET)//是更新中断
	{	
		TIM_ClearITPendingBit(RF_RX_TIMER, TIM_IT_Update);  //清除TIMx更新中断标志    
		Rf.HeadFlag=0;
		Rf.ZaboFlag=1;
		Rf.Count=0;
		TIM14_Set(1);
	}	    
}
void TIM14_Set(u8 sta)
{
	if(sta)
	{       
		TIM_SetCounter(RF_RX_TIMER,0);//计数器清空
		TIM_Cmd(RF_RX_TIMER, ENABLE);  //使能TIMx	
	}else TIM_Cmd(RF_RX_TIMER, DISABLE);//关闭定时器5 
}
void TIM14_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RF_RX_TIMER_CLK, ENABLE); //时钟使能//TIM5时钟使能    
	
	TIM_TimeBaseInitStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseInitStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式

	TIM_TimeBaseInit(RF_RX_TIMER, &TIM_TimeBaseInitStructure); //根据指定的参数初始化TIMx的时间基数单位	
	TIM_ITConfig(RF_RX_TIMER,TIM_IT_Update,ENABLE ); //使能指定的TIM5中断,允许更新中断						 

	NVIC_InitStructure.NVIC_IRQChannel = TIM8_TRG_COM_TIM14_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}

/***********************************************************************
函数名称: 定时器13初始化
功    能：定时器13主要是为发送波形设置，生成不同占空比的方波
输入参数：
输出参数：
编写时间：
编 写 人：
注    意：中断优先级 2-1    IO:PA7
***********************************************************************/ 
void TIM13_Init(u16 arr,u16 psc)
{		 			
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RF_TX_TIMER_CLK, ENABLE); //时钟使能//TIM13时钟使能    
	
	TIM_TimeBaseInitStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseInitStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	
	TIM_TimeBaseInit(RF_TX_TIMER, &TIM_TimeBaseInitStructure); //根据指定的参数初始化TIMx的时间基数单位 
	TIM_ITConfig(RF_TX_TIMER,TIM_IT_Update,ENABLE ); //使能指定的TIM13中断,允许更新中断	                   
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}  
/***********************************************************************
函数名称:定时器13中断服务函数
功    能：根据要发送数据的每一位高低发送延时
输入参数：
输出参数：
编写时间：
编 写 人：
注    意：//将4T压缩为1T
***********************************************************************/ 
void TIM8_UP_TIM13_IRQHandler(void)
{ 	
	if(TIM_GetITStatus(RF_TX_TIMER, TIM_IT_Update) != RESET)//是更新中断
	{	
		Rf.SendTime++;
		if(Rf.SendEnable==1) 
		{
			//Rf.SendFlag有三个状态，0发送同步字节，1发送数据1，2发送数据0
			if(Rf.SendFlag==0)  //发送同步字节
			{
				if(Rf.SendTime==1)
				{
					if(Rf.SendCount==5)
					{
						Rf.SendEnable=0;
						Rf.SendCount=0;
						Rf.SendTime=0;
						Rf.SendFlag=0;
						//CC1101_Init();	
						//CC1101EV1527Init();
						//halSpiStrobe(CCxxx0_SRX);
						//GPIO_ResetBits(RF_TX_PORT,RF_TX_PIN);						
						 
						TIM14_Set(0);
						TIM13_Set(1);
					}						
					GPIO_SetBits(RF_TX_PORT,RF_TX_PIN);
				}
				else
				{
					GPIO_ResetBits(RF_TX_PORT,RF_TX_PIN);				
					if(Rf.SendTime==32)
					{
						Rf.SendTime=0;
						if(Rf.SendData&(1<<(23-Rf.Movecnt)))
						{
							Rf.SendFlag=1;
						}else Rf.SendFlag=2;
						Rf.Movecnt++;
					}
				}
			}else if(Rf.SendFlag==1) //发送“1”
			{
				if(Rf.SendTime<=3)							//一共要发送四次
				{
					GPIO_SetBits(RF_TX_PORT,RF_TX_PIN);				
				}
				else
				{
					GPIO_ResetBits(RF_TX_PORT,RF_TX_PIN);				
					Rf.SendTime=0;
					if(Rf.Movecnt<24)						 //判断24位是否发送完成
					{
						if(Rf.SendData&(1<<(23-Rf.Movecnt)))//判断下一次发送0还是1
						{
							Rf.SendFlag=1;
						}else Rf.SendFlag=2;
						Rf.Movecnt++;
					}else
					{
						Rf.SendCount++;
						Rf.SendFlag=0;
						Rf.Movecnt=0;
						Rf.SendTime=0;
					}
				}					
			}else if(Rf.SendFlag==2) //发送“0”
			{
				if(Rf.SendTime==1)
				{
					GPIO_SetBits(RF_TX_PORT,RF_TX_PIN);				
				}
				else
				{
					GPIO_ResetBits(RF_TX_PORT,RF_TX_PIN);				
					if(Rf.SendTime==4)
					{
						Rf.SendTime=0;
						if(Rf.Movecnt<24)
						{
							if(Rf.SendData&(1<<(23-Rf.Movecnt)))
							{
								Rf.SendFlag=1;
							}else Rf.SendFlag=2;
							Rf.Movecnt++;
						}else
						{
							Rf.SendCount++;
							Rf.SendFlag=0;
							Rf.Movecnt=0;
							Rf.SendTime=0;
						}
					}
				}					
			}			
		}		
		TIM_ClearITPendingBit(RF_TX_TIMER, TIM_IT_Update);  //清除TIMx更新中断标志     
	}	    
}
void TIM13_Set(u8 sta)
{
	if(sta)
	{       
		TIM_SetCounter(RF_TX_TIMER,0);//计数器清空
		TIM_Cmd(RF_TX_TIMER, ENABLE);  //使能TIMx	
	}else TIM_Cmd(RF_TX_TIMER, DISABLE);//关闭定时器13
}

void EXTI10_Int(u8 en)
{
    EXTI->PR=1<<10;  
    if(en)EXTI->IMR|=1<<10;
    else EXTI->IMR&=~(1<<10);
}
/***********************************************************************
函数名称:系统初始化函数
功    能：
输入参数：
输出参数：
编写时间：
编 写 人：
注    意：
***********************************************************************/ 
void RF_H3V4_H34B_Init(void)
{
	RF_EXTI_Init();
	TIM14_Init(60000,59);
	TIM14_Set(1);
	TIM13_Init(300,59);//300us周期
	TIM13_Set(0);
 	Rf.ZaboFlag=1;   //滤除杂波
}

void EV1527_Run(void)
{
	if(OUTPUTDEVICE.RF_State == 1){
		RF_H34B_Send(OUTPUTDEVICE.RF_Code);
		OUTPUTDEVICE.RF_State = 0;
	}
	else if(OUTPUTDEVICE.RF_State == 2){
		INPUTDEVICE.RF_State=4;
		while(RF_H3V4F_Rev(&(INPUTDEVICE.RF_Code))==0){
			if(OUTPUTDEVICE.RF_State == 3){
				OUTPUTDEVICE.RF_State = 0;
				break;
			}
		}
		if(OUTPUTDEVICE.RF_State != 0){	
			OUTPUTDEVICE.RF_State = 0;
			INPUTDEVICE.RF_State=6;
		}			
	}
}




















