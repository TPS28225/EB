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
	GPIO_InitTypeDef GPIO_InitStructure;//定义GPIO_InitTypeDef类型的结构体成员GPIO_InitStructure
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

	RCC_APB1PeriphClockCmd(ZIGBEE_TIMER_CLK, ENABLE); //时钟使能
	TIM_TimeBaseStructure.TIM_Period = 1000-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到1000为10ms
	TIM_TimeBaseStructure.TIM_Prescaler =(6000-1); //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(ZIGBEE_TIMER, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_Cmd(ZIGBEE_TIMER, DISABLE);  	//失能TIMx	
	
	NVIC_InitStructure.NVIC_IRQChannel = ZIGBEE_TIMER_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ClearITPendingBit(ZIGBEE_TIMER, TIM_IT_Update);  //清除TIMx更新中断标志     	
	TIM_ITConfig(ZIGBEE_TIMER,TIM_IT_Update,ENABLE ); //使能指定的TIMx中断,允许更新中断

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
	
	USART_ClearITPendingBit(ZIGBEE_USART, USART_IT_RXNE);					//清除中断TC位	
	USART_ITConfig(ZIGBEE_USART, USART_IT_RXNE, ENABLE);        ///////接收中断使能
	USART_Cmd(ZIGBEE_USART,ENABLE);															//最后使能串口4
}	
void Zigbee_Rx(void)
{
		char res;
		res=USART_ReceiveData(ZIGBEE_USART);	
		USART_SendData(ZIGBEE_USART, res);
		if(RX_Column_Counter<TX_RX_BUFFER_SIZE)		//还可以接收数据
		{
			TIM_SetCounter(ZIGBEE_TIMER,0);		//计数器清空        					//计数器清空
			if(RX_Column_Counter==0) 	 				//使能定时器的中断 
			{
				TIM_SetCounter(ZIGBEE_TIMER,0);	//计数器清空
				TIM_Cmd(ZIGBEE_TIMER, ENABLE);  //使能TIMx	
			}
			if((((OS_Q*)(q_msg_zigbee_rx->OSEventPtr))->OSQEntries)<=ZIGBEE_RX_ARRY_NUM)
				INPUTDEVICE.Zigbee_RX[RX_Row_Counter][RX_Column_Counter++]=res;		//记录接收到的值
		}
/*溢出处理：1一行写满，但下一个缓冲区还空：从下一行开始写
						2所有缓冲区都写满：跳至第一行，不断刷新第一行，但不第一行写满后，不会跳至第二行，而是接着从第一行的头写起。
*/		
		else 																
		{
			RX_Column_Counter=0;
			TIM_Cmd(ZIGBEE_TIMER, DISABLE);  //失能TIMx				
			if((((OS_Q*)(q_msg_zigbee_rx->OSEventPtr))->OSQEntries)<ZIGBEE_RX_ARRY_NUM)
			{
				OSQPost(q_msg_zigbee_rx,(void*)(INPUTDEVICE.Zigbee_RX[RX_Row_Counter]));
				RX_Row_Counter++;								//指向下一行
				if(RX_Row_Counter>=ZIGBEE_RX_ARRY_NUM)RX_Row_Counter = 0;				
			}
		}
}

void Zigbee_Tx(char *buf,u16 len)
{
	u16 t;
  for(t=0;t<len;t++)		  //循环发送数据
	{		   
		while(USART_GetFlagStatus(ZIGBEE_USART,USART_FLAG_TC) == RESET);	  
		USART_SendData(ZIGBEE_USART,buf[t]);
	}	  
	while(USART_GetFlagStatus(ZIGBEE_USART,USART_FLAG_TC) == RESET);	
}
/***********************************************************************
函数名称：void UART4_IRQHandler(void) 
功    能：完成SCI的数据的接收
输入参数：
输出参数：
编写时间：2012.11.22
编 写 人：
注    意：
***********************************************************************/
void UART5_IRQHandler(void)  
{
	if(USART_GetITStatus(ZIGBEE_USART, USART_IT_RXNE) != RESET)//接收到了数据
	{
		Zigbee_Rx();
		USART_ClearITPendingBit(ZIGBEE_USART, USART_IT_RXNE);
	}
}

/***********************************************************************
函数名称:定时器5的中断服务函数和初始化
功    能：
输入参数：
输出参数：
编写时间：
编 写 人：
注    意：
***********************************************************************/  
void TIM5_IRQHandler(void)
{ 	
	if(TIM_GetITStatus(ZIGBEE_TIMER, TIM_IT_Update) != RESET)//是更新中断
	{	 			   
		if((((OS_Q*)(q_msg_zigbee_rx->OSEventPtr))->OSQEntries)<ZIGBEE_RX_ARRY_NUM)
		{
			INPUTDEVICE.Zigbee_RX[RX_Row_Counter][RX_Column_Counter]=0;//添加'\0'
			OSQPost(q_msg_zigbee_rx,(void*)(INPUTDEVICE.Zigbee_RX[RX_Row_Counter]));		
			RX_Row_Counter++;						//指向下一行
			RX_Column_Counter=0;
			if(RX_Row_Counter>=ZIGBEE_RX_ARRY_NUM)RX_Row_Counter=0;
		}
		TIM_Cmd(ZIGBEE_TIMER, DISABLE);  	//失能TIMx			
		TIM_SetCounter(ZIGBEE_TIMER,0);		//计数器清空
		TIM_ClearITPendingBit(ZIGBEE_TIMER, TIM_IT_Update);  //清除TIMx更新中断标志     
	}	    
}



































