/***********************************************************************
�ļ����ƣ�main.C
��    �ܣ�
��дʱ�䣺
�� д �ˣ�������Ƕ���������Ӽ����Ŷ�
ע    �⣺
***********************************************************************/
#include "main.h"

/*********************************************************/
/*********************************************************/


int main(void)
{
	//��ʼ������
	getUniqueID(uniqueID);
	BSP_Init();
	//��ʼ��ϵͳ
	OSInit();
	//������������
	OSTaskCreate(	Task_StartUp,               		    				//ָ����������ָ��
                  	(void *) 0,												//����ʼִ��ʱ�����ݸ�����Ĳ�����ָ��
					(OS_STK *)&Stk_TaskStartUp[TASK_STARTUP_STK_SIZE - 1],	//���������Ķ�ջ��ջ��ָ��   �Ӷ����µݼ�
					(INT8U) OS_USER_PRIO_LOWEST);							//�������������ȼ�  

	//���ļ�������0  
	OSTimeSet(0);

	//����UCOS-II�ں�
	OSStart();

	return 0;
}
//���������ջ
OS_STK Stk_TaskStartUp[TASK_STARTUP_STK_SIZE];

void Task_StartUp(void *pdata)
{
	
	//��ʼ��UCOSʱ��
	//OS_TICKS_PER_SEC Ϊ UCOS-II ÿ�������
	SysTick_Config(SystemCoreClock/OS_TICKS_PER_SEC - 1);
	
	q_msg_zigbee_rx=OSQCreate(&MsgGrp_q_msg_zigbee_rx[0],ZIGBEE_RX_ARRY_NUM);				
	q_msg_zigbee_tx=OSQCreate(&MsgGrp_q_msg_zigbee_tx[0],ZIGBEE_TX_ARRY_NUM);	
	q_msg_bluetooth_tx=OSQCreate(&MsgGrpq_msg_bluetooth_tx[0],BLUETOOTH_TX_ARRY_NUM);			
	//���ȼ�˵����ʹ��OS_USER_PRIO_GET(n)������ȡ
	//OS_USER_PRIO_GET(0)���,OS_USER_PRIO_GET(1)��֮����������
	//OS_USER_PRIO_GET(0)����ߵ����ȼ�����Ҫ�����ڴ������������Ҫ�����ȴ������������Ϊ���������ȼ�  

	//OSTaskCreate(	Task_Xxx,               		    					//ָ����������ָ��
    //              (void *)0,												//����ʼִ��ʱ�����ݸ�����Ĳ�����ָ��
	//				(OS_STK *)&Stk_TaskXxx[TASK_XXX_STK_SIZE - 1],			//���������Ķ�ջ��ջ��ָ��   �Ӷ����µݼ�
	//				(INT8U) OS_USER_PRIO_GET(N));							//�������������ȼ�  

//	OSTaskCreate(Task_TCP_Client, (void *)0, &Stk_Task_TCP_Client[TASK_TCP_CLIENT_STK_SIZE-1], OS_USER_PRIO_GET(2));//������������ʵ�����ٿ���
	OSTaskCreate(Task_UDP_Client, (void *)0, &Stk_Task_UDP_Client[TASK_UDP_CLIENT_STK_SIZE-1], OS_USER_PRIO_GET(3));
//	OSTaskCreate(Task_OUTPUT, (void *)0, &Stk_Task_OUTPUT[TASK_TEST_OUTPUT_STK_SIZE-1], OS_USER_PRIO_GET(8));
//	OSTaskCreate(Task_INPUT, (void *)0, &Stk_Task_INPUT[TASK_TEST_INPUT_STK_SIZE-1], OS_USER_PRIO_GET(7));
//	OSTaskCreate(Task_KEY, (void *)0, &Stk_Task_KEY[TASK_TEST_KEY_STK_SIZE-1], OS_USER_PRIO_GET(6));
	OSTaskCreate(Task_TX, (void *)0, &Stk_Task_TX[TASK_TEST_TX_STK_SIZE-1], OS_USER_PRIO_GET(4));
  OSTaskCreate(Task_RX, (void *)0, &Stk_Task_RX[TASK_TEST_RX_STK_SIZE-1], OS_USER_PRIO_GET(5));
//		//OLED��ʾ����
//	OSTaskCreate(Task_OLEDDisplay, (void *)0, &Stk_Task_OLED_DISPLAY[TASK_OLED_DISPLAY_STK_SIZE-1], OS_USER_PRIO_GET(9));
//	//��������
//	OSTaskCreate(Task_BEEP_MUSIC_Display, (void *)0, &Stk_Task_BEEP_MUSIC[TASK_BEEP_MUSIC_STK_SIZE-1], OS_USER_PRIO_GET(10));
	OSTaskSuspend(OS_USER_PRIO_LOWEST);
	while(1)
	{
		//ѭ�����س���ִ�����
		//ͨ�����������ʹһ��ϵͳ״̬����˸����ʾϵͳ��������
		//GPIO_ToggleBits(LED2);
		//GPIO_ToggleBits(LED3);
		OSTimeDlyHMSM(0, 0, 0, 1000);//1000ms
	}
}
