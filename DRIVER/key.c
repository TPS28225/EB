#include "main.h"

char Buletooth_msg[4][10]={{"AT+CK\r\n"},//音量加
													 {"AT+CL\r\n"},//音量减
													 {"AT+MD\r\n"},//下一曲
													 {"AT+ME\r\n"}};//上一曲

void KEY_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;	
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
 	
 	RCC_AHB1PeriphClockCmd(KEY1_CLK, ENABLE);	 	//使能端口时钟
	RCC_AHB1PeriphClockCmd(KEY2_CLK, ENABLE);	
	RCC_AHB1PeriphClockCmd(KEY3_CLK, ENABLE);	
	RCC_AHB1PeriphClockCmd(KEY4_CLK, ENABLE);	
	
	RCC_AHB1PeriphClockCmd(DOOR_CLK, ENABLE);	 	//使能端口时钟
	RCC_AHB1PeriphClockCmd(HUMAN_CLK, ENABLE);	
	RCC_AHB1PeriphClockCmd(SOUND_CLK, ENABLE);
	
	RCC_AHB1PeriphClockCmd(VOICE_ADD_CLK, ENABLE);	
	RCC_AHB1PeriphClockCmd(VOICE_RED_CLK, ENABLE);	
	RCC_AHB1PeriphClockCmd(SONG_NEXT_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(SONG_FORMER_CLK, ENABLE);
	
 	GPIO_InitStructure.GPIO_Pin =  KEY1_PIN;			
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;        //下拉	
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
 	GPIO_Init(KEY1_PORT, &GPIO_InitStructure);				
	
	GPIO_InitStructure.GPIO_Pin =  KEY2_PIN;			
 	GPIO_Init(KEY2_PORT, &GPIO_InitStructure);		
	
	GPIO_InitStructure.GPIO_Pin =  KEY3_PIN;			
 	GPIO_Init(KEY3_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin =  KEY4_PIN;			
 	GPIO_Init(KEY4_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin =  DOOR_PIN;			
 	GPIO_Init(DOOR_PORT, &GPIO_InitStructure);	
	
	
	
	GPIO_InitStructure.GPIO_Pin =  VOICE_ADD_PIN;			
 	GPIO_Init(VOICE_ADD_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin =  VOICE_RED_PIN;			
 	GPIO_Init(VOICE_RED_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin =  SONG_NEXT_PIN;			
 	GPIO_Init(SONG_NEXT_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin =  SONG_FORMER_PIN;			
 	GPIO_Init(SONG_FORMER_PORT, &GPIO_InitStructure);


/***********/						 			
	GPIO_InitStructure.GPIO_Pin = SOUND_PIN;
	GPIO_Init(SOUND_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  HUMAN_PIN;
 	GPIO_Init(HUMAN_PORT, &GPIO_InitStructure);		
	
	RCC_APB2PeriphClockCmd(SOUND_EXIT_CLK, ENABLE);	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource7);
	
			/* 配置 EXTI LineXXX */
	EXTI_InitStructure.EXTI_Line = EXTI_Line7;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line7);  //清除EXTI7线路挂起位
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x06;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

u8 KEY1_Counter=0;
u8 KEY2_Counter=0;
u8 KEY3_Counter=0;
u8 KEY4_Counter=0;
u8 DOOR_Counter=0;
u8 SOUND_Counter=0;
u8 HUMAN_Counter=0;	

u8 VOICE_ADD_Counter=0;
u8 VOICE_RED_Counter=0;
u8 SONG_NEXT_Counter=0;
u8 SONG_FORMER_Counter=0;	

u8 Counter=0;

void KEY_RUN(void)
{	

	if(Counter<10)
	{
		Counter++;		

		if(!KEY1) KEY1_Counter++;
		if(!KEY2) KEY2_Counter++;
		if(!KEY3) KEY3_Counter++;
		if(!KEY4) KEY4_Counter++;
		if(HUMAN) HUMAN_Counter++;
		if(!DOOR) DOOR_Counter++;
		
		if(!VOICE_ADD) VOICE_ADD_Counter++;
		if(!VOICE_RED) VOICE_RED_Counter++;
		if(!SONG_NEXT) SONG_NEXT_Counter++;
		if(!SONG_FORMER) SONG_FORMER_Counter++;		
	}
	else
	{
		Counter = 0;
		if(KEY1_Counter>1)INPUTDEVICE.KEY[0]=SET;//OUTPUTDEVICE.Beep=1;
			else INPUTDEVICE.KEY[0]=RESET;
		if(KEY2_Counter>1)INPUTDEVICE.KEY[1]=SET;//OUTPUTDEVICE.Beep=0;
			else INPUTDEVICE.KEY[1]=RESET;
		if(KEY3_Counter>1)INPUTDEVICE.KEY[2]=SET;
			else INPUTDEVICE.KEY[2]=RESET;
		if(KEY4_Counter>1)INPUTDEVICE.KEY[3]=SET;
			else INPUTDEVICE.KEY[3]=RESET;
		if(HUMAN_Counter>1)INPUTDEVICE.exist_people=SET;
			else INPUTDEVICE.exist_people=RESET;
		if(SOUND_Counter>1)INPUTDEVICE.sound_exceed_threshold=SET;
			else INPUTDEVICE.sound_exceed_threshold=RESET;
		if(DOOR_Counter>1)INPUTDEVICE.Magnetic_Door_Contact=SET;
			else INPUTDEVICE.Magnetic_Door_Contact=RESET;
		
		if(VOICE_ADD_Counter>1)
		{
			OSQPost(q_msg_bluetooth_tx,Buletooth_msg[0]);
		}
		else if(VOICE_RED_Counter>1)
		{
			OSQPost(q_msg_bluetooth_tx,Buletooth_msg[1]);
		}	
		
		if(SONG_NEXT_Counter>1)
		{
			OSQPost(q_msg_bluetooth_tx,Buletooth_msg[2]);
		}
		else if(SONG_FORMER_Counter>1)
		{
			OSQPost(q_msg_bluetooth_tx,Buletooth_msg[3]);
		}

		KEY1_Counter=0;
		KEY2_Counter=0;
		KEY3_Counter=0;
		KEY4_Counter=0;
		DOOR_Counter=0;
		SOUND_Counter=0;
		HUMAN_Counter=0;	

	  VOICE_ADD_Counter=0;
	  VOICE_RED_Counter=0;
	  SONG_NEXT_Counter=0;
	  SONG_FORMER_Counter=0;			
	}
}
















