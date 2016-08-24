#ifndef _DEVICEMANAGER_H
#define _DEVICEMANAGER_H

#include "main.h"

#define ZIGBEE_RX_ARRY_NUM			8
#define KEY_NUMBER							4
#define ZIGBEE_INPUT_ARRY_NUM		50
#define MAG_DOOR_CONTACT_NUM 		4


#define LED_NUM 								8
#define ZIGBEE_TX_ARRY_NUM			4
#define TX_RX_BUFFER_SIZE				50
#define OLED_OUTPUT_ARRY_NUM		50
#define IRCODE_ARRY_NUM			    300
#define BLUETOOTH_TX_ARRY_NUM   8 
typedef struct {
	int RFID_CARDID;
	u16 Data;
	u8 	Card_State;//判断输出卡信息的卡状态，决定是否写入新的余额
	u8  entrance_guard_pass;	
	u8  ACK[2];
}CARD_Property;
typedef union
{
	CARD_Property rfid_card_Info;
	u8	CARD_Info_Str[16];
}CARD_Info;	

typedef struct {
	float 			Distance; 			//√									  //0-2000CM    //计算出的距离 
	u8 					temperature;		//√							    	//0-50Degree
	u8 					humidity;				//√	      						//20-95%
	u8 					exist_people;		//√										//TRUE/FALSE
	u8 					sound_exceed_threshold;	 //√	  	    //TRUE/FALSE
	int	 				LightIntensity;	  			//√					    //0-65535
	u32					RFID_CARDID;           //√
	CARD_Info		RFID_CARD;
	char				Zigbee_RX[ZIGBEE_RX_ARRY_NUM][TX_RX_BUFFER_SIZE];//√			
	u8					KEY[KEY_NUMBER];       //√	
	u8					Magnetic_Door_Contact; //√	
	char        IR_State;
	char        IR_Code[IRCODE_ARRY_NUM];       
}INPUTDEVICE_MEASURE;

typedef struct {
	char 				LED[LED_NUM];       //√															
	char 				Beep;								//√											
	char 				Motor;							//√																				
	char 				Zigbee_TX[ZIGBEE_TX_ARRY_NUM][TX_RX_BUFFER_SIZE];	//√							
	char	 			OLED[OLED_OUTPUT_ARRY_NUM];											
	char        Bluetooth[BLUETOOTH_TX_ARRY_NUM][TX_RX_BUFFER_SIZE];//√			
	char        IR_State;           //√
	CARD_Info		RFID_CARD;
	char        IR_Code[IRCODE_ARRY_NUM];    //√
	char				Cureent_Exam_Num;
}OUTPUTDEVICE_CONTROL;
#endif






















