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
FlagStatus ECHO_COUNT_START = RESET;
FlagStatus ECHO_PIN_STATE = RESET; 
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
	TIM_Cmd(UltrasonicWave_TIMER, DISABLE);			                                 //��ʱ��ʧ��
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
		delay_us(30);	
	}
}
extern u16 RFTimeBuff[200];
void EXTI15_10_IRQHandler(void)
{
	OS_CPU_SR cpu_sr;
	float UltrasonicWave_Distance=0;      //������ľ���  
	OS_ENTER_CRITICAL();    // ���ж�                               
	OSIntNesting++;	   		//�ж�Ƕ�ײ�����֪ͨucos
	OS_EXIT_CRITICAL();	   	//���ж�
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
			if(UltrasonicWave_Distance>2000)INPUTDEVICE.Distance=2000;
			else INPUTDEVICE.Distance = UltrasonicWave_Distance;

		}
			
		EXTI_ClearITPendingBit(EXTI_Line11);  //���EXTI11��·����λ
	}
	
	if(EXTI_GetITStatus(RF_RX_EXIT_LINE) != RESET)
	{
		EXTI_ClearITPendingBit(RF_RX_EXIT_LINE);  //���LINE10�ϵ��жϱ�־λ 
		TIM14_Set(0);              //�رն�ʱ��
		if(Rf.ZaboFlag==1)       //ʹ���˲�
		{
			if(Rf.Count >= RF_CONT)     //�ж������ϱ��Ƿ���ɣ���ɼ�����δ����˳��ȴ����
				return;
					
			Rf.TimeVal=TIM14->CNT;
			if((Rf.TimeVal>3000)&&(Rf.TimeVal<14000))  //�ж��Ƿ�Ϊͬ��ͷ
			{
				if(Rf.HeadFlag==0)
					Rf.HeadFlag=1;                  //���յ�1��ͬ��ͷ
				else if(Rf.HeadFlag==1)
				{
					Rf.HeadFlag=0;               //���յ�2��ͬ��ͷ
					Rf.ZaboFlag=0;							//�˲�����
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
				//�������ݹ���������յ��ߵ͵�ƽʱ�䳬����Χ����Ϊ������Ч
				if(RFTimeBuff[Rf.Count]<150 || RFTimeBuff[Rf.Count]>15000)				
				{
					Rf.ZaboFlag=1;
					Rf.Count=0;
					TIM14_Set(1);
					return;
				}
				Rf.Count++;
				if(Rf.Count >= RF_CONT)   //�������ݳ���150����������ɣ�ʹ���ϱ�
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
	OSIntExit();//�ж��˳���֪ͨucos�����þ����ӣ�	
}

/******************* (C) 1209 Lab *****END OF FILE************/
