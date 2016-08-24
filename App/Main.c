/***********************************************************************
文件名称：main.C
功    能：
编写时间：
编 写 人：北京智嵌物联网电子技术团队
注    意：
***********************************************************************/
#include "main.h"

/*********************************************************/
/*********************************************************/


int main(void)
{
	//初始化板子
	getUniqueID(uniqueID);
	BSP_Init();
	//初始化系统
	OSInit();
	//创建启动任务
	OSTaskCreate(	Task_StartUp,               		    				//指向任务代码的指针
                  	(void *) 0,												//任务开始执行时，传递给任务的参数的指针
					(OS_STK *)&Stk_TaskStartUp[TASK_STARTUP_STK_SIZE - 1],	//分配给任务的堆栈的栈顶指针   从顶向下递减
					(INT8U) OS_USER_PRIO_LOWEST);							//分配给任务的优先级  

	//节拍计数器清0  
	OSTimeSet(0);

	//启动UCOS-II内核
	OSStart();

	return 0;
}
//启动任务堆栈
OS_STK Stk_TaskStartUp[TASK_STARTUP_STK_SIZE];

void Task_StartUp(void *pdata)
{
	
	//初始化UCOS时钟
	//OS_TICKS_PER_SEC 为 UCOS-II 每秒嘀嗒数
	SysTick_Config(SystemCoreClock/OS_TICKS_PER_SEC - 1);
	
	q_msg_zigbee_rx=OSQCreate(&MsgGrp_q_msg_zigbee_rx[0],ZIGBEE_RX_ARRY_NUM);				
	q_msg_zigbee_tx=OSQCreate(&MsgGrp_q_msg_zigbee_tx[0],ZIGBEE_TX_ARRY_NUM);	
	q_msg_bluetooth_tx=OSQCreate(&MsgGrpq_msg_bluetooth_tx[0],BLUETOOTH_TX_ARRY_NUM);			
	//优先级说明，使用OS_USER_PRIO_GET(n)宏来获取
	//OS_USER_PRIO_GET(0)最高,OS_USER_PRIO_GET(1)次之，依次类推
	//OS_USER_PRIO_GET(0)：最高的优先级，主要用于在处理紧急事务，需要将优先处理的任务设置为最高这个优先级  

	//OSTaskCreate(	Task_Xxx,               		    					//指向任务代码的指针
    //              (void *)0,												//任务开始执行时，传递给任务的参数的指针
	//				(OS_STK *)&Stk_TaskXxx[TASK_XXX_STK_SIZE - 1],			//分配给任务的堆栈的栈顶指针   从顶向下递减
	//				(INT8U) OS_USER_PRIO_GET(N));							//分配给任务的优先级  

//	OSTaskCreate(Task_TCP_Client, (void *)0, &Stk_Task_TCP_Client[TASK_TCP_CLIENT_STK_SIZE-1], OS_USER_PRIO_GET(2));//在移入真正的实验板后再开启
	OSTaskCreate(Task_UDP_Client, (void *)0, &Stk_Task_UDP_Client[TASK_UDP_CLIENT_STK_SIZE-1], OS_USER_PRIO_GET(3));
//	OSTaskCreate(Task_OUTPUT, (void *)0, &Stk_Task_OUTPUT[TASK_TEST_OUTPUT_STK_SIZE-1], OS_USER_PRIO_GET(8));
//	OSTaskCreate(Task_INPUT, (void *)0, &Stk_Task_INPUT[TASK_TEST_INPUT_STK_SIZE-1], OS_USER_PRIO_GET(7));
//	OSTaskCreate(Task_KEY, (void *)0, &Stk_Task_KEY[TASK_TEST_KEY_STK_SIZE-1], OS_USER_PRIO_GET(6));
	OSTaskCreate(Task_TX, (void *)0, &Stk_Task_TX[TASK_TEST_TX_STK_SIZE-1], OS_USER_PRIO_GET(4));
  OSTaskCreate(Task_RX, (void *)0, &Stk_Task_RX[TASK_TEST_RX_STK_SIZE-1], OS_USER_PRIO_GET(5));
//		//OLED显示任务
//	OSTaskCreate(Task_OLEDDisplay, (void *)0, &Stk_Task_OLED_DISPLAY[TASK_OLED_DISPLAY_STK_SIZE-1], OS_USER_PRIO_GET(9));
//	//声音任务
//	OSTaskCreate(Task_BEEP_MUSIC_Display, (void *)0, &Stk_Task_BEEP_MUSIC[TASK_BEEP_MUSIC_STK_SIZE-1], OS_USER_PRIO_GET(10));
	OSTaskSuspend(OS_USER_PRIO_LOWEST);
	while(1)
	{
		//循环看守程序执行情况
		//通常情况下这里使一个系统状态灯闪烁，表示系统正在运行
		//GPIO_ToggleBits(LED2);
		//GPIO_ToggleBits(LED3);
		OSTimeDlyHMSM(0, 0, 0, 1000);//1000ms
	}
}
