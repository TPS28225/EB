#include "main.h"
#include "Zigbee.h"
#include <string.h>
u16 RX_Row_Counter=0;
u16 RX_Column_Counter=0;


void Zigbee_RUN(void)
{
	char *msg;
	u8 err;
	if((((OS_Q*)(q_msg_zigbee_tx->OSEventPtr))->OSQEntries)!=0)
	{
		msg = OSQPend(q_msg_zigbee_tx,0,&err);
		Zigbee_Tx(msg,strlen(msg));
	}
}


void Zigbee_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//����GPIO_InitTypeDef���͵Ľṹ���ԱGPIO_InitStructure
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStruct;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(ZIGBEE_TX_PORT_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(ZIGBEE_RX_PORT_CLK, ENABLE);
	RCC_APB1PeriphClockCmd(ZIGBEE_USART_CLK, ENABLE);

	USART_DeInit(ZIGBEE_USART);
	
	USART_StructInit(&USART_InitStructure);
	USART_ClockStructInit(&USART_ClockInitStruct);      
   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = ZIGBEE_TX_PIN; 
	GPIO_Init(ZIGBEE_TX_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(ZIGBEE_TX_PORT,GPIO_PinSource12,GPIO_AF_UART5); //tx    
	
	GPIO_InitStructure.GPIO_Pin = ZIGBEE_RX_PIN;        				
	GPIO_Init(ZIGBEE_RX_PORT, &GPIO_InitStructure);                                                                                                                 
	GPIO_PinAFConfig(ZIGBEE_RX_PORT,GPIO_PinSource2,GPIO_AF_UART5);	//rx

	RCC_APB1PeriphClockCmd(ZIGBEE_TIMER_CLK, ENABLE); //ʱ��ʹ��
	TIM_TimeBaseStructure.TIM_Period = 1000-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������1000Ϊ10ms
	TIM_TimeBaseStructure.TIM_Prescaler =(6000-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(ZIGBEE_TIMER, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	TIM_Cmd(ZIGBEE_TIMER, DISABLE);  	//ʧ��TIMx	
	
	NVIC_InitStructure.NVIC_IRQChannel = ZIGBEE_TIMER_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ClearITPendingBit(ZIGBEE_TIMER, TIM_IT_Update);  //���TIMx�����жϱ�־     	
	TIM_ITConfig(ZIGBEE_TIMER,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIMx�ж�,��������ж�

	USART_ClockInit(ZIGBEE_USART,&USART_ClockInitStruct);
	USART_InitStructure.USART_BaudRate = 57600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(ZIGBEE_USART,&USART_InitStructure); 
	
	NVIC_InitStructure.NVIC_IRQChannel = ZIGBEE_USART_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0D;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ClearITPendingBit(ZIGBEE_USART, USART_IT_RXNE);					//����ж�TCλ	
	USART_ITConfig(ZIGBEE_USART, USART_IT_RXNE, ENABLE);        ///////�����ж�ʹ��
	USART_Cmd(ZIGBEE_USART,ENABLE);															//���ʹ�ܴ���4
}	
void Zigbee_Rx(void)
{
		char res;
		res=USART_ReceiveData(ZIGBEE_USART);	
		USART_SendData(ZIGBEE_USART, res);
		if(RX_Column_Counter<TX_RX_BUFFER_SIZE)		//�����Խ�������
		{
			TIM_SetCounter(ZIGBEE_TIMER,0);		//���������        					//���������
			if(RX_Column_Counter==0) 	 				//ʹ�ܶ�ʱ�����ж� 
			{
				TIM_SetCounter(ZIGBEE_TIMER,0);	//���������
				TIM_Cmd(ZIGBEE_TIMER, ENABLE);  //ʹ��TIMx	
			}
			if((((OS_Q*)(q_msg_zigbee_rx->OSEventPtr))->OSQEntries)<=ZIGBEE_RX_ARRY_NUM)
				INPUTDEVICE.Zigbee_RX[RX_Row_Counter][RX_Column_Counter++]=res;		//��¼���յ���ֵ
		}
/*�������1һ��д��������һ�����������գ�����һ�п�ʼд
						2���л�������д����������һ�У�����ˢ�µ�һ�У�������һ��д���󣬲��������ڶ��У����ǽ��Ŵӵ�һ�е�ͷд��
*/		
		else 																
		{
			RX_Column_Counter=0;
			TIM_Cmd(ZIGBEE_TIMER, DISABLE);  //ʧ��TIMx				
			if((((OS_Q*)(q_msg_zigbee_rx->OSEventPtr))->OSQEntries)<ZIGBEE_RX_ARRY_NUM)
			{
				OSQPost(q_msg_zigbee_rx,(void*)(INPUTDEVICE.Zigbee_RX[RX_Row_Counter]));
				RX_Row_Counter++;								//ָ����һ��
				if(RX_Row_Counter>=ZIGBEE_RX_ARRY_NUM)RX_Row_Counter = 0;				
			}
		}
}

void Zigbee_Tx(char *buf,u16 len)
{
	u16 t;
  for(t=0;t<len;t++)		  //ѭ����������
	{		   
		while(USART_GetFlagStatus(ZIGBEE_USART,USART_FLAG_TC) == RESET);	  
		USART_SendData(ZIGBEE_USART,buf[t]);
	}	  
	while(USART_GetFlagStatus(ZIGBEE_USART,USART_FLAG_TC) == RESET);	
}
/***********************************************************************
�������ƣ�void UART4_IRQHandler(void) 
��    �ܣ����SCI�����ݵĽ���
���������
���������
��дʱ�䣺2012.11.22
�� д �ˣ�
ע    �⣺
***********************************************************************/
void UART5_IRQHandler(void)  
{
	if(USART_GetITStatus(ZIGBEE_USART, USART_IT_RXNE) != RESET)//���յ�������
	{
		Zigbee_Rx();
		USART_ClearITPendingBit(ZIGBEE_USART, USART_IT_RXNE);
	}
}

/***********************************************************************
��������:��ʱ��5���жϷ������ͳ�ʼ��
��    �ܣ�
���������
���������
��дʱ�䣺
�� д �ˣ�
ע    �⣺
***********************************************************************/  
void TIM5_IRQHandler(void)
{ 	
	if(TIM_GetITStatus(ZIGBEE_TIMER, TIM_IT_Update) != RESET)//�Ǹ����ж�
	{	 			   
		if((((OS_Q*)(q_msg_zigbee_rx->OSEventPtr))->OSQEntries)<ZIGBEE_RX_ARRY_NUM)
		{
			INPUTDEVICE.Zigbee_RX[RX_Row_Counter][RX_Column_Counter]=0;//���'\0'
			OSQPost(q_msg_zigbee_rx,(void*)(INPUTDEVICE.Zigbee_RX[RX_Row_Counter]));		
			RX_Row_Counter++;						//ָ����һ��
			RX_Column_Counter=0;
			if(RX_Row_Counter>=ZIGBEE_RX_ARRY_NUM)RX_Row_Counter=0;
		}
		TIM_Cmd(ZIGBEE_TIMER, DISABLE);  	//ʧ��TIMx			
		TIM_SetCounter(ZIGBEE_TIMER,0);		//���������
		TIM_ClearITPendingBit(ZIGBEE_TIMER, TIM_IT_Update);  //���TIMx�����жϱ�־     
	}	    
}



































