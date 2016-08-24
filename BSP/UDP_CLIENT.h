/***********************************************************************
文件名称：UDP_CLIENT.H
功    能：完成UDP的数据收发
编写时间：2013.4.25
编 写 人：赵
注    意：
***********************************************************************/
#ifndef _UDP_CLIENT_H_
#define _UDP_CLIENT_H_


/***************开发板ip及MAC定义*************************/
#define BOARD_IP  			 	192,168,87,252   		//开发板ip 
#define BOARD_NETMASK   	 	255,255,255,0   		//开发板子网掩码
#define BOARD_WG		   	 	 192,168,87,1   			//开发板子网关
#define BOARD_MAC_ADDR      	0,0,0,0,0,1				//开发板MAC地址

#define UDP_CLIENT_PORT			1030
#define UDP_REMOTE_PORT			1031
#define UDP_UDP_REMOTE_IP		192,168,87,105


extern struct udp_pcb *udp_pcb;
extern struct ip_addr ipaddr;
extern struct pbuf *udp_p;

void UDP_client_init(void);
void UDP_Send_Data(struct udp_pcb *pcb,struct pbuf *p);
void My_IP4_ADDR(struct ip_addr *ipaddr,unsigned char a,unsigned char b,unsigned char c,unsigned char d);
static void UDP_Delay(unsigned long ulVal);
void msgParser(void);
void msgReporter(char *msg, int length);
#endif

