/***********************************************************************
�ļ����ƣ�UDP_CLIENT.C
��    �ܣ����UDP�������շ�
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
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
�������ƣ�udp_server_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p,struct ip_addr *addr, u16_t port)
��    �ܣ�udp���ݽ��պͷ���
���������
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺����һ���ص���������һ��udp�ε����������ʱ�ᱻ����
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
		//udp_sendto(pcb,p_temp,&destAddr,port); /* ���յ��������ٷ��ͳ�ȥ */			
	pbuf_free(p); 						/* �ͷŸ�UDP�� */
}
/***********************************************************************
�������ƣ�void UDP_client_init(void)
��    �ܣ����udp�ͻ��˳�ʼ��
���������
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/
void UDP_client_init(void)
{
	udp_p = pbuf_alloc(PBUF_RAW,MAX_TXRX_BUF_SIZE,PBUF_RAM);
	My_IP4_ADDR(&ipaddr,UDP_UDP_REMOTE_IP);				//Զ��IP
	udp_pcb = udp_new();
	udp_bind(udp_pcb,IP_ADDR_ANY,UDP_CLIENT_PORT); 	/* �󶨱���IP��ַ */
	udp_connect(udp_pcb,&ipaddr,UDP_REMOTE_PORT); 		/* ����Զ������ */		
	udp_recv(udp_pcb,udp_server_recv,NULL); 
}
/***********************************************************************
�������ƣ�My_IP4_ADDR(void)
��    �ܣ�IP��ַ��װ��
���������
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/
void My_IP4_ADDR(struct ip_addr *ipaddr,unsigned char a,unsigned char b,unsigned char c,unsigned char d)
{
	ipaddr->addr = htonl(((u32_t)((a) & 0xff) << 24) | \
                               ((u32_t)((b) & 0xff) << 16) | \
                               ((u32_t)((c) & 0xff) << 8) | \
                                (u32_t)((d) & 0xff));
}
/***********************************************************************
�������ƣ�void UDP_client_init(void)
��    �ܣ����udp�ͻ��˳�ʼ��
���������
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/
void UDP_Send_Data(struct udp_pcb *pcb,struct pbuf *p)
{
	udp_send(pcb,p);
	UDP_Delay(0XFFFFF);//��ʱ�����ܷ���̫��	
}

/***********************************************************************
�������ƣ�Delay(unsigned long ulVal)
��    �ܣ�����ѭ������һ������ʱ
���������
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/
static void UDP_Delay(unsigned long ulVal) /* ����ѭ������һ������ʱ */
{
	while ( --ulVal != 0 );
}