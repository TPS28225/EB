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
	LED_PWM_Init(999,59);
}

void LED_PWM_Init(u32 arr,u32 psc)
{		 					 	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4,ENABLE);  	//TIM3ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC, ENABLE); 	//ʹ��PORTABCʱ��	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); 
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM4);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           //GPIOA6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PA6
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;           //GPIOC7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOC,&GPIO_InitStructure);              //��ʼ��PC7
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;//GPIOB0 GPIOB1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOB,&GPIO_InitStructure);               //��ʼ��GPIOB0 GPIOB1
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_8|GPIO_Pin_9;//GPIOB6789 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOB,&GPIO_InitStructure);               //��ʼ��

	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//��ʼ����ʱ��3	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//��ʼ����ʱ��4	
	
	//��ʼ��TIM3 Channel1234 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM������ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC1	 
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2 
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC3	 
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC4	
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 OC1	 
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 OC2 
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 OC3	 
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 OC4		

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR3�ϵ�Ԥװ�ؼĴ���
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR4�ϵ�Ԥװ�ؼĴ���
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR3�ϵ�Ԥװ�ؼĴ���
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR4�ϵ�Ԥװ�ؼĴ���
 // TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPEʹ�� 	�߼���ʱ����Ҫ
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
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3	
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM4		
}  

