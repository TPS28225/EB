 /***********************************************************************
文件名称：TCP_CLIENT.H
功    能：完成TCP的数据收发
编写时间：2013.4.25
编 写 人：赵
注    意：
***********************************************************************/
#ifndef  _TCP_CLIENT_H_
#define  _TCP_CLIENT_H_
#include "main.h"

/***************开发板ip及MAC定义*************************/
/***************真正起作用的在main.h里********************/
//#define BOARD_IP  			 192,168,87,252   		//开发板ip 
//#define BOARD_NETMASK   	 255,255,255,0   		//开发板子网掩码
//#define BOARD_WG		   	  192,168,87,1 			//开发板子网关
//#define BOARD_MAC_ADDR       0,0,0,0,0,1			//开发板MAC地址

#define TCP_LOCAL_PORT     		1030 
#define TCP_SERVER_PORT    		7298
#define TCP_SERVER_IP   			192,168,87,222	//192,168,87,111//115,28,86,143 //192,168,87,105//服务器IP

extern struct tcp_pcb *tcp_client_pcb;

void TCP_Client_Init(u16_t local_port,u16_t remote_port,unsigned char a,unsigned char b,unsigned char c,unsigned char d);
err_t TCP_Client_Send_Data(struct tcp_pcb *cpcb,unsigned char *buff,unsigned int length);
struct tcp_pcb *Check_TCP_Connect(void);
void Delay_s(unsigned long ulVal); /* 利用循环产生一定的延时 */
#endif

