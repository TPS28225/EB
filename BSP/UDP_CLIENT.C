/***********************************************************************
文件名称：UDP_CLIENT.C
功    能：完成UDP的数据收发
编写时间：2013.4.25
编 写 人：
注    意：
***********************************************************************/

#include "main.h"

struct udp_pcb *udp_pcb;
struct ip_addr ipaddr;
struct pbuf *udp_p;

extern tx_buf_t  tx_buf;
extern rx_buf_t  rx_buf;

void msgReporter(char *msg, int length)
{			
	if(tx_buf.numOfBuf < MAX_RX_BUF)
	{						
		memcpy(&tx_buf.buffer[tx_buf.numOfBuf][0], msg, length);
		tx_buf.buffer[tx_buf.numOfBuf][length] = 0;
		tx_buf.numOfBuf++;		
	}
}
void msgParser(void)
{
	char * msg;
	while(rx_buf.numOfBuf > 0)
	{
		msg = rx_buf.buffer[--rx_buf.numOfBuf];	
		parserJson(msg);
	}
}

/***********************************************************************
函数名称：udp_server_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p,struct ip_addr *addr, u16_t port)
功    能：udp数据接收和发送
输入参数：
输出参数：
编写时间：2013.4.25
编 写 人：
注    意：这是一个回调函数，当一个udp段到达这个连接时会被调用
***********************************************************************/
void udp_server_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p,struct ip_addr *addr, u16_t port)
{
	struct pbuf *p_temp = p;
	while(p_temp != NULL)
	{
		if(rx_buf.numOfBuf < MAX_RX_BUF)
		{
			memcpy(&rx_buf.buffer[rx_buf.numOfBuf][0], p_temp->payload, p_temp->len);
			rx_buf.buffer[rx_buf.numOfBuf][p_temp->len] = 0;
			rx_buf.numOfBuf++;
		}
		p_temp = p_temp->next;
	}
		//udp_sendto(pcb,p_temp,&destAddr,port); /* 将收到的数据再发送出去 */			
	pbuf_free(p); 						/* 释放该UDP段 */
}
/***********************************************************************
函数名称：void UDP_client_init(void)
功    能：完成udp客户端初始化
输入参数：
输出参数：
编写时间：2013.4.25
编 写 人：
注    意：
***********************************************************************/
void UDP_client_init(void)
{
	udp_p = pbuf_alloc(PBUF_RAW,MAX_TXRX_BUF_SIZE,PBUF_RAM);
	My_IP4_ADDR(&ipaddr,UDP_UDP_REMOTE_IP);				//远端IP
	udp_pcb = udp_new();
	udp_bind(udp_pcb,IP_ADDR_ANY,UDP_CLIENT_PORT); 	/* 绑定本地IP地址 */
	udp_connect(udp_pcb,&ipaddr,UDP_REMOTE_PORT); 		/* 连接远程主机 */		
	udp_recv(udp_pcb,udp_server_recv,NULL); 
}
/***********************************************************************
函数名称：My_IP4_ADDR(void)
功    能：IP地址的装配
输入参数：
输出参数：
编写时间：2013.4.25
编 写 人：
注    意：
***********************************************************************/
void My_IP4_ADDR(struct ip_addr *ipaddr,unsigned char a,unsigned char b,unsigned char c,unsigned char d)
{
	ipaddr->addr = htonl(((u32_t)((a) & 0xff) << 24) | \
                               ((u32_t)((b) & 0xff) << 16) | \
                               ((u32_t)((c) & 0xff) << 8) | \
                                (u32_t)((d) & 0xff));
}
/***********************************************************************
函数名称：void UDP_client_init(void)
功    能：完成udp客户端初始化
输入参数：
输出参数：
编写时间：2013.4.25
编 写 人：
注    意：
***********************************************************************/
void UDP_Send_Data(struct udp_pcb *pcb,struct pbuf *p)
{
	udp_send(pcb,p);
	UDP_Delay(0XFFFFF);//延时，不能发送太快	
}

/***********************************************************************
函数名称：Delay(unsigned long ulVal)
功    能：利用循环产生一定的延时
输入参数：
输出参数：
编写时间：2013.4.25
编 写 人：
注    意：
***********************************************************************/
static void UDP_Delay(unsigned long ulVal) /* 利用循环产生一定的延时 */
{
	while ( --ulVal != 0 );
}
