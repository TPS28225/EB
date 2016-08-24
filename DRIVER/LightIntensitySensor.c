#include  "main.h"
#include	"I2C.h"
//*********************************************************
//
//��������BH1750�ڲ�����
//
//*********************************************************
u8 LightIntensitySensor_measure()
{   	
	u16 dis_data;
	u8 LightIntensitySensor_Tempvalue[2];
	
	I2C_Start();                          //��ʼ�ź�
	I2C_SendByte(SLAVEADDRESS+1);         //�����豸��ַ+���ź�
	if(I2C_WaitAck()==FALSE)
	{
		I2C_Stop();                          //ֹͣ�ź� 
		INPUTDEVICE.LightIntensity=0;	
		return FALSE;
	}
	LightIntensitySensor_Tempvalue[0] = I2C_ReadByte();        
	I2C_Ack();                  //��ӦACK
	LightIntensitySensor_Tempvalue[1] = I2C_ReadByte();  
	I2C_NoAck();                //���һ��������Ҫ��NOACK
	I2C_Stop();                          //ֹͣ�ź� 
	
	dis_data=LightIntensitySensor_Tempvalue[0];
	dis_data=(dis_data<<8)+LightIntensitySensor_Tempvalue[1];//�ϳ�����     
	INPUTDEVICE.LightIntensity=dis_data/1.2;	
	
	return TRUE;
}


//��ʼ��BH1750��������Ҫ��ο�pdf�����޸�****
void LightIntensitySensor_Init()
{
	I2C_INIT();		
	I2C_Single_Write(SLAVEADDRESS,0x01);	
	I2C_Single_Write(SLAVEADDRESS,0x01);		// power on
	I2C_Single_Write(SLAVEADDRESS,0x10);	 	// H- resolution mode
}

      



