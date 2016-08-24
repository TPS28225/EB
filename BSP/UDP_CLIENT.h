/***********************************************************************
�ļ����ƣ�UDP_CLIENT.H
��    �ܣ����UDP�������շ�
��дʱ�䣺2013.4.25
�� д �ˣ���
ע    �⣺
***********************************************************************/
#ifndef _UDP_CLIENT_H_
#define _UDP_CLIENT_H_


/***************������ip��MAC����*************************/
#define BOARD_IP  			 	192,168,87,252   		//������ip 
#define BOARD_NETMASK   	 	255,255,255,0   		//��������������
#define BOARD_WG		   	 	 192,168,87,1   			//������������
#define BOARD_MAC_ADDR      	0,0,0,0,0,1				//������MAC��ַ

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

