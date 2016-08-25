/***********************************************************************
文件名称：
功    能：
编写时间：
编 写 人：
注    意：
***********************************************************************/
#include "main.h"  
#include "bmpdisplay.h"
#include "xbffontcreate.h"
__align(8) OS_STK Stk_Task_RX[TASK_TEST_RX_STK_SIZE];
__align(8) OS_STK Stk_Task_TX[TASK_TEST_TX_STK_SIZE];
__align(8) OS_STK Stk_Task_OUTPUT[TASK_TEST_OUTPUT_STK_SIZE];
__align(8) OS_STK Stk_Task_INPUT[TASK_TEST_INPUT_STK_SIZE];
__align(8) OS_STK Stk_Task_KEY[TASK_TEST_KEY_STK_SIZE];
__align(8) OS_STK Stk_Task_UDP_Client[TASK_UDP_CLIENT_STK_SIZE];
__align(8) OS_STK Stk_Task_TCP_Client[TASK_TCP_CLIENT_STK_SIZE];

//显示屏
__align(8) OS_STK Stk_Task_OLED_DISPLAY[TASK_OLED_DISPLAY_STK_SIZE];
//声音
__align(8) OS_STK Stk_Task_BEEP_MUSIC[TASK_BEEP_MUSIC_STK_SIZE];
tx_buf_t  tx_buf;
rx_buf_t  rx_buf;

char uniqueID[32];

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
函数名称：void Task_LED(void *pdata)
功    能：
输入参数：
输出参数：
编写时间：
编 写 人：
注    意：
***********************************************************************/
void Task_INPUT(void *pdata)
{		
//	char str[10];
//	LcmClearBMP();	
  while(1)
	{
//		UltrasonicWave_StartMeasure();
//		DHT11_Read_Data();
//		LightIntensitySensor_measure();
//		GET_CARDID();	 
		OSTimeDlyHMSM(0, 0, 0, 200);
	}
}
void Task_KEY(void *pdata)
{				
  while(1)
	{
		KEY_RUN();
		OSTimeDlyHMSM(0, 0, 0, 10);
	}
}
extern int IR_LearnState;
void Task_OUTPUT(void *pdata)
{	
	IR_LearnState=0;		
  while(1)
	{
//		runTime.OutputStartTime = TIM_GetCounter(DELAY_TIMER);
//		LED_Run();	
////		BEEP_Run();	
//		MOTOR_Run();
//		BLUTOOTH_Run();
//		Zigbee_RUN();
//		IR_Run();
//		runTime.OutputEndTime = TIM_GetCounter(DELAY_TIMER);
//		if(runTime.OutputEndTime - runTime.OutputStartTime > runTime.OutputRunTime)
//			runTime.OutputRunTime = runTime.OutputEndTime - runTime.OutputStartTime;	
//		OSTimeDlyHMSM(0, 0, 1, 0);
		
//	//实验1例子	
//		INPUTDEVICE.exist_people=1;
//		INPUTDEVICE.sound_exceed_threshold=1;
//		INPUTDEVICE.Magnetic_Door_Contact=1;
//		INPUTDEVICE.temperature=30;
//		OUTPUTDEVICE.LED[0]=1;
//		OSTimeDlyHMSM(0,0,1,0);//,OS_OPT_TIME_PERIODIC,&err);//延时2s
//		
//		INPUTDEVICE.exist_people=0;
//		INPUTDEVICE.sound_exceed_threshold=0;
//		INPUTDEVICE.Magnetic_Door_Contact=0;
//		INPUTDEVICE.temperature=20;
//		OUTPUTDEVICE.LED[0]=0;
//		OSTimeDlyHMSM(0,0,1,0);//,OS_OPT_TIME_PERIODIC,&err);//延时2s
//		
//	//实验2例子			
//		OUTPUTDEVICE.LED[0]=1;	
//		OUTPUTDEVICE.LED[1]=1;			
//		OUTPUTDEVICE.LED[2]=1;			
//		OUTPUTDEVICE.LED[3]=1;
//		OUTPUTDEVICE.LED[7]=1;			
//		INPUTDEVICE.sound_exceed_threshold=1;			
//		INPUTDEVICE.LightIntensity=65535;
//		
//		OSTimeDlyHMSM(0,0,1,0);//,OS_OPT_TIME_PERIODIC,&err);//延时2s	
//		
//		OUTPUTDEVICE.LED[0]=0;	
//		OUTPUTDEVICE.LED[1]=0;			
//		OUTPUTDEVICE.LED[2]=0;			
//		OUTPUTDEVICE.LED[3]=0;
//		OUTPUTDEVICE.LED[7]=0;		
//		INPUTDEVICE.sound_exceed_threshold=0;		
//		INPUTDEVICE.LightIntensity=10;
//		
//		OSTimeDlyHMSM(0,0,1,0);//,OS_OPT_TIME_PERIODIC,&err);//延时2s	

////	//实验3例子		
//		INPUTDEVICE.humidity=70;
//		INPUTDEVICE.temperature=30;
//		OSTimeDlyHMSM(0, 0, 2, 0);//延时2s	

//		INPUTDEVICE.humidity=55;
//		INPUTDEVICE.temperature=23;
//		OSTimeDlyHMSM(0, 0, 2, 0);//延时2s		
//		
//		INPUTDEVICE.humidity=40;
//		INPUTDEVICE.temperature=15;
//		OSTimeDlyHMSM(0, 0, 2, 0);//延时2s		

//	//实验4例子		
//		INPUTDEVICE.Distance=7.011;
//		OSTimeDlyHMSM(0, 0, 2, 0);//延时2s	

//		INPUTDEVICE.Distance=4.23;
//		OSTimeDlyHMSM(0, 0, 2, 0);//延时2s		
//		
//		INPUTDEVICE.Distance=1.345;
//		OSTimeDlyHMSM(0, 0, 2, 0);//延时2s	


//		OSTimeDlyHMSM(0, 0, 6, 0);//延时2s
//		IR_LearnState++;
//		if(4==IR_LearnState)IR_LearnState=0;	

	OUTPUTDEVICE.RFID_CARD.rfid_card_Info.Card_State=1;
	OSTimeDlyHMSM(0, 0, 6, 0);//延时2s
	}
}
/***********************************************************************
函数名称：void Task_TX(void *pdata)
功    能：
输入参数：
输出参数：
编写时间：
编 写 人：
注    意：
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
		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}
/***********************************************************************
函数名称：void Task_RX(void *pdata)
功    能：
输入参数：
输出参数：
编写时间：
编 写 人：
注    意：
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
函数名称：void Task_UDP_Client(void *pdata)
功    能：
输入参数：
输出参数：
编写时间：
编 写 人：
注    意：
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
		LocalTime ++;
		LwIP_Periodic_Handle(LocalTime);		
		runTime.UdpEndTime = TIM_GetCounter(DELAY_TIMER);
		if(runTime.UdpEndTime - runTime.UdpStartTime > runTime.UdpRunTime)
			runTime.UdpRunTime = runTime.UdpEndTime - runTime.UdpStartTime;
		OSTimeDlyHMSM(0, 0, 0, 10);//挂起10ms，以便其他线程运行
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
		LocalTime ++;
		LwIP_Periodic_Handle(LocalTime);		
		OSTimeDlyHMSM(0, 0, 0, 100);//挂起10ms，以便其他线程运行
	}
}

void Task_OLEDDisplay(void *pdata)
{
	FATFS fs;
	f_mount(0, &fs);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC,ENABLE);//要开启STenwim，必须先开CRC时钟
  GUI_Init();
	
//	Create_XBF16("0:/SYSTEM/FONT/XBF20.xbf");	
//	GUI_SetBkColor(GUI_BLACK);
//	GUI_SetColor(0x00d1fef0);
//	GUI_SetFont(&GUI_Font32_ASCII);
//	GUI_SetTextMode(GUI_TM_TRANS);	GUI_UC_SetEncodeUTF8();
//	GUI_DispStringHCenterAt("111111111",100,0);
//	GUI_Clear();

//	GUI_SetFont(&XBF16_Font);
//	GUI_SetColor(GUI_RED);
//	GUI_SetTextMode(GUI_TM_TRANS);
//	GUI_Clear();

//	GUI_DispStringHCenterAt("按照十进制整数格式输出，显示 a=1234  ",300,0);//("ALIENTEK XBF 汉字显示");
//	while(1);
	
//	MainTask();
	
	bmpdisplay_demo();
}


void Task_BEEP_MUSIC_Display(void *pdata)
{
	Beep_Config();
	while(1){
		musicPlay();
	}
}










