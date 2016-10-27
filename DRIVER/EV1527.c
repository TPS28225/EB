#include "main.h"
/***********************************************************************
�������ƣ�H34B  H3V4F
������������Ƶ�շ�   ����EV1527����
�õ����裺�ⲿ�ж�2       IO:PC2 �ж����ȼ� 0-2
					��ʱ��5                �ж����ȼ� 0-3
					��ʱ��3PWM���  IO:PA7 �ж����ȼ� 2-1
ʱ    ��: 2015/12/15
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
��������: RF_H3V4F_Rev ����
��    ��: ������Ƶ���Σ���������н���
���������*buff �������ݵ����飬û�ν���3�����ݣ�ÿ������3���ֽ�
�����������
��дʱ�䣺
�� д �ˣ�
ע    �⣺
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
			 
				*data=(decOut[0]<<16)+(decOut[1]<<8)+decOut[2];//���ܳ���
				Rf.State = 0;
			  Rf.Count = 0;
				return 1;
		 }
		 else if((buff[3] == buff[6]) && (buff[4] == buff[7]) && (buff[5] == buff[8]))
		 {
				decOut[0] = buff[3];
				decOut[1] = buff[4];
				decOut[2] = buff[5];
			 		 
				*data=(decOut[0]<<16)+(decOut[1]<<8)+decOut[2];//���ܳ���
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
��������: RF_H34B_Send   
��    �ܣ�H34B�ķ��亯������Ҫ��ʹ�ܶ�����PWM������Σ�
					���岨���������жϷ�����
���������RF_ENCODE_DATA   Ҫ���͵�24λ��   ��8λ������
�����������
��дʱ�䣺
�� д �ˣ�
ע    �⣺
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
��������: ��Ƶ��ʼ��
��    �ܣ��ⲿ�ж�2�����ó�ʼ��  IO: PC2
�����������
�����������
��дʱ�䣺
�� д �ˣ�
ע    �⣺�ж����ȼ�  0-2
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
  EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}
/***********************************************************************
��������: �ⲿ�ж�10�������
������������Ҫ�ǽ�����Ƶ���Σ���¼ʱ��Ƭ��Ϣ
�����������
�����������
��дʱ�䣺
�� д �ˣ�
ע    �⣺1.�����ж��ȹرն�ʱ�������жϿ�����ʱ��		
					2.���˲������ж��յ�����ͬ��ͷʱ����ʼ��¼����
***********************************************************************/  
//��UltrasonicWave.c��

/***********************************************************************
��������:��ʱ��14���жϷ������ͳ�ʼ��
��    �ܣ�һ����ʱ��5�����жϣ����ͬ��ͷ�����ݣ���ͷ��ʼ����
���������
���������
��дʱ�䣺
�� д �ˣ�
ע    �⣺��ʱ��14��������Ҫ��Ϊ���ղ��η��񣬳�ʼ��ʱ50ms�����ж�
					һ�������жϣ����ղ��δ��¿�ʼ
					�ж����ȼ�  0-3
***********************************************************************/  
void TIM8_TRG_COM_TIM14_IRQHandler(void)
{ 	
	if(TIM_GetITStatus(RF_RX_TIMER, TIM_IT_Update) != RESET)//�Ǹ����ж�
	{	
		TIM_ClearITPendingBit(RF_RX_TIMER, TIM_IT_Update);  //���TIMx�����жϱ�־    
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
		TIM_SetCounter(RF_RX_TIMER,0);//���������
		TIM_Cmd(RF_RX_TIMER, ENABLE);  //ʹ��TIMx	
	}else TIM_Cmd(RF_RX_TIMER, DISABLE);//�رն�ʱ��5 
}
void TIM14_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RF_RX_TIMER_CLK, ENABLE); //ʱ��ʹ��//TIM5ʱ��ʹ��    
	
	TIM_TimeBaseInitStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseInitStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ

	TIM_TimeBaseInit(RF_RX_TIMER, &TIM_TimeBaseInitStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ	
	TIM_ITConfig(RF_RX_TIMER,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM5�ж�,��������ж�						 

	NVIC_InitStructure.NVIC_IRQChannel = TIM8_TRG_COM_TIM14_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}

/***********************************************************************
��������: ��ʱ��13��ʼ��
��    �ܣ���ʱ��13��Ҫ��Ϊ���Ͳ������ã����ɲ�ͬռ�ձȵķ���
���������
���������
��дʱ�䣺
�� д �ˣ�
ע    �⣺�ж����ȼ� 2-1    IO:PA7
***********************************************************************/ 
void TIM13_Init(u16 arr,u16 psc)
{		 			
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RF_TX_TIMER_CLK, ENABLE); //ʱ��ʹ��//TIM13ʱ��ʹ��    
	
	TIM_TimeBaseInitStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseInitStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	
	TIM_TimeBaseInit(RF_TX_TIMER, &TIM_TimeBaseInitStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ 
	TIM_ITConfig(RF_TX_TIMER,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM13�ж�,��������ж�	                   
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}  
/***********************************************************************
��������:��ʱ��13�жϷ�����
��    �ܣ�����Ҫ�������ݵ�ÿһλ�ߵͷ�����ʱ
���������
���������
��дʱ�䣺
�� д �ˣ�
ע    �⣺//��4Tѹ��Ϊ1T
***********************************************************************/ 
void TIM8_UP_TIM13_IRQHandler(void)
{ 	
	if(TIM_GetITStatus(RF_TX_TIMER, TIM_IT_Update) != RESET)//�Ǹ����ж�
	{	
		Rf.SendTime++;
		if(Rf.SendEnable==1) 
		{
			//Rf.SendFlag������״̬��0����ͬ���ֽڣ�1��������1��2��������0
			if(Rf.SendFlag==0)  //����ͬ���ֽ�
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
			}else if(Rf.SendFlag==1) //���͡�1��
			{
				if(Rf.SendTime<=3)							//һ��Ҫ�����Ĵ�
				{
					GPIO_SetBits(RF_TX_PORT,RF_TX_PIN);				
				}
				else
				{
					GPIO_ResetBits(RF_TX_PORT,RF_TX_PIN);				
					Rf.SendTime=0;
					if(Rf.Movecnt<24)						 //�ж�24λ�Ƿ������
					{
						if(Rf.SendData&(1<<(23-Rf.Movecnt)))//�ж���һ�η���0����1
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
			}else if(Rf.SendFlag==2) //���͡�0��
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
		TIM_ClearITPendingBit(RF_TX_TIMER, TIM_IT_Update);  //���TIMx�����жϱ�־     
	}	    
}
void TIM13_Set(u8 sta)
{
	if(sta)
	{       
		TIM_SetCounter(RF_TX_TIMER,0);//���������
		TIM_Cmd(RF_TX_TIMER, ENABLE);  //ʹ��TIMx	
	}else TIM_Cmd(RF_TX_TIMER, DISABLE);//�رն�ʱ��13
}

void EXTI10_Int(u8 en)
{
    EXTI->PR=1<<10;  
    if(en)EXTI->IMR|=1<<10;
    else EXTI->IMR&=~(1<<10);
}
/***********************************************************************
��������:ϵͳ��ʼ������
��    �ܣ�
���������
���������
��дʱ�䣺
�� д �ˣ�
ע    �⣺
***********************************************************************/ 
void RF_H3V4_H34B_Init(void)
{
	RF_EXTI_Init();
	TIM14_Init(60000,59);
	TIM14_Set(1);
	TIM13_Init(300,59);//300us����
	TIM13_Set(0);
 	Rf.ZaboFlag=1;   //�˳��Ӳ�
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




















