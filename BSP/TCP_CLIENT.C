/***********************************************************************
文件名称：TCP_CLIENT.C
功    能：完成TCP的客户端的数据收发
编写时间：2013.4.25
编 写 人：
注    意：
***********************************************************************/

#include "main.h"
#include "string.h"

struct tcp_pcb *tcp_client_pcb;
unsigned char connect_flag = 0;
/***********************************************************************
函数名称：Delay_s(unsigned long ulVal)
功    能：利用循环产生一定的延时
输入参数：
输出参数：
编写时间：2013.4.25
编 写 人：
注    意：
***********************************************************************/
void Delay_s(unsigned long ulVal) /* 利用循环产生一定的延时 */
{
	while ( --ulVal != 0 );
}

/***********************************************************************
函数名称：void TCP_Client_Send_Data(unsigned char *buff)
功    能：TC[客户端发送数据函数
输入参数：
输出参数：
编写时间：2013.4.25
编 写 人：
注    意：for(cpcb = tcp_active_pcbs;cpcb != NULL; cpcb = cpcb->next) 
***********************************************************************/
err_t TCP_Client_Send_Data(struct tcp_pcb *cpcb,unsigned char *buff,unsigned int length)
{
	err_t err;

	err = tcp_write(cpcb,buff,length,TCP_WRITE_FLAG_COPY);	//发送数据
	tcp_output(cpcb);
	//tcp_close(tcp_client_pcb);				//发送完数据关闭连接,根据具体情况选择使用	
	return err;					
}

/***********************************************************************
函数名称：Check_TCP_Connect(void)
功    能：检查连接
输入参数：
输出参数：
编写时间：2013.4.25
编 写 人：
注    意：for(cpcb = tcp_active_pcbs;cpcb != NULL; cpcb = cpcb->next) 
***********************************************************************/\
struct tcp_pcb *Check_TCP_Connect(void)
{
	struct tcp_pcb *cpcb = 0;
	connect_flag = 0;
	for(cpcb = tcp_active_pcbs;cpcb != NULL; cpcb = cpcb->next)
	{
	//	if(cpcb->local_port == TCP_LOCAL_PORT && cpcb->remote_port == TCP_SERVER_PORT)		//如果TCP_LOCAL_PORT端口指定的连接没有断开
		if(cpcb -> state == ESTABLISHED)  //如果得到应答，则证明已经连接上
		{
			OUTPUTDEVICE.LED[7]=10;//TIM_SetCompare3(TIM3,100);
			connect_flag = 1;  						//连接标志
			break;							   	
		}
	}

	if(connect_flag == 0)  	// TCP_LOCAL_PORT指定的端口未连接或已断开
	{
		TIM_SetCompare3(TIM3,0);	
		TCP_Client_Init(TCP_LOCAL_PORT,TCP_SERVER_PORT,TCP_SERVER_IP); //重新连接
		cpcb = 0;
	}
	return cpcb;	
}
/***********************************************************************
函数名称：err_t RS232_TCP_Connected(void *arg,struct tcp_pcb *pcb,err_t err)
功    能：完成RS232到TCP的数据发送
输入参数：
输出参数：
编写时间：2013.4.25
编 写 人：
注    意：这是一个回调函数，当TCP客户端请求的连接建立时被调用
***********************************************************************/
err_t TCP_Connected(void *arg,struct tcp_pcb *pcb,err_t err)
{
	//tcp_client_pcb = pcb;
	return ERR_OK;
}
/***********************************************************************
函数名称：TCP_Client_Recv(void *arg, struct tcp_pcb *pcb,struct pbuf *p,err_t err)
功    能：tcp客户端接收数据回调函数
输入参数：
输出参数：
编写时间：2013.4.25
编 写 人：
注    意：这是一个回调函数，当TCP服务器发来数据时调用
***********************************************************************/

unsigned char *p_data;
err_t  TCP_Client_Recv(void *arg, struct tcp_pcb *pcb,struct pbuf *p,err_t err)
{
	struct pbuf *p_temp = p;
	
	if(p_temp != NULL)
	{	
		tcp_recved(pcb, p_temp->tot_len);//获取数据长度 tot_len：tcp数据块的长度
		if(rx_buf.numOfBuf < MAX_RX_BUF)
		{
			sprintf(rx_buf.buffer[rx_buf.numOfBuf],"");
			while(p_temp != NULL)	
			{
				if(p_temp->tot_len > 900)
				break;
				strncat(rx_buf.buffer[rx_buf.numOfBuf],p_temp->payload, p_temp->len);
				p_temp = p_temp->next;
			}
			rx_buf.numOfBuf++;	
		}
	}
	else
	{
		tcp_close(pcb); 											/* 作为TCP服务器不应主动关闭这个连接？ */
	}
	/* 释放该TCP段 */
	pbuf_free(p); 	
	err = ERR_OK;
	return err;
}
/***********************************************************************
函数名称：TCP_Client_Init(u16_t local_port,u16_t remote_port,unsigned char a,unsigned char b,unsigned char c,unsigned char d)
功    能：tcp客户端初始化
输入参数：local_port本地端口号；remote_port：目标端口号；a,b,c,d：服务器ip
输出参数：
编写时间：2013.4.25
编 写 人：
注    意：
***********************************************************************/
void TCP_Client_Init(u16_t local_port,u16_t remote_port,unsigned char a,unsigned char b,unsigned char c,unsigned char d)
{

	struct ip_addr ipaddr;
	err_t err;
	IP4_ADDR(&ipaddr,a,b,c,d);           //服务器IP地址
	tcp_client_pcb = tcp_new(); /* 建立通信的TCP控制块(Clipcb) */
	if (!tcp_client_pcb)
	{
		return ;
	}		
	err = tcp_bind(tcp_client_pcb,IP_ADDR_ANY,local_port); /* 绑定本地IP地址和端口号 ，本地ip地址在LwIP_Init()中已经初始化*/
	if(err != ERR_OK)
	{
		return ;
	}    
	tcp_connect(tcp_client_pcb,&ipaddr,remote_port,TCP_Connected);//注册回调函数
	tcp_recv(tcp_client_pcb,TCP_Client_Recv); 				/* 设置tcp接收回调函数 */
}


