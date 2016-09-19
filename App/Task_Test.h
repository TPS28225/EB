/***********************************************************************
文件名称：
功    能：
编写时间：
编 写 人：
注    意：
***********************************************************************/

#ifndef _APP_TASK_TEST_H_
#define _APP_TASK_TEST_H_

#include "main.h"


#define TASK_TEST_TX_STK_SIZE	    2048
#define TASK_TEST_RX_STK_SIZE	    2048
#define TASK_TEST_OUTPUT_STK_SIZE	512
#define TASK_UDP_CLIENT_STK_SIZE	2048
#define TASK_TCP_CLIENT_STK_SIZE	2048
#define TASK_TEST_INPUT_STK_SIZE	512
#define TASK_TEST_KEY_STK_SIZE		512
#define TASK_OLED_DISPLAY_STK_SIZE (1024)
#define TASK_BEEP_MUSIC_STK_SIZE	(256)
#define TASK_STATE_TEST_STK_SIZE	(128)

extern OS_EVENT * q_msg_zigbee_rx;			
extern OS_EVENT * q_msg_zigbee_tx;
extern OS_EVENT * q_msg_bluetooth_tx;	

extern int pong_flag;

extern void * MsgGrp_q_msg_zigbee_rx[ZIGBEE_RX_ARRY_NUM];
extern void * MsgGrp_q_msg_zigbee_tx[ZIGBEE_TX_ARRY_NUM];
extern void * MsgGrpq_msg_bluetooth_tx[BLUETOOTH_TX_ARRY_NUM];

extern OS_STK Stk_Task_TX[TASK_TEST_TX_STK_SIZE];
extern OS_STK Stk_Task_RX[TASK_TEST_RX_STK_SIZE];
extern OS_STK Stk_Task_OUTPUT[TASK_TEST_OUTPUT_STK_SIZE];
extern OS_STK Stk_Task_UDP_Client[TASK_UDP_CLIENT_STK_SIZE];
extern OS_STK Stk_Task_TCP_Client[TASK_TCP_CLIENT_STK_SIZE];
extern OS_STK Stk_Task_INPUT[TASK_TEST_INPUT_STK_SIZE];
extern OS_STK Stk_Task_KEY[TASK_TEST_KEY_STK_SIZE];
extern OS_STK Stk_Task_OLED_DISPLAY[TASK_OLED_DISPLAY_STK_SIZE];
extern OS_STK Stk_Task_BEEP_MUSIC[TASK_BEEP_MUSIC_STK_SIZE];
extern OS_STK Stk_Task_STATE_TEST[TASK_STATE_TEST_STK_SIZE];

void Task_TX(void *pdata);
void Task_RX(void *pdata);
void Task_OUTPUT(void *pdata);
void Task_UDP_Client(void *pdata);
void Task_INPUT(void *pdata);
void Task_TCP_Client(void *pdata);
void Task_KEY(void *pdata);
void Task_OLEDDisplay(void *pdata);
void Task_BEEP_MUSIC_Display(void *pdata);
void Task_STATE_TEST(void *pdata);
#endif
