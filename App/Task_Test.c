/***********************************************************************
�ļ����ƣ�
��    �ܣ�
��дʱ�䣺
�� д �ˣ�
ע    �⣺
***********************************************************************/
#include "main.h"  
#include "bmpdisplay.h"
#include "xbffontcreate.h"
#include "exammanager.h"
__align(8) OS_STK Stk_Task_RX[TASK_TEST_RX_STK_SIZE];
__align(8) OS_STK Stk_Task_TX[TASK_TEST_TX_STK_SIZE];
__align(8) OS_STK Stk_Task_OUTPUT[TASK_TEST_OUTPUT_STK_SIZE];
__align(8) OS_STK Stk_Task_INPUT[TASK_TEST_INPUT_STK_SIZE];
__align(8) OS_STK Stk_Task_KEY[TASK_TEST_KEY_STK_SIZE];
__align(8) OS_STK Stk_Task_UDP_Client[TASK_UDP_CLIENT_STK_SIZE];
__align(8) OS_STK Stk_Task_TCP_Client[TASK_TCP_CLIENT_STK_SIZE];
__align(8) OS_STK Stk_Task_STATE_TEST[TASK_STATE_TEST_STK_SIZE];

//��ʾ��
__align(8) OS_STK Stk_Task_OLED_DISPLAY[TASK_OLED_DISPLAY_STK_SIZE];
//����
__align(8) OS_STK Stk_Task_BEEP_MUSIC[TASK_BEEP_MUSIC_STK_SIZE];
tx_buf_t  tx_buf;
rx_buf_t  rx_buf;

char uniqueID[33]={0};

INPUTDEVICE_MEASURE INPUTDEVICE;
OUTPUTDEVICE_CONTROL OUTPUTDEVICE;

OS_EVENT * q_msg_zigbee_rx;		
OS_EVENT * q_msg_zigbee_tx;	
OS_EVENT * q_msg_bluetooth_tx;

void * MsgGrp_q_msg_zigbee_rx[ZIGBEE_RX_ARRY_NUM];
void * MsgGrp_q_msg_zigbee_tx[ZIGBEE_TX_ARRY_NUM];
void * MsgGrpq_msg_bluetooth_tx[BLUETOOTH_TX_ARRY_NUM];

typedef struct
{
	u32 UdpStartTime;
	u32 UdpEndTime;
	u32 UdpRunTime;
	u32 RxStartTime;
	u32 RxEndTime;
	u32 RxRunTime;
	u32 TxStartTime;
	u32 TxEndTime;
	u32 TxRunTime;
	u32 InputStartTime;
	u32 InputEndTime;
	u32 InputRunTime;
	u32 OutputStartTime;
	u32 OutputEndTime;
	u32 OutputRunTime;
	
}taskRunTime;
taskRunTime runTime;
/***********************************************************************
�������ƣ�void Task_LED(void *pdata)
��    �ܣ�
���������
���������
��дʱ�䣺
�� д �ˣ�
ע    �⣺
***********************************************************************/
void Task_INPUT(void *pdata)
{			
  while(1)
	{
		UltrasonicWave_StartMeasure();
		DHT11_Read_Data();
		LightIntensitySensor_measure();
//		GET_CARDID();	 
		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}
void Task_KEY(void *pdata)
{				
  while(1)
	{
		KEY_RUN();
		OSTimeDlyHMSM(0, 0, 0, 30);
	}
}
extern int IR_LearnState;
void Task_OUTPUT(void *pdata)
{	
//	IR_LearnState=0;		
  while(1)
	{
//		runTime.OutputStartTime = TIM_GetCounter(DELAY_TIMER);
		LED_Run();	
		MOTOR_Run();
		BLUTOOTH_Run();
//		Zigbee_RUN();
//		IR_Run();
				
//		runTime.OutputEndTime = TIM_GetCounter(DELAY_TIMER);
//		if(runTime.OutputEndTime - runTime.OutputStartTime > runTime.OutputRunTime)
//			runTime.OutputRunTime = runTime.OutputEndTime - runTime.OutputStartTime;	
//		OSTimeDlyHMSM(0, 0, 1, 0);


//	OUTPUTDEVICE.RFID_CARD.rfid_card_Info.Card_State=1;
	OSTimeDlyHMSM(0, 0, 2, 0);//��ʱ2s
	}
}
/***********************************************************************
�������ƣ�void Task_TX(void *pdata)
��    �ܣ�
���������
���������
��дʱ�䣺
�� д �ˣ�
ע    �⣺
***********************************************************************/

void Task_TX(void *pdata)
{		
  while(1)
	{
		char *msg;
		runTime.TxStartTime = TIM_GetCounter(DELAY_TIMER);
		msg = makeJson();
		strlen(msg);
		msgReporter(msg,strlen(msg));
		free(msg);
		runTime.TxEndTime = TIM_GetCounter(DELAY_TIMER);
		if(runTime.TxEndTime - runTime.TxStartTime > runTime.TxRunTime)
			runTime.TxRunTime = runTime.TxEndTime - runTime.TxStartTime;	
		OSTimeDlyHMSM(0, 0, 5, 0);
	}
}
/***********************************************************************
�������ƣ�void Task_RX(void *pdata)
��    �ܣ�
���������
���������
��дʱ�䣺
�� д �ˣ�
ע    �⣺
***********************************************************************/

void Task_RX(void *pdata)
{	
  while(1)
	{
		runTime.RxStartTime = TIM_GetCounter(DELAY_TIMER);
    msgParser();
		runTime.RxEndTime = TIM_GetCounter(DELAY_TIMER);
		if(runTime.RxEndTime - runTime.RxStartTime > runTime.RxRunTime)
			runTime.RxRunTime = runTime.RxEndTime - runTime.RxStartTime;	
		OSTimeDlyHMSM(0, 0, 0, 200);
	}
}

/***********************************************************************
***********************************************************************
�������ƣ�void Task_UDP_Client(void *pdata)
��    �ܣ�
���������
���������
��дʱ�䣺
�� д �ˣ�
ע    �⣺
***********************************************************************/
void Task_UDP_Client(void *pdata)
{
	__IO uint32_t LocalTime = 0; /* this variable is used to create a time reference incremented by 10ms */
	/* configure ethernet (GPIOs, clocks, MAC, DMA) */ 
	ETH_BSP_Config();
	LwIP_Init();

	/* UDP_client Init */
	UDP_client_init();
	while(1)
	{ 	
		runTime.UdpStartTime = TIM_GetCounter(DELAY_TIMER);
		while(tx_buf.numOfBuf > 0)
		{
			udp_p->payload = tx_buf.buffer[--tx_buf.numOfBuf];
			udp_p->len=udp_p->tot_len=strlen(tx_buf.buffer[tx_buf.numOfBuf]);
		  udp_send(udp_pcb,udp_p);
		}
		LocalTime +=10;
		LwIP_Periodic_Handle(LocalTime);		
		runTime.UdpEndTime = TIM_GetCounter(DELAY_TIMER);
		if(runTime.UdpEndTime - runTime.UdpStartTime > runTime.UdpRunTime)
			runTime.UdpRunTime = runTime.UdpEndTime - runTime.UdpStartTime;
		OSTimeDlyHMSM(0, 0, 0, 10);//����10ms���Ա������߳�����
	}
}

void Task_TCP_Client(void *pdata)
{	
	__IO uint32_t LocalTime = 0; 
//	unsigned char *tcp_data;
	struct tcp_pcb *pcb;	
	ETH_BSP_Config();
	LwIP_Init();

	/* TCP_Client Init */
	TCP_Client_Init(TCP_LOCAL_PORT,TCP_SERVER_PORT,TCP_SERVER_IP);
	while(1)
	{  
		pcb = Check_TCP_Connect();
		if(pcb != 0)
		{	
			while(tx_buf.numOfBuf > 0)
			{     
				TCP_Client_Send_Data(pcb,(unsigned char*)tx_buf.buffer[tx_buf.numOfBuf-1],strlen(tx_buf.buffer[tx_buf.numOfBuf-1]));
				//TCP_Client_Send_Data(pcb,(unsigned char*)tx_buf.buffer[tx_buf.numOfBuf-1],14);
				tx_buf.numOfBuf--;				
			}			
		}		
		LocalTime +=10;
		LwIP_Periodic_Handle(LocalTime);		
		OSTimeDlyHMSM(0, 0, 0, 10);//����10ms���Ա������߳�����
	}
}
void Task_OLEDDisplay(void *pdata)
{
	u8 result;
	FATFS fs;
	static FIL BMPFile;
	f_mount(0, &fs);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC,ENABLE);//Ҫ����STenwim�������ȿ�CRCʱ��
  GUI_Init();
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(GUI_WHITE);
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_UC_SetEncodeUTF8();
	GUI_UC_SetEncodeUTF8();
	GUI_Clear();
	GUI_SetFont(&GUI_Font16_1);
	GUI_DispStringAt("CPU         STM32F207",10,10);
	GUI_DispStringAt("LCD           480x320",10,30);
	GUI_DispStringAt("EXRAM             OK!",10,50);	
	GUI_DispStringAt("GUI                   OK!",10,70);
	GUI_DispStringAt("PLEASE WAITING...   ",10,90);	
//	MainTask();
	
	OUTPUTDEVICE.Cureent_Exam_Num=61;
	while(1){
			//���SD������ֹ������ʵ����������				
		GUI_SetTextMode(GUI_TM_NORMAL);
		GUI_SetFont(&GUI_Font16_1);
		GUI_Clear();
		GUI_DispStringAt("CPU         STM32F207",10,10);
		GUI_DispStringAt("LCD           480x320",10,30);
		GUI_DispStringAt("EXRAM             OK!",10,50);	
		GUI_DispStringAt("GUI                   OK!",10,70);
		GUI_DispStringAt("PLEASE WAITING...   ",10,90);	
		while(1){
			result = f_open(&BMPFile,"0:/picture/face.bmp",FA_READ);	//���ļ�
			//�ļ��򿪴���
			if(result != FR_OK) 	
			{				
				GUI_DispStringAt("SDCARD fault.             ",10,90);
			}
			else 	{
				GUI_DispStringAt("SDCARD SUCCESS.     ",10,90);	
				f_close(&BMPFile);	
				break;
			}
		}		
		GUI_SetTextMode(GUI_TM_TRANS);
		
		switch(OUTPUTDEVICE.Cureent_Exam_Num){	
			case 1:bmpdisplay_exam1();break;
			
			case 2:bmpdisplay_exam2();break;
			
			case 3:bmpdisplay_exam3();break;
			
			case 4:bmpdisplay_exam4();break;
			
			case 5:bmpdisplay_exam5();break;
			
			case 61:bmpdisplay_exam6_bus();break;
			
			case 62:bmpdisplay_exam6_entrance_guard();break;
			
			case 7:bmpdisplay_exam7();break;
			
			case 8:bmpdisplay_exam8();break;

			case 9:bmpdisplay_exam9();break;			
		}
		OSTimeDlyHMSM(0, 0, 0, 200);//����200ms���Ա������߳�����
	}	
}


void Task_BEEP_MUSIC_Display(void *pdata)
{
	while(1){
		BEEP_Run();
		OSTimeDlyHMSM(0, 0, 0, 200);//����100ms���Ա������߳�����
	}
}
	u32 Stak_OLED_Free=0xffffffff;
void Task_STATE_TEST(void *pdata){
	OS_STK_DATA Stak_OLED;

	while(1){		
		GPIO_SetBits(GPIOA,GPIO_Pin_5);		
		OSTimeDlyHMSM(0, 0, 0, 100);//����100ms���Ա������߳�����
		OSTaskStkChk(OS_USER_PRIO_GET(3), &Stak_OLED);
		if(Stak_OLED.OSFree<Stak_OLED_Free)
			Stak_OLED_Free=Stak_OLED.OSFree;
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);				
		OSTimeDlyHMSM(0, 0, 2, 0);//����100ms���Ա������߳�����
	}	
}








