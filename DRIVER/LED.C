#include "main.h"

u8 led_count = 0;
void LED_Run(void)
{
	led_count = ! led_count;
	if(led_count == 0)
	{
		TIM_SetCompare3(TIM4, 0);	
		TIM_SetCompare4(TIM4, 0);	
		TIM_SetCompare2(TIM4, 0);	
		TIM_SetCompare1(TIM4, 0);
		TIM_SetCompare2(TIM3, 0);	
		TIM_SetCompare1(TIM3, 0);	
		TIM_SetCompare4(TIM3, 0);	
		TIM_SetCompare3(TIM3, 0);			
	}
	else
	{
		TIM_SetCompare3(TIM4,100);	
		TIM_SetCompare4(TIM4,100);	
		TIM_SetCompare2(TIM4,100);	
		TIM_SetCompare1(TIM4,100);
		TIM_SetCompare2(TIM3,100);	
		TIM_SetCompare1(TIM3,100);	
		TIM_SetCompare4(TIM3,100);	
		TIM_SetCompare3(TIM3,100);			
	}
//	TIM_SetCompare3(TIM4,OUTPUTDEVICE.LED[0]*10);	
//	TIM_SetCompare4(TIM4,OUTPUTDEVICE.LED[1]*10);	
//	TIM_SetCompare2(TIM4,OUTPUTDEVICE.LED[2]*10);	
//	TIM_SetCompare1(TIM4,OUTPUTDEVICE.LED[3]*10);
//	TIM_SetCompare2(TIM3,OUTPUTDEVICE.LED[4]*10);	
//	TIM_SetCompare1(TIM3,OUTPUTDEVICE.LED[5]*10);	
//	TIM_SetCompare4(TIM3,OUTPUTDEVICE.LED[6]*10);	
//	TIM_SetCompare3(TIM3,OUTPUTDEVICE.LED[7]*10);	
}
//u8 led_count = 0;
//void LED_Run(void)
//{
//	led_count++;
//	if(led_count == 1)
//	{
//		TIM_SetCompare3(TIM4, 100);	
//		TIM_SetCompare4(TIM4, 0);	
//		TIM_SetCompare2(TIM4, 0);	
//		TIM_SetCompare1(TIM4, 0);
//		TIM_SetCompare2(TIM3, 0);	
//		TIM_SetCompare1(TIM3, 0);	
//		TIM_SetCompare4(TIM3, 0);	
//		TIM_SetCompare3(TIM3, 0);
//	}else if(led_count == 2)
//	{
//		TIM_SetCompare3(TIM4, 0);	
//		TIM_SetCompare4(TIM4, 100);	
//		TIM_SetCompare2(TIM4, 0);	
//		TIM_SetCompare1(TIM4, 0);
//		TIM_SetCompare2(TIM3, 0);	
//		TIM_SetCompare1(TIM3, 0);	
//		TIM_SetCompare4(TIM3, 0);	
//		TIM_SetCompare3(TIM3, 0);		
//	}else if(led_count == 3)
//	{
//		TIM_SetCompare3(TIM4, 0);	
//		TIM_SetCompare4(TIM4, 0);	
//		TIM_SetCompare2(TIM4, 100);	
//		TIM_SetCompare1(TIM4, 0);
//		TIM_SetCompare2(TIM3, 0);	
//		TIM_SetCompare1(TIM3, 0);	
//		TIM_SetCompare4(TIM3, 0);	
//		TIM_SetCompare3(TIM3, 0);		
//	}else if(led_count == 4)
//	{
//		TIM_SetCompare3(TIM4, 0);	
//		TIM_SetCompare4(TIM4, 0);	
//		TIM_SetCompare2(TIM4, 0);	
//		TIM_SetCompare1(TIM4, 100);
//		TIM_SetCompare2(TIM3, 0);	
//		TIM_SetCompare1(TIM3, 0);	
//		TIM_SetCompare4(TIM3, 0);	
//		TIM_SetCompare3(TIM3, 0);		
//	}else if(led_count == 5)
//	{
//		TIM_SetCompare3(TIM4, 0);	
//		TIM_SetCompare4(TIM4, 0);	
//		TIM_SetCompare2(TIM4, 0);	
//		TIM_SetCompare1(TIM4, 0);
//		TIM_SetCompare2(TIM3, 100);	
//		TIM_SetCompare1(TIM3, 0);	
//		TIM_SetCompare4(TIM3, 0);	
//		TIM_SetCompare3(TIM3, 0);		
//	}else if(led_count == 6)
//	{
//		TIM_SetCompare3(TIM4, 0);	
//		TIM_SetCompare4(TIM4, 0);	
//		TIM_SetCompare2(TIM4, 0);	
//		TIM_SetCompare1(TIM4, 0);
//		TIM_SetCompare2(TIM3, 0);	
//		TIM_SetCompare1(TIM3, 100);	
//		TIM_SetCompare4(TIM3, 0);	
//		TIM_SetCompare3(TIM3, 0);		
//	}else if(led_count == 7)
//	{
//		TIM_SetCompare3(TIM4, 0);	
//		TIM_SetCompare4(TIM4, 0);	
//		TIM_SetCompare2(TIM4, 0);	
//		TIM_SetCompare1(TIM4, 0);
//		TIM_SetCompare2(TIM3, 0);	
//		TIM_SetCompare1(TIM3, 0);	
//		TIM_SetCompare4(TIM3, 100);	
//		TIM_SetCompare3(TIM3, 0);		
//	}else if(led_count == 8)
//	{
//		TIM_SetCompare3(TIM4, 0);	
//		TIM_SetCompare4(TIM4, 0);	
//		TIM_SetCompare2(TIM4, 0);	
//		TIM_SetCompare1(TIM4, 0);
//		TIM_SetCompare2(TIM3, 0);	
//		TIM_SetCompare1(TIM3, 0);	
//		TIM_SetCompare4(TIM3, 0);	
//		TIM_SetCompare3(TIM3, 100);		
//	}else	if(led_count == 9)
//	{
//		TIM_SetCompare3(TIM4, 0);	
//		TIM_SetCompare4(TIM4, 0);	
//		TIM_SetCompare2(TIM4, 0);	
//		TIM_SetCompare1(TIM4, 0);
//		TIM_SetCompare2(TIM3, 0);	
//		TIM_SetCompare1(TIM3, 0);	
//		TIM_SetCompare4(TIM3, 100);	
//		TIM_SetCompare3(TIM3, 0);
//	}else if(led_count == 10)
//	{
//		TIM_SetCompare3(TIM4, 0);	
//		TIM_SetCompare4(TIM4, 0);	
//		TIM_SetCompare2(TIM4, 0);	
//		TIM_SetCompare1(TIM4, 0);
//		TIM_SetCompare2(TIM3, 0);	
//		TIM_SetCompare1(TIM3, 100);	
//		TIM_SetCompare4(TIM3, 0);	
//		TIM_SetCompare3(TIM3, 0);		
//	}else if(led_count == 11)
//	{
//		TIM_SetCompare3(TIM4, 0);	
//		TIM_SetCompare4(TIM4, 0);	
//		TIM_SetCompare2(TIM4, 0);	
//		TIM_SetCompare1(TIM4, 0);
//		TIM_SetCompare2(TIM3, 100);	
//		TIM_SetCompare1(TIM3, 0);	
//		TIM_SetCompare4(TIM3, 0);	
//		TIM_SetCompare3(TIM3, 0);		
//	}else if(led_count == 12)
//	{
//		TIM_SetCompare3(TIM4, 0);	
//		TIM_SetCompare4(TIM4, 0);	
//		TIM_SetCompare2(TIM4, 0);	
//		TIM_SetCompare1(TIM4, 100);
//		TIM_SetCompare2(TIM3, 0);	
//		TIM_SetCompare1(TIM3, 0);	
//		TIM_SetCompare4(TIM3, 0);	
//		TIM_SetCompare3(TIM3, 0);		
//	}else if(led_count == 13)
//	{
//		TIM_SetCompare3(TIM4, 0);	
//		TIM_SetCompare4(TIM4, 0);	
//		TIM_SetCompare2(TIM4, 100);	
//		TIM_SetCompare1(TIM4, 0);
//		TIM_SetCompare2(TIM3, 0);	
//		TIM_SetCompare1(TIM3, 0);	
//		TIM_SetCompare4(TIM3, 0);	
//		TIM_SetCompare3(TIM3, 0);		
//	}else if(led_count == 14)
//	{
//		TIM_SetCompare3(TIM4, 0);	
//		TIM_SetCompare4(TIM4, 100);	
//		TIM_SetCompare2(TIM4, 0);	
//		TIM_SetCompare1(TIM4, 0);
//		TIM_SetCompare2(TIM3, 0);	
//		TIM_SetCompare1(TIM3, 0);	
//		TIM_SetCompare4(TIM3, 0);	
//		TIM_SetCompare3(TIM3, 0);		
//	}else if(led_count == 15)
//	{
//		TIM_SetCompare3(TIM4, 100);	
//		TIM_SetCompare4(TIM4, 0);	
//		TIM_SetCompare2(TIM4, 0);	
//		TIM_SetCompare1(TIM4, 0);
//		TIM_SetCompare2(TIM3, 0);	
//		TIM_SetCompare1(TIM3, 0);	
//		TIM_SetCompare4(TIM3, 0);	
//		TIM_SetCompare3(TIM3, 0);		
//	}else if(led_count == 15)
//	{
//		TIM_SetCompare3(TIM4, 100);	
//		TIM_SetCompare4(TIM4, 0);	
//		TIM_SetCompare2(TIM4, 0);	
//		TIM_SetCompare1(TIM4, 0);
//		TIM_SetCompare2(TIM3, 0);	
//		TIM_SetCompare1(TIM3, 0);	
//		TIM_SetCompare4(TIM3, 0);	
//		TIM_SetCompare3(TIM3, 0);		
//	}else if(led_count < 25 && led_count%2==0)
//	{
//		TIM_SetCompare3(TIM4, 100);	
//		TIM_SetCompare4(TIM4, 100);	
//		TIM_SetCompare2(TIM4, 100);	
//		TIM_SetCompare1(TIM4, 100);
//		TIM_SetCompare2(TIM3, 100);	
//		TIM_SetCompare1(TIM3, 100);	
//		TIM_SetCompare4(TIM3, 100);	
//		TIM_SetCompare3(TIM3, 100);		
//	}else if(led_count < 25 && led_count%2!=0)
//	{
//		TIM_SetCompare3(TIM4, 0);	
//		TIM_SetCompare4(TIM4, 0);	
//		TIM_SetCompare2(TIM4, 0);	
//		TIM_SetCompare1(TIM4, 0);
//		TIM_SetCompare2(TIM3, 0);	
//		TIM_SetCompare1(TIM3, 0);	
//		TIM_SetCompare4(TIM3, 0);	
//		TIM_SetCompare3(TIM3, 0);		
//	}
//	if(led_count==25)
//	{
//		TIM_SetCompare3(TIM4,OUTPUTDEVICE.LED[0]*10);	
//		TIM_SetCompare4(TIM4,OUTPUTDEVICE.LED[1]*10);	
//		TIM_SetCompare2(TIM4,OUTPUTDEVICE.LED[2]*10);	
//		TIM_SetCompare1(TIM4,OUTPUTDEVICE.LED[3]*10);
//		TIM_SetCompare2(TIM3,OUTPUTDEVICE.LED[4]*10);	
//		TIM_SetCompare1(TIM3,OUTPUTDEVICE.LED[5]*10);	
//		TIM_SetCompare4(TIM3,OUTPUTDEVICE.LED[6]*10);	
//		TIM_SetCompare3(TIM3,OUTPUTDEVICE.LED[7]*10);	
//	}
//}
void LED_Configuration(void)
{			
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTA时钟	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;           //GPIOA5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //输出功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PA5
	LED_PWM_Init(999,59);
}

void LED_PWM_Init(u32 arr,u32 psc)
{		 					 	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4,ENABLE);  	//TIM3时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC, ENABLE); 	//使能PORTABC时钟	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); 
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM4);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           //GPIOA6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PA6
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;           //GPIOC7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure);              //初始化PC7
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;//GPIOB0 GPIOB1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure);               //初始化GPIOB0 GPIOB1
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_8|GPIO_Pin_9;//GPIOB6789 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure);               //初始化

	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//初始化定时器3	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//初始化定时器4	
	
	//初始化TIM3 Channel1234 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC1	 
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2 
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC3	 
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC4	
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC1	 
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC2 
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC3	 
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC4		

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR3上的预装载寄存器
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR4上的预装载寄存器
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR1上的预装载寄存器
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR2上的预装载寄存器
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR3上的预装载寄存器
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR4上的预装载寄存器
 // TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPE使能 	高级定时器需要
	TIM_CtrlPWMOutputs(TIM3,ENABLE);
	TIM_CtrlPWMOutputs(TIM4,ENABLE);
	TIM_SetCompare1(TIM3,0);	
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,0);
	TIM_SetCompare4(TIM3,0);
	TIM_SetCompare1(TIM4,0);	
	TIM_SetCompare2(TIM4,0);
	TIM_SetCompare3(TIM4,0);
	TIM_SetCompare4(TIM4,0);
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3	
	TIM_Cmd(TIM4, ENABLE);  //使能TIM4		
}  


