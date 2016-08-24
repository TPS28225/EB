/******************** (C) 1209 Lab **************************
 * �ļ���  : UltrasonicWave.c
 * ����    �����������ģ�飬UltrasonicWave_Configuration��������
             ��ʼ������ģ�飬UltrasonicWave_StartMeasure��������
			 ������࣬������õ�����ͨ������1��ӡ����         
 * ʵ��ƽ̨��Mini STM32������  STM32F103RBT6
 * Ӳ�����ӣ�------------------
 *          | PC8  - TRIG      |
 *          | PC7  - ECHO      |
 *           ------------------
 * ��汾  ��ST3.5.0
 *
 * ����    ��Lee 
*********************************************************************************/

#include "main.h"
#include "UltrasonicWave.h"

static FlagStatus ECHO_COUNT_START = RESET;
static FlagStatus ECHO_PIN_STATE = RESET;
 
/*
 * ��������UltrasonicWave_Configuration
 * ����  ��������ģ��ĳ�ʼ��
 * ����  ����
 * ���  ����	
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
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(TRIG_PORT, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(ECHO_PORT_CLK, ENABLE); 
	GPIO_InitStructure.GPIO_Pin = ECHO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(ECHO_PORT, &GPIO_InitStructure);	

	RCC_APB2PeriphClockCmd(UltrasonicWave_EXIT_CLK, ENABLE);	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource11);
	
		/* ���� EXTI LineXXX */
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line11);  //���EXTI15_10��·����λ
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x05;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	RCC_APB2PeriphClockCmd(UltrasonicWave_TIMER_CLK, ENABLE); //ʱ��ʹ��
	TIM_TimeBaseStructure.TIM_Period = 60000-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =(1200-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  100Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(UltrasonicWave_TIMER, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	TIM_SetCounter(UltrasonicWave_TIMER,0);
	TIM_Cmd(UltrasonicWave_TIMER, DISABLE);			                                 //��ʱ��2ʧ��

}

void EXTI15_10_IRQHandler(void)
{
	float UltrasonicWave_Distance=0;      //������ľ���  

	if(EXTI_GetITStatus(EXTI_Line11) != RESET)
	{
    ECHO_PIN_STATE=(FlagStatus)GPIO_ReadInputDataBit(ECHO_PORT, ECHO_PIN); 
		
		if((ECHO_PIN_STATE==SET)&&ECHO_COUNT_START == RESET)                
		{
			ECHO_COUNT_START = SET;
			TIM_SetCounter(UltrasonicWave_TIMER,0); 
			TIM_Cmd(UltrasonicWave_TIMER, ENABLE);    //����ʱ��			
		}
		else if((ECHO_PIN_STATE==RESET)&&(ECHO_COUNT_START == SET))                
		{
			ECHO_COUNT_START = RESET;
			TIM_Cmd(UltrasonicWave_TIMER, DISABLE);   
			UltrasonicWave_Distance = TIM_GetCounter(UltrasonicWave_TIMER)*0.17;									 //�������&&UltrasonicWave_Distance<150
		}		
		else if((ECHO_PIN_STATE==SET)&&(ECHO_COUNT_START == SET))
 		{	
			ECHO_COUNT_START = RESET;						
			TIM_Cmd(UltrasonicWave_TIMER, DISABLE);			                                 //��ʱ��2ʧ��
			TIM_SetCounter(UltrasonicWave_TIMER,0);
		}
		else if((ECHO_PIN_STATE==RESET)&&(ECHO_COUNT_START == RESET))
 		{	
			ECHO_COUNT_START = RESET;
			TIM_Cmd(UltrasonicWave_TIMER, DISABLE);			                                 //��ʱ��2ʧ��
			TIM_SetCounter(UltrasonicWave_TIMER,0);
		}

		if(UltrasonicWave_Distance>0)
		{
			INPUTDEVICE.Distance=UltrasonicWave_Distance;
		}
			
		EXTI_ClearITPendingBit(EXTI_Line11);  //���EXTI11��·����λ
	}

}

/*
 * ��������UltrasonicWave_StartMeasure
 * ����  ����ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
 * ����  ����
 * ���  ����	
 */
void UltrasonicWave_StartMeasure(void)
{	
	if(ECHO_COUNT_START == RESET)
	{
		INPUTDEVICE.Distance=0;
		GPIO_SetBits(TRIG_PORT,TRIG_PIN);//��>10US�ĸߵ�ƽ�UltrasonicWave_PORT,TRIG_PIN��������define����?
		delay_us(20);		                      //��ʱ20US
		GPIO_ResetBits(TRIG_PORT,TRIG_PIN);
	}
}

//void UltrasonicWave_MeasureDistance(void)
//{
//  GPIO_SetBits(UltrasonicWave_PORT,TRIG_PIN); 		  //��>10US�ĸߵ�ƽ�UltrasonicWave_PORT,TRIG_PIN��������define����?
//  delay_us(20);		                      //��ʱ20US
//  GPIO_ResetBits(UltrasonicWave_PORT,TRIG_PIN);
//	
//	while(GPIO_ReadInputDataBit(UltrasonicWave_PORT,ECHO_PIN)==RESET);	                 //�ȴ��͵�ƽ	
//	
//	TIM_SetCounter(UltrasonicWave_TIMER,0);
//	TIM_Cmd(UltrasonicWave_TIMER, ENABLE);                                             //����ʱ��

//	while(GPIO_ReadInputDataBit(UltrasonicWave_PORT,ECHO_PIN)==SET);	                 //�ȴ��͵�ƽ

//	TIM_Cmd(UltrasonicWave_TIMER, DISABLE);			                                 //��ʱ��2ʧ��
//	UltrasonicWave_Distance=TIM_GetCounter(UltrasonicWave_TIMER)*5*34/200.0;									 //�������&&UltrasonicWave_Distance<150
//		
//	if(UltrasonicWave_Distance>0)
//	{
////		printf("distance:%f cm",UltrasonicWave_Distance);	
//		
//	}		
//}

/******************* (C) 1209 Lab *****END OF FILE************/
