#include "main.h"


void MOTOR_Run(void)
{
	static char Motor_Speed_Current=1;
	if(Motor_Speed_Current!=OUTPUTDEVICE.Motor)	
	{
		Motor_Speed_Current = OUTPUTDEVICE.Motor;
		if(OUTPUTDEVICE.Motor < 0)
		{
			MOTOR_ON;
			TIM_SetCompare4(TIM1,0);
			TIM_SetCompare1(TIM1,(0-Motor_Speed_Current)*10);			
		}
		else if(OUTPUTDEVICE.Motor > 0)
		{
			MOTOR_ON;
			TIM_SetCompare1(TIM1,0);
			TIM_SetCompare4(TIM1,Motor_Speed_Current*10);
		}
		else
		{
			MOTOR_OFF;
			TIM_SetCompare1(TIM1,0);
			TIM_SetCompare4(TIM1,0);
		}
	}
}

void MOTOR_Configuration(void)
{
	MOTOR_PWM_Init(1000,119);
}

void MOTOR_PWM_Init(u32 arr,u32 psc)
{		 					 	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	//TIM1时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTA时钟	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_TIM1);
	
	GPIO_InitStructure.GPIO_Pin =  MOTOR_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(MOTOR_GPIO, &GPIO_InitStructure);	
	MOTOR_OFF;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11;           //GPIOA8 11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PA8 11
	
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//初始化定时器1
	
	//初始化TIM1Channel1 4 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 OC1	 
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 OC4	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM1在CCR1上的预装载寄存器
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM1在CCR4上的预装载寄存器
  TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPE使能 	高级定时器需要
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	TIM_SetCompare1(TIM1,0);	
	TIM_SetCompare4(TIM1,0);
	TIM_Cmd(TIM1, ENABLE);  //使能TIM1

}  
