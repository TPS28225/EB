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
#include "exammanager.h"
__align(8) OS_STK Stk_Task_RX[TASK_TEST_RX_STK_SIZE];
__align(8) OS_STK Stk_Task_TX[TASK_TEST_TX_STK_SIZE];
__align(8) OS_STK Stk_Task_OUTPUT[TASK_TEST_OUTPUT_STK_SIZE];
__align(8) OS_STK Stk_Task_INPUT[TASK_TEST_INPUT_STK_SIZE];
__align(8) OS_STK Stk_Task_KEY[TASK_TEST_KEY_STK_SIZE];
__align(8) OS_STK Stk_Task_UDP_Client[TASK_UDP_CLIENT_STK_SIZE];
__align(8) OS_STK Stk_Task_TCP_Client[TASK_TCP_CLIENT_STK_SIZE];
__align(8) OS_STK Stk_Task_STATE_TEST[TASK_STATE_TEST_STK_SIZE];

//显示屏
__align(8) OS_STK Stk_Task_OLED_DISPLAY[TASK_OLED_DISPLAY_STK_SIZE];
//声音
__align(8) OS_STK Stk_Task_BEEP_MUSIC[TASK_BEEP_MUSIC_STK_SIZE];
tx_buf_t  tx_buf;
rx_buf_t  rx_buf;

char uniqueID[33]={0};

INPUTDEVICE_MEASURE INPUTDEVICE;
OUTPUTDEVICE_CONTROL OUTPUTDEVICE;

OS_EVENT * q_msg_zigbee_rx;		
OS_EVENT * q_msg_zigbee_tx;	
OS_EVENT * q_msg_bluetooth_tx;

int pong_flag=0;

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

void Clear_Sensor_Data(void)
{
	OUTPUTDEVICE.LED[0]=0;
	OUTPUTDEVICE.LED[1]=0;
	OUTPUTDEVICE.LED[2]=0;
	OUTPUTDEVICE.LED[3]=0;
	OUTPUTDEVICE.LED[4]=0;
	OUTPUTDEVICE.LED[5]=0;
	OUTPUTDEVICE.LED[6]=0;
	OUTPUTDEVICE.LED[7]=0;
	OUTPUTDEVICE.Motor=0;
	OUTPUTDEVICE.Beep=0;	
	OUTPUTDEVICE.RF_State = 0;//add by W
	OUTPUTDEVICE.picture_num=0;

}
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
  while(1)
	{
		UltrasonicWave_StartMeasure();
		DHT11_Read_Data();
		LightIntensitySensor_measure();
//		EV1527_Run();//待进一步调试
		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}
void Task_KEY(void *pdata)
{				
  while(1)
	{
		KEY_RUN();
		EV1527_Run();
		OSTimeDlyHMSM(0, 0, 0, 100);
	}
}
extern int IR_LearnState;
void Task_OUTPUT(void *pdata)
{	
	IR_LearnState=0;		
  while(1)
	{
		if(OUTPUTDEVICE.CLEAR>=1){
			Clear_Sensor_Data();
			OUTPUTDEVICE.CLEAR=0;
		}
		runTime.OutputStartTime = TIM_GetCounter(DELAY_TIMER);
		LED_Run();	
		MOTOR_Run();
		BLUTOOTH_Run();
		Zigbee_RUN();
		IR_Run();
		runTime.OutputEndTime = TIM_GetCounter(DELAY_TIMER);
		if(runTime.OutputEndTime - runTime.OutputStartTime > runTime.OutputRunTime)
			runTime.OutputRunTime = runTime.OutputEndTime - runTime.OutputStartTime;	

		OSTimeDlyHMSM(0, 0, 0, 200);//延时500ms
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
	char *msg;
	
//	OSTimeDlyHMSM(0, 0, 2, 0);	
//	//这里LOGIN和REG换了下顺序，是为了让接收方收到的顺序正确
//	msg = makeJson(LOGIN);
//	strlen(msg);
//	msgReporter(msg,strlen(msg));
//	free(msg);
	
	OSTimeDlyHMSM(0, 0, 5, 0);
	
//	msg = makeJson(REG);
//	strlen(msg);
//	msgReporter(msg,strlen(msg));
//	free(msg);
	
  while(1)
	{	
		runTime.TxStartTime = TIM_GetCounter(DELAY_TIMER);
		
		if(3<pong_flag){		
			msg = makeJson(PONG);
			pong_flag=0;
			strlen(msg);
			msgReporter(msg,strlen(msg));
			free(msg);	
		}
		else{
			msg = makeJson(RPT);
			strlen(msg);
			msgReporter(msg,strlen(msg));
			free(msg);		
		}
		
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
		LocalTime +=10;
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
		LocalTime +=10;
		LwIP_Periodic_Handle(LocalTime);		
		OSTimeDlyHMSM(0, 0, 0, 10);//挂起10ms，以便其他线程运行
	}
}
void Task_OLEDDisplay(void *pdata)
{
	u8 result,T_counter=0;
	FATFS fs;
	static FIL BMPFile;
	f_mount(0, &fs);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC,ENABLE);//要开启STenwim，必须先开CRC时钟
  GUI_Init();
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(GUI_WHITE);
	GUI_SetTextMode(GUI_TM_NORMAL);
	GUI_UC_SetEncodeUTF8();
	LCD_Clear(BLACK);//GUI_Clear();
	GUI_SetFont(GUI_FONT_24_ASCII);
	OUTPUTDEVICE.Cureent_Exam_Num=0;
//	MainTask();

	result = f_open(&BMPFile,"0:/picture/face.bmp",FA_READ);	//打开文件
	//文件打开错误
	if(result != FR_OK) 	
	{		
		GUI_SetBkColor(GUI_BLUE);	
		LCD_Clear(BLUE);//GUI_Clear();
		GUI_DispStringAt("HARDWARE ERROR: ",10,40);
		GUI_DispStringAt("NOW FIXING:   ",10,80);
		//GUI_DispDec  (result, 3);
		GUI_DispDecAt (result, 230, 40, 3);
		while(1){
			result = f_open(&BMPFile,"0:/picture/face.bmp",FA_READ);	//打开文件
			GUI_DispDecAt (result, 230, 40, 3);
			GUI_DispDecAt (T_counter, 230, 80,2);
			GUI_DispChar('%');
			T_counter+=10;
			//文件打开错误
			if(result == FR_OK)break;
			OSTimeDlyHMSM(0, 0, 0, 100);//挂起100ms，以便其他线程运行
			if(T_counter>100){			
				GUI_DispStringAt ("SORRY! ERROR CAN NOT BE FIXED. ", 10,120);
				GUI_DispStringAt ("PLEASE POWER OFF AND RESTART...", 10,160);
				while(1){
					OSTimeDlyHMSM(0, 0, 2, 0);//挂起100ms，以便其他线程运行
				}
			}
		}	
		GUI_SetBkColor(GUI_BLACK);
		GUI_SetColor(GUI_WHITE);
		LCD_Clear(BLACK);//GUI_Clear();	
		GUI_DispStringAt("SDCARD OK.                ",10,90);	
		f_close(&BMPFile);
	}
	
	GUI_Init();
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(GUI_WHITE);
	GUI_SetTextMode(GUI_TM_NORMAL);
	GUI_UC_SetEncodeUTF8();
	LCD_Clear(BLACK);//GUI_Clear();
	GUI_SetFont(GUI_FONT_24_ASCII);
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_SetFont(GUI_FONT_16_ASCII);
	
	while(1){
		

		
		//清除输出设备状态
		GUI_Init();
		GUI_SetBkColor(GUI_BLACK);
		GUI_SetColor(GUI_WHITE);
		GUI_SetTextMode(GUI_TM_TRANS);
		GUI_SetFont(GUI_FONT_16_ASCII);
		
		OUTPUTDEVICE.LED[0]=0;
		OUTPUTDEVICE.LED[1]=0;
		OUTPUTDEVICE.LED[2]=0;
		OUTPUTDEVICE.LED[3]=0;
		OUTPUTDEVICE.LED[4]=0;
		OUTPUTDEVICE.LED[5]=0;
		OUTPUTDEVICE.LED[6]=0;
		OUTPUTDEVICE.LED[7]=0;
		OUTPUTDEVICE.Motor=0;
		OUTPUTDEVICE.Beep=0;
		OUTPUTDEVICE.picture_num=0;
		DHT11_Init();//
		LightIntensitySensor_Init();//
		RC522_Init();//
		
		GUI_SetTextMode(GUI_TM_TRANS);
		GUI_SetFont(GUI_FONT_16_ASCII);
			
		switch(OUTPUTDEVICE.Cureent_Exam_Num){			
			case 0:bmpdisplay_exam0();break;
			
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

			case 10:bmpdisplay_exam10();break;
			
			case 11:bmpdisplay_exam11();break;
			
			default:OUTPUTDEVICE.Cureent_Exam_Num=0;
		}
		OSTimeDlyHMSM(0, 0, 0, 200);//挂起200ms，以便其他线程运行
	}	
}


void Task_BEEP_MUSIC_Display(void *pdata)
{
	while(1){
		BEEP_Run();
		OSTimeDlyHMSM(0, 0, 0, 200);//挂起100ms，以便其他线程运行
	}
}
u32 Stak_OLED_Free=0xffffffff;
void Task_STATE_TEST(void *pdata){
	OS_STK_DATA Stak_OLED,Stak_OUTPUT;

	while(1){		
		GPIO_SetBits(GPIOA,GPIO_Pin_5);		
		OSTimeDlyHMSM(0, 0, 0, 100);//挂起100ms，以便其他线程运行
		OSTaskStkChk(OS_USER_PRIO_GET(3), &Stak_OLED);
		if(Stak_OLED.OSFree<Stak_OLED_Free)
			Stak_OLED_Free=Stak_OLED.OSFree;
		
		OSTaskStkChk(OS_USER_PRIO_GET(3), &Stak_OUTPUT);
		if(Stak_OUTPUT.OSFree<Stak_OLED_Free)
			Stak_OLED_Free=Stak_OLED.OSFree;
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);				
		OSTimeDlyHMSM(0, 0, 2, 0);//挂起100ms，以便其他线程运行
	}	
}








