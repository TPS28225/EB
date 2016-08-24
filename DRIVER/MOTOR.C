#include "main.h"


void MOTOR_Run(void)
{
	static char Motor_Speed_Current=0;
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
	MOTOR_PWM_Init(999,119);
}

void MOTOR_PWM_Init(u32 arr,u32 psc)
{		 					 	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	//TIM1ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ��	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_TIM1);
	
	GPIO_InitStructure.GPIO_Pin =  MOTOR_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(MOTOR_GPIO, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12;           //GPIOA8 11 12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PA8 11 12
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_12);
	
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//��ʼ����ʱ��1
	
	//��ʼ��TIM1Channel1 4 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM������ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 OC1	 
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 OC4	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR4�ϵ�Ԥװ�ؼĴ���
  TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPEʹ�� 	�߼���ʱ����Ҫ
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	TIM_SetCompare1(TIM1,0);	
	TIM_SetCompare4(TIM1,0);
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1

}  