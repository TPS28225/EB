#include "cJSON.h"
#include "parserJSON.h"
#include "devicemanager.h"
#include "main.h"
#include "string.h"


u16 BT_RX_Row_Counter = 0;
u16 ZB_TX_Row_Counter = 0;

char * makeJson()
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
	cJSON_AddStringToObject(pJsonRoot, "devId", uniqueID);
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
	cJSON_AddNumberToObject(pSubJson,"key1",INPUTDEVICE.KEY[0]);
	cJSON_AddNumberToObject(pSubJson,"key2",INPUTDEVICE.KEY[1]);
	cJSON_AddNumberToObject(pSubJson,"key3",INPUTDEVICE.KEY[2]);
	cJSON_AddNumberToObject(pSubJson,"key4",INPUTDEVICE.KEY[3]);
	cJSON_AddNumberToObject(pSubJson,"led1",OUTPUTDEVICE.LED[0]);
	cJSON_AddNumberToObject(pSubJson,"led2",OUTPUTDEVICE.LED[1]);
	cJSON_AddNumberToObject(pSubJson,"led3",OUTPUTDEVICE.LED[2]);
	cJSON_AddNumberToObject(pSubJson,"led4",OUTPUTDEVICE.LED[3]);
	cJSON_AddNumberToObject(pSubJson,"led5",OUTPUTDEVICE.LED[4]);
	cJSON_AddNumberToObject(pSubJson,"led6",OUTPUTDEVICE.LED[5]);
	cJSON_AddNumberToObject(pSubJson,"led7",OUTPUTDEVICE.LED[6]);
	cJSON_AddNumberToObject(pSubJson,"led8",OUTPUTDEVICE.LED[7]);
	cJSON_AddNumberToObject(pSubJson, "beep",OUTPUTDEVICE.Beep);
	cJSON_AddNumberToObject(pSubJson, "dcmotor",OUTPUTDEVICE.Motor);
	cJSON_AddItemToObject(pSubJson, "ir", PThdSubJson = cJSON_CreateObject());
	cJSON_AddNumberToObject(PThdSubJson,"state",INPUTDEVICE.IR_State);
	if(INPUTDEVICE.IR_State == 5)
	{
		cJSON_AddStringToObject(PThdSubJson,"code",INPUTDEVICE.IR_Code);
		IR_LearnEnable(0);
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
	pSub = cJSON_GetObjectItem(pJson, "devId");
	if(pSub != NULL)
	{
		if(!strcmp(uniqueID,pSub->valuestring))
		{
			pSub = cJSON_GetObjectItem(pJson, "type");
			if(!strcmp("cmd",pSub->valuestring))
			{
				pSub = cJSON_GetObjectItem(pJson, "data");
				if(pSub != NULL)
				{
					pSubSub = cJSON_GetObjectItem(pSub, "led1");
					if(pSubSub != NULL)
					{
						OUTPUTDEVICE.LED[0] = pSubSub->valueint;
					}
					pSubSub = cJSON_GetObjectItem(pSub, "led2");
					if(pSubSub != NULL)
					{
						OUTPUTDEVICE.LED[1] = pSubSub->valueint;
					}		
					pSubSub = cJSON_GetObjectItem(pSub, "led3");
					if(pSubSub != NULL)
					{
						OUTPUTDEVICE.LED[2] = pSubSub->valueint;
					}	
					pSubSub = cJSON_GetObjectItem(pSub, "led4");
					if(pSubSub != NULL)
					{
						OUTPUTDEVICE.LED[3] = pSubSub->valueint;
					}	
					pSubSub = cJSON_GetObjectItem(pSub, "led5");
					if(pSubSub != NULL)
					{
						OUTPUTDEVICE.LED[4] = pSubSub->valueint;
					}	
					pSubSub = cJSON_GetObjectItem(pSub, "led6");
					if(pSubSub != NULL)
					{
						OUTPUTDEVICE.LED[5] = pSubSub->valueint;
					}	
					pSubSub = cJSON_GetObjectItem(pSub, "led7");
					if(pSubSub != NULL)
					{
						OUTPUTDEVICE.LED[6] = pSubSub->valueint;
					}	
					pSubSub = cJSON_GetObjectItem(pSub, "led8");
					if(pSubSub != NULL)
					{
						OUTPUTDEVICE.LED[7] = pSubSub->valueint;
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


