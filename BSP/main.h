/***********************************************************************
文件名称：
功    能：
编写时间：
编 写 人：
注    意：
***********************************************************************/
 
#ifndef _MAIN_H_
#define _MAIN_H_


//添加必要的头文件
#include "stm32f2xx.h" 
#include "devicemanager.h"
#include "stm32f2x7_eth.h"
#include "stm32f2x7_eth_bsp.h"
#include "stm32f2x7_sdio_bsp.h"
#include "usart.h"
#include "ff.h"	
#include "string.h"
#include "lwip/UDP.h"
#include "lwip/tcp.h"
#include "netconf.H"
#include "M_Type_P.h"
#include "M_CMSIS_P.h" 
#include "M_Global.h"
#include "Task_Startup.h"
#include "Bsp_Global.h"
#include "Task_Test.h" 
#include "TCP_CLIENT.h"
#include "UDP_CLIENT.h"
#include "NVIC.h"
#include "parser.h"
#include "config.h"
#include "LED.H"
#include "parserJSON.h"
#include "devicemanager.h"
#include "beep.h"
#include "motor.h"
#include "Zigbee.h"
#include "BLUTOOTH.h"
#include "delay.h"
#include "UltrasonicWave.h"
#include "KEY.h"
#include "dht11.h"
#include "LightIntensitySensor.h"
#include "RC522.h"
#include "ir.h"
#include "ILI93xx.h"
#include "GUI.h"
#include "sram.h"	 

//ET Module版本号
#define M_VERSION	100

//1单片机环境 

#define M_DEV_MCU   1
 #define RMII_MODE  1
/* MAC ADcontinue;continue;DRESS: MAC_ADDR0:MAC_ADDR1:MAC_ADDR2:MAC_ADDR3:MAC_ADDR4:MAC_ADDR5 */
#define MAC_ADDR0   2
#define MAC_ADDR1   0
#define MAC_ADDR2   0
#define MAC_ADDR3   0
#define MAC_ADDR4   0
#define MAC_ADDR5   0
 
/*Static IP ADDRESS: IP_ADDR0.IP_ADDR1.IP_ADDR2.IP_ADDR3 */
#define IP_ADDR0   192
#define IP_ADDR1   168
#define IP_ADDR2   87
#define IP_ADDR3   252
   
/*NETMASK*/
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255
#define NETMASK_ADDR3   0

/*Gateway Address*/
#define GW_ADDR0   192
#define GW_ADDR1   168
#define GW_ADDR2   87
#define GW_ADDR3   1  
//全局初始化函数声明
void M_Global_init(void);

#define MAX_TX_BUF 5
#define MAX_RX_BUF 5

#define MAX_TXRX_BUF_SIZE 1000    

typedef struct{
	char buffer[MAX_TX_BUF][MAX_TXRX_BUF_SIZE];
	int  numOfBuf;
}tx_buf_t;

typedef struct{
	char buffer[MAX_RX_BUF][MAX_TXRX_BUF_SIZE];
	int  numOfBuf;
}rx_buf_t;

extern tx_buf_t  tx_buf;
extern rx_buf_t  rx_buf;

extern INPUTDEVICE_MEASURE INPUTDEVICE;
extern OUTPUTDEVICE_CONTROL OUTPUTDEVICE;

extern char uniqueID[33];
//////////////////////////////////////////////////////////////////////////
/////////////////////////以下包含不同模块的头文件/////////////////////////
//////////////////////////////////////////////////////////////////////////

//软延时函数
#include "M_Delay_P.h"

void Delay(uint32_t nCount);

#endif
