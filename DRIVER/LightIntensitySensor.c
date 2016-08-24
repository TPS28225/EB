#include  "main.h"
#include	"I2C.h"
//*********************************************************
//
//连续读出BH1750内部数据
//
//*********************************************************
u8 LightIntensitySensor_measure()
{   	
	u16 dis_data;
	u8 LightIntensitySensor_Tempvalue[2];
	
	I2C_Start();                          //起始信号
	I2C_SendByte(SLAVEADDRESS+1);         //发送设备地址+读信号
	if(I2C_WaitAck()==FALSE)
	{
		I2C_Stop();                          //停止信号 
		INPUTDEVICE.LightIntensity=0;	
		return FALSE;
	}
	LightIntensitySensor_Tempvalue[0] = I2C_ReadByte();        
	I2C_Ack();                  //回应ACK
	LightIntensitySensor_Tempvalue[1] = I2C_ReadByte();  
	I2C_NoAck();                //最后一个数据需要回NOACK
	I2C_Stop();                          //停止信号 
	
	dis_data=LightIntensitySensor_Tempvalue[0];
	dis_data=(dis_data<<8)+LightIntensitySensor_Tempvalue[1];//合成数据     
	INPUTDEVICE.LightIntensity=dis_data/1.2;	
	
	return TRUE;
}


//初始化BH1750，根据需要请参考pdf进行修改****
void LightIntensitySensor_Init()
{
	I2C_INIT();		
	I2C_Single_Write(SLAVEADDRESS,0x01);	
	I2C_Single_Write(SLAVEADDRESS,0x01);		// power on
	I2C_Single_Write(SLAVEADDRESS,0x10);	 	// H- resolution mode
}

      



