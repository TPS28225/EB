#include "main.h"
#include "string.h"

void BLUTOOTH_Run(void)
{
	char *msg;
	u8 err;
	if((((OS_Q*)(q_msg_bluetooth_tx->OSEventPtr))->OSQEntries)!=0)
	{
		msg = OSQPend(q_msg_bluetooth_tx,0,&err);
		Usart4_Send_Data(msg,strlen(msg));
	}
}

void BLUTOOTH_Configuration(void)
{
	Usart4_Init(9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No);
}

void Usart4_Init(u32 bound, u16 wordLength, u16 stopBit, u16 parity)
{  
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
 
	RCC_AHB1PeriphClockCmd(BLUTOOTH_PORT_CLK, ENABLE);//使能GPIOC时钟
	RCC_APB1PeriphClockCmd(BLUTOOTH_USART_CLK,ENABLE);//使能USART4时钟
	
	USART_DeInit(BLUTOOTH_USART);
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4);
	
	GPIO_InitStructure.GPIO_Pin = BLUTOOTH_TX_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    //复用
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(BLUTOOTH_TX_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = BLUTOOTH_RX_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    //复用
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(BLUTOOTH_RX_PORT, &GPIO_InitStructure);
	  
	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = wordLength;//8位数据长度
	USART_InitStructure.USART_StopBits = stopBit;//一个停止位
	USART_InitStructure.USART_Parity = parity;///奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//收发模式
  USART_Init(BLUTOOTH_USART, &USART_InitStructure); ; //初始化串口
   
//  USART_ITConfig(BLUTOOTH_USART, USART_IT_RXNE, ENABLE);//开启中断
//	USART_ClearITPendingBit(BLUTOOTH_USART, USART_IT_TC);
  USART_Cmd(BLUTOOTH_USART, ENABLE);                    //使能串口 
}

void Usart4_Send_Data(char *buf,u16 len)
{
	u16 t;
  for(t=0;t<len;t++)		  //循环发送数据
	{		   
		while(USART_GetFlagStatus(BLUTOOTH_USART,USART_FLAG_TC) == RESET);	  
		USART_SendData(BLUTOOTH_USART,buf[t]);
	}	  
	while(USART_GetFlagStatus(BLUTOOTH_USART,USART_FLAG_TC) == RESET);		 
}


























