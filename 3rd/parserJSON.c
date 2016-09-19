#include "cJSON.h"
#include "parserJSON.h"
#include "devicemanager.h"
#include "main.h"
#include "string.h"
#define 	DEVICEID "NQAyAAtRNTMzODQwNQAyAAtRNTMzODQw" //uniqueID

u16 BT_RX_Row_Counter = 0;
u16 ZB_TX_Row_Counter = 0;

extern tx_buf_t  tx_buf;
extern rx_buf_t  rx_buf;

char * makeJson(Jason_Funtype function)
{
	cJSON * pJsonRoot;
	cJSON * pSubJson;
	cJSON * PThdSubJson;
	char * p=0;
	u8 err;
	
	pJsonRoot = cJSON_CreateObject();
	if(NULL == pJsonRoot)
	{
		return NULL;
	}
	//选择发送的功能
	switch(function){
		//发送传感器数据
		case RPT:
			cJSON_AddStringToObject(pJsonRoot, "devId", DEVICEID);
			cJSON_AddStringToObject(pJsonRoot, "type", "rpt");
			cJSON_AddItemToObject(pJsonRoot, "data", pSubJson = cJSON_CreateObject());
			cJSON_AddNumberToObject(pSubJson, "lux", INPUTDEVICE.LightIntensity);
			cJSON_AddNumberToObject(pSubJson,"soundSensor",INPUTDEVICE.sound_exceed_threshold);
			cJSON_AddNumberToObject(pSubJson,"peopleSensor",INPUTDEVICE.exist_people);
			cJSON_AddNumberToObject(pSubJson,"temp",INPUTDEVICE.temperature);
			cJSON_AddNumberToObject(pSubJson,"humi",INPUTDEVICE.humidity);
			
			cJSON_AddNumberToObject(pSubJson, "door",INPUTDEVICE.Magnetic_Door_Contact);
			
			cJSON_AddNumberToObject(pSubJson,"distance",INPUTDEVICE.Distance);
			cJSON_AddNumberToObject(pSubJson,"rfid",INPUTDEVICE.RFID_CARDID);
			if((((OS_Q*)(q_msg_zigbee_rx->OSEventPtr))->OSQEntries)!=0)
			{
				cJSON_AddStringToObject(pSubJson,"zigbee",OSQPend(q_msg_zigbee_rx,0,&err));
			}
			cJSON_AddItemToObject(pSubJson, "key", PThdSubJson = cJSON_CreateObject());
			cJSON_AddNumberToObject(PThdSubJson,"key1",INPUTDEVICE.KEY[0]);
			cJSON_AddNumberToObject(PThdSubJson,"key2",INPUTDEVICE.KEY[1]);
			cJSON_AddNumberToObject(PThdSubJson,"key3",INPUTDEVICE.KEY[2]);
			cJSON_AddNumberToObject(PThdSubJson,"key4",INPUTDEVICE.KEY[3]);
			
			cJSON_AddItemToObject(pSubJson, "led", PThdSubJson = cJSON_CreateObject());	
			cJSON_AddNumberToObject(PThdSubJson,"led1",OUTPUTDEVICE.LED[0]);	
			cJSON_AddNumberToObject(PThdSubJson,"led2",OUTPUTDEVICE.LED[1]);
			cJSON_AddNumberToObject(PThdSubJson,"led3",OUTPUTDEVICE.LED[2]);
			cJSON_AddNumberToObject(PThdSubJson,"led4",OUTPUTDEVICE.LED[3]);
			cJSON_AddNumberToObject(PThdSubJson,"led5",OUTPUTDEVICE.LED[4]);
			cJSON_AddNumberToObject(PThdSubJson,"led6",OUTPUTDEVICE.LED[5]);
			cJSON_AddNumberToObject(PThdSubJson,"led7",OUTPUTDEVICE.LED[6]);
			cJSON_AddNumberToObject(PThdSubJson,"led8",OUTPUTDEVICE.LED[7]);
			
			cJSON_AddItemToObject(pSubJson, "ir", PThdSubJson = cJSON_CreateObject());
			cJSON_AddNumberToObject(PThdSubJson,"state",INPUTDEVICE.IR_State);
			if(INPUTDEVICE.IR_State == 5)
			{
				cJSON_AddStringToObject(PThdSubJson,"code",INPUTDEVICE.IR_Code);
				IR_LearnEnable(0);
			}	
			cJSON_AddNumberToObject(pSubJson, "beep",OUTPUTDEVICE.Beep);
			cJSON_AddNumberToObject(pSubJson, "dcmotor",OUTPUTDEVICE.Motor);
			break;
		//客户端发送注册包
		case REG:
			cJSON_AddStringToObject(pJsonRoot, "devId", DEVICEID);
			cJSON_AddStringToObject(pJsonRoot, "devName","zongheng_kongkai");
			cJSON_AddStringToObject(pJsonRoot, "type", "reg");
			break;
		//客户端发送连接请求
		case LOGIN:
			cJSON_AddStringToObject(pJsonRoot, "devId", DEVICEID);
			cJSON_AddStringToObject(pJsonRoot, "type","login");
			cJSON_AddStringToObject(pJsonRoot, "client_name", DEVICEID);
			cJSON_AddStringToObject(pJsonRoot, "group_id", "1");
			break;
		//客户端回应心跳 pong
		case PONG:
			cJSON_AddStringToObject(pJsonRoot, "type","pong");
			break;
	}			
	p = cJSON_PrintUnformatted(pJsonRoot);
	cJSON_Delete(pJsonRoot);
			
	return p;
}

void parserJson(char * pMsg)
{
	cJSON * pJson;
	cJSON * pSub;
	cJSON * pSubSub;
	cJSON * pSubSubSub;
	if(pMsg == NULL)
	{
		return;
	}
	pJson = cJSON_Parse(pMsg);
	if(pJson == NULL)
	{
		return;
	}
	
	//接收心跳
	pSub = cJSON_GetObjectItem(pJson, "type");
	if(!strcmp("ping",pSub->valuestring))
	{
			pong_flag++;
	}
	
	//接收数据
	pSub = cJSON_GetObjectItem(pJson, "devId");
	if(pSub != NULL)
	{	
		if(!strcmp(DEVICEID,pSub->valuestring))
		{
			pSub = cJSON_GetObjectItem(pJson, "type");
			if(!strcmp("cmd",pSub->valuestring))
			{
				pSub = cJSON_GetObjectItem(pJson, "data");
				if(pSub != NULL)
				{
					
					pSubSub = cJSON_GetObjectItem(pSub, "test");
					if(pSubSub != NULL)
					{
						OUTPUTDEVICE.Cureent_Exam_Num = pSubSub->valueint;
					}					
					pSubSub = cJSON_GetObjectItem(pSub, "led");
					if(pSubSub != NULL)
					{
						pSubSubSub = cJSON_GetObjectItem(pSubSub, "led1");
						if(pSubSubSub != NULL)
						{
							OUTPUTDEVICE.LED[0] = pSubSubSub->valueint;
						}
						pSubSubSub = cJSON_GetObjectItem(pSubSub, "led2");
						if(pSubSubSub != NULL)
						{
							OUTPUTDEVICE.LED[1] = pSubSubSub->valueint;
						}		
						pSubSubSub = cJSON_GetObjectItem(pSubSub, "led3");
						if(pSubSubSub != NULL)
						{
							OUTPUTDEVICE.LED[2] = pSubSubSub->valueint;
						}	
						pSubSubSub = cJSON_GetObjectItem(pSubSub, "led4");
						if(pSubSubSub != NULL)
						{
							OUTPUTDEVICE.LED[3] = pSubSubSub->valueint;
						}	
						pSubSubSub = cJSON_GetObjectItem(pSubSub, "led5");
						if(pSubSubSub != NULL)
						{
							OUTPUTDEVICE.LED[4] = pSubSubSub->valueint;
						}	
						pSubSubSub = cJSON_GetObjectItem(pSubSub, "led6");
						if(pSubSubSub != NULL)
						{
							OUTPUTDEVICE.LED[5] = pSubSubSub->valueint;
						}	
						pSubSubSub = cJSON_GetObjectItem(pSubSub, "led7");
						if(pSubSubSub != NULL)
						{
							OUTPUTDEVICE.LED[6] = pSubSubSub->valueint;
						}	
						pSubSubSub = cJSON_GetObjectItem(pSubSub, "led8");
						if(pSubSubSub != NULL)
						{
							OUTPUTDEVICE.LED[7] = pSubSubSub->valueint;
						}	
					}						

					pSubSub = cJSON_GetObjectItem(pSub, "beep");
					if(pSubSub != NULL)
					{
						OUTPUTDEVICE.Beep = pSubSub->valueint;
					}	
					pSubSub = cJSON_GetObjectItem(pSub, "dcmotor");
					if(pSubSub != NULL)
					{
						OUTPUTDEVICE.Motor = pSubSub->valueint;						
					}
					
					pSubSub = cJSON_GetObjectItem(pSub, "ir");
					if(pSubSub != NULL)
					{
						pSubSubSub = cJSON_GetObjectItem(pSubSub, "state");
						if(pSubSubSub != NULL)
						{
							OUTPUTDEVICE.IR_State = pSubSubSub->valueint;
						}		
						pSubSubSub = cJSON_GetObjectItem(pSubSub, "code");
						if(pSubSubSub != NULL)
						{
							strncpy(OUTPUTDEVICE.IR_Code,pSubSubSub->valuestring,IRCODE_ARRY_NUM);
						}								
					}

//							"rfid":{
//			"id":"FF03DC6B",
//			"data":10,   //(?????)
//			"enable":0,  //????:0???/1???   ?????
//			"ack":" "    //??		 
//		}
					pSubSub = cJSON_GetObjectItem(pSub, "rfid");
					if(pSubSub != NULL)
					{
						pSubSubSub = cJSON_GetObjectItem(pSubSub, "operation");
						if(pSubSubSub != NULL)
						{
							OUTPUTDEVICE.RFID_CARD.rfid_card_Info.Card_Operation = pSubSubSub->valueint;
						}
						pSubSubSub = cJSON_GetObjectItem(pSubSub, "charge_enable");
						if(pSubSubSub != NULL)
						{
							OUTPUTDEVICE.RFID_CARD.rfid_card_Info.Card_Charge_Enable = pSubSubSub->valueint;
						}	
						pSubSubSub = cJSON_GetObjectItem(pSubSub, "data");
						if(pSubSubSub != NULL)
						{
							OUTPUTDEVICE.RFID_CARD.rfid_card_Info.Data = pSubSubSub->valueint;
						}
						pSubSubSub = cJSON_GetObjectItem(pSubSub, "pass_enable");
						if(pSubSubSub != NULL)
						{
							OUTPUTDEVICE.RFID_CARD.rfid_card_Info.entrance_guard_pass = pSubSubSub->valueint;
						}
						
					}
					pSubSub = cJSON_GetObjectItem(pSub, "zigbee");
					if(pSubSub != NULL)
					{		
						if((((OS_Q*)(q_msg_zigbee_tx->OSEventPtr))->OSQEntries)<ZIGBEE_TX_ARRY_NUM)
						{
							strncpy(OUTPUTDEVICE.Zigbee_TX[ZB_TX_Row_Counter],pSubSub->valuestring,TX_RX_BUFFER_SIZE);
							OSQPost(q_msg_zigbee_tx,(void*)(OUTPUTDEVICE.Zigbee_TX[ZB_TX_Row_Counter]));
							ZB_TX_Row_Counter++;
							if(ZB_TX_Row_Counter>=ZIGBEE_TX_ARRY_NUM) ZB_TX_Row_Counter = 0;								
						}						
					}		
					pSubSub = cJSON_GetObjectItem(pSub, "oled");
					if(pSubSub != NULL)
					{
						strncpy(OUTPUTDEVICE.OLED,pSubSub->valuestring,50);
					}		
					pSubSub = cJSON_GetObjectItem(pSub, "bluetooth");
					if(pSubSub != NULL)
					{
						if((((OS_Q*)(q_msg_bluetooth_tx->OSEventPtr))->OSQEntries)<BLUETOOTH_TX_ARRY_NUM)
						{
							strncpy(OUTPUTDEVICE.Bluetooth[BT_RX_Row_Counter],pSubSub->valuestring,TX_RX_BUFFER_SIZE);
							OSQPost(q_msg_bluetooth_tx,(void*)(OUTPUTDEVICE.Bluetooth[BT_RX_Row_Counter]));
							BT_RX_Row_Counter++;
							if(BT_RX_Row_Counter>=BLUETOOTH_TX_ARRY_NUM) BT_RX_Row_Counter = 0;								
						}						
					}						
				}
			}

		}
	}
	cJSON_Delete(pJson);
}

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

