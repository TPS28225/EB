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
 
	RCC_AHB1PeriphClockCmd(BLUTOOTH_PORT_CLK, ENABLE);//ʹ��GPIOCʱ��
	RCC_APB1PeriphClockCmd(BLUTOOTH_USART_CLK,ENABLE);//ʹ��USART4ʱ��
	
	USART_DeInit(BLUTOOTH_USART);
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4);
	
	GPIO_InitStructure.GPIO_Pin = BLUTOOTH_TX_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    //����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(BLUTOOTH_TX_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = BLUTOOTH_RX_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    //����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(BLUTOOTH_RX_PORT, &GPIO_InitStructure);
	  
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = wordLength;//8λ���ݳ���
	USART_InitStructure.USART_StopBits = stopBit;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = parity;///��żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ
  USART_Init(BLUTOOTH_USART, &USART_InitStructure); ; //��ʼ������
   
//  USART_ITConfig(BLUTOOTH_USART, USART_IT_RXNE, ENABLE);//�����ж�
//	USART_ClearITPendingBit(BLUTOOTH_USART, USART_IT_TC);
  USART_Cmd(BLUTOOTH_USART, ENABLE);                    //ʹ�ܴ��� 
}

void Usart4_Send_Data(char *buf,u16 len)
{
	u16 t;
  for(t=0;t<len;t++)		  //ѭ����������
	{		   
		while(USART_GetFlagStatus(BLUTOOTH_USART,USART_FLAG_TC) == RESET);	  
		USART_SendData(BLUTOOTH_USART,buf[t]);
	}	  
	while(USART_GetFlagStatus(BLUTOOTH_USART,USART_FLAG_TC) == RESET);		 
}


























