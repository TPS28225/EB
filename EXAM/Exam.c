#include "bmpdisplay.h"
#include "GUI.h"
#include "malloc.h"
#include "ff.h"
#include "devicemanager.h"
#include "exammanager.h"
#include "stdio.h"

extern GUI_CONST_STORAGE GUI_FONT GUI_Fontyouyuan20;
extern GUI_CONST_STORAGE GUI_FONT GUI_Fontyouyuan16;
extern INPUTDEVICE_MEASURE INPUTDEVICE;
extern OUTPUTDEVICE_CONTROL OUTPUTDEVICE;

static const char * _apStrings_youren[] = {"\xe6\x9c\x89\xe4\xba\xba"};//����(UTF8��ʽ��)
static const char * _apStrings_wuren[] = {"\xe6\x97\xa0\xe4\xba\xba"};  //����
static const char * _apStrings_jiashi[] = {"\xe5\x8a\xa0\xe6\xb9\xbf"};//��ʪ
static const char * _apStrings_chushi[] = {"\xe9\x99\xa4\xe6\xb9\xbf"};//��ʪ
static const char * _apStrings_zhileng[] = {"\xe5\x88\xb6\xe5\x86\xb7"};//����
static const char * _apStrings_zhire[] = {"\xe5\x88\xb6\xe7\x83\xad"};	//����
static const char * _apStrings_shushi[] = {"\xe8\x88\x92\xe9\x80\x82"};	//����

void bmpdisplay_exam1(void)
{
	int Temp_Counter=0;
	int Delete_Counter=0;
	
	int Light_Beep_On_Flag=3;
	int LED_Flag=3;

	GUI_MEMDEV_Handle hMem_Main;

	GUI_MEMDEV_Handle hMem_Sub_beep_off_350_125_84x75;
	GUI_MEMDEV_Handle hMem_Sub_beep_on_350_125_84x75;
	GUI_MEMDEV_Handle hMem_Sub_light_on_360_50_66x76;
	GUI_MEMDEV_Handle hMem_Sub_light_off_360_50_66x76;
	GUI_MEMDEV_Handle hMem_Sub_word_background_175_105_105x40;
	GUI_MEMDEV_Handle hMem_Sub_fan_345_205_94x90[8];	
//
// Create the memory device
//
	hMem_Main = GUI_MEMDEV_Create(0, 0, 480, 320);

	
	GUI_SetBkColor(GUI_BLACK);//����
	GUI_SetColor(GUI_RED);
	GUI_SetFont(&GUI_Fontyouyuan20);
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_Clear();

	GUI_MEMDEV_Select(hMem_Main);//ѡ�д洢�豸		
	dispbmpex("0:/picture/face.bmp",0,0,	0);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_CopyToLCDAt(hMem_Main, 0, 0);
//	GUI_Delay(5000);	
	
	GUI_MEMDEV_Select(hMem_Main);//ѡ�д洢�豸		
	dispbmpex("0:/picture/exam1/exam_background.bmp",0,0,	0);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_CopyToLCDAt(hMem_Main, 0, 0);	
	GUI_MEMDEV_Delete(hMem_Main);	
//	GUI_Delay(1000);
//����ͼ��
	hMem_Sub_beep_off_350_125_84x75=Create_MEMDEV_Icon("0:/picture/exam1/beep_off_350_125_84x75.bmp",350,125);
	hMem_Sub_beep_on_350_125_84x75=Create_MEMDEV_Icon("0:/picture/exam1/beep_on_350_125_84x75.bmp",350,125);	
	
	hMem_Sub_light_off_360_50_66x76=Create_MEMDEV_Icon("0:/picture/exam1/light_off_360_50_66x76.bmp",360,50);
	hMem_Sub_light_on_360_50_66x76=Create_MEMDEV_Icon("0:/picture/exam1/light_on_360_50_66x76.bmp",360,50);	

	hMem_Sub_word_background_175_105_105x40=Create_MEMDEV_Icon("0:/picture/exam1/word_background_175_105_105x40.bmp",175,105);	
	
	hMem_Sub_fan_345_205_94x90[0]=Create_MEMDEV_Icon("0:/picture/exam1/fan1_345_205_94x90.bmp",345,205);
	hMem_Sub_fan_345_205_94x90[1]=Create_MEMDEV_Icon("0:/picture/exam1/fan2_345_205_94x90.bmp",345,205);
	hMem_Sub_fan_345_205_94x90[2]=Create_MEMDEV_Icon("0:/picture/exam1/fan3_345_205_94x90.bmp",345,205);
	hMem_Sub_fan_345_205_94x90[3]=Create_MEMDEV_Icon("0:/picture/exam1/fan4_345_205_94x90.bmp",345,205);
	hMem_Sub_fan_345_205_94x90[4]=Create_MEMDEV_Icon("0:/picture/exam1/fan5_345_205_94x90.bmp",345,205);
	hMem_Sub_fan_345_205_94x90[5]=Create_MEMDEV_Icon("0:/picture/exam1/fan6_345_205_94x90.bmp",345,205);
	hMem_Sub_fan_345_205_94x90[6]=Create_MEMDEV_Icon("0:/picture/exam1/fan7_345_205_94x90.bmp",345,205);
	hMem_Sub_fan_345_205_94x90[7]=Create_MEMDEV_Icon("0:/picture/exam1/fan8_345_205_94x90.bmp",345,205);	

	GUI_SetColor(0x00d1fef0);
	GUI_SetFont(&GUI_Fontyouyuan20);
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_UC_SetEncodeUTF8();
	
	while(1)	{	
		if(1==INPUTDEVICE.exist_people ||
			 1==INPUTDEVICE.sound_exceed_threshold ||
			 1==INPUTDEVICE.Magnetic_Door_Contact){
				 if(1!=Light_Beep_On_Flag){
						GUI_MEMDEV_CopyToLCDAt(hMem_Sub_beep_on_350_125_84x75, 350, 125);	
						 
						GUI_MEMDEV_CopyToLCDAt(hMem_Sub_word_background_175_105_105x40 ,175,105);				 
						GUI_DispStringAt(_apStrings_youren[0], 175, 112);	
						Light_Beep_On_Flag=1;			 
					}	
		}				 
		else{
			if(0!=Light_Beep_On_Flag){
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_beep_off_350_125_84x75, 350, 125);	
			
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_word_background_175_105_105x40 ,175,105);
				GUI_DispStringAt(_apStrings_wuren[0], 175, 112);
				Light_Beep_On_Flag=0;				
			}				
		}
		
		if(1==OUTPUTDEVICE.LED[0]){
			if(1!=LED_Flag){
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_on_360_50_66x76 ,360,50);
				LED_Flag=1;
			}

		}
		else {
			if(0!=LED_Flag){
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_off_360_50_66x76 ,360,50);
				LED_Flag=0;
			}
		}
		
		if(INPUTDEVICE.temperature >= 24 ){
			GUI_MEMDEV_CopyToLCDAt(hMem_Sub_fan_345_205_94x90[Temp_Counter],345,205);
			Temp_Counter++;
			if(7==Temp_Counter)	Temp_Counter=0;				
		}
		
		if(1!=OUTPUTDEVICE.Cureent_Exam_Num){
			Delete_MEMDEV_Icon(hMem_Sub_beep_off_350_125_84x75);
			Delete_MEMDEV_Icon(hMem_Sub_beep_on_350_125_84x75);
			
			Delete_MEMDEV_Icon(hMem_Sub_light_off_360_50_66x76);
			Delete_MEMDEV_Icon(hMem_Sub_light_on_360_50_66x76);
			
			Delete_MEMDEV_Icon(hMem_Sub_word_background_175_105_105x40);

			for(Delete_Counter=0;Delete_Counter<=7;Delete_Counter++){
				Delete_MEMDEV_Icon(hMem_Sub_fan_345_205_94x90[Delete_Counter]);
			}
			break;
		}
		GUI_Delay(10);
		
	}
}

void bmpdisplay_exam2(void)
{
	int Temp_Counter=0;
	int Delete_Counter=0;
	
	int Light_On_Flag[4]={3,3,3};//�Ȳ���0��Ҳ����1����
	int sound_exceed_threshold_Flag=3;
//	int Power_On=3;	
	int Power_On_Flag=3;
	int Light_Intensity_Record=0;
	char Light_Intensity[10];

	GUI_MEMDEV_Handle hMem_Main;

	GUI_MEMDEV_Handle hMem_Sub_power_on_274_274_74x37;
	GUI_MEMDEV_Handle hMem_Sub_power_off_274_274_74x37;

	GUI_MEMDEV_Handle hMem_Sub_light_on_116_37x16[4];
	GUI_MEMDEV_Handle hMem_Sub_light_off_116_37x16[4];

	GUI_MEMDEV_Handle hMem_Sub_word_background_1_125_120_82x40;//word_background_1_125_120_120x40
	GUI_MEMDEV_Handle hMem_Sub_word_background_2_150_215_70x40;//word_background_2_150_215_70x40


	
//
// Create the memory device
//
	hMem_Main = GUI_MEMDEV_Create(0, 0, 480, 320);

	
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(0x00d1fef0);
	GUI_SetFont(&GUI_Font32_ASCII);
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_UC_SetEncodeUTF8();
	GUI_Clear();

	GUI_MEMDEV_Select(hMem_Main);//ѡ�д洢�豸		
	dispbmpex("0:/picture/face.bmp",0,0,	0);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_CopyToLCDAt(hMem_Main, 0, 0);
//	GUI_Delay(5000);	
	
	GUI_MEMDEV_Select(hMem_Main);//ѡ�д洢�豸		
	dispbmpex("0:/picture/exam2/exam2_background.bmp",0,0,	0);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_CopyToLCDAt(hMem_Main, 0, 0);	
	GUI_MEMDEV_Delete(hMem_Main);	

	sprintf(Light_Intensity,"%d",INPUTDEVICE.LightIntensity);
	GUI_DispStringHCenterAt(Light_Intensity,166,120);
	GUI_DispStringAt("lx", 210, 120);	
	
//	GUI_Delay(1000);
//����ͼ��
	hMem_Sub_power_on_274_274_74x37=Create_MEMDEV_Icon("0:/picture/exam2/power_on_274_274_74x37.bmp",274,274);
	hMem_Sub_power_off_274_274_74x37=Create_MEMDEV_Icon("0:/picture/exam2/power_off_274_274_74x37.bmp",274,274);	
	
	hMem_Sub_word_background_1_125_120_82x40=Create_MEMDEV_Icon("0:/picture/exam2/word_background_1_125_120_82x40.bmp",125,120);	
	hMem_Sub_word_background_2_150_215_70x40=Create_MEMDEV_Icon("0:/picture/exam2/word_background_2_150_215_70x40.bmp",150,215);	
	
	hMem_Sub_light_on_116_37x16[0]=Create_MEMDEV_Icon("0:/picture/exam2/light_on_247_116_37x16.bmp",247,116);
	hMem_Sub_light_on_116_37x16[1]=Create_MEMDEV_Icon("0:/picture/exam2/light_on_303_116_37x16.bmp",303,116);
	hMem_Sub_light_on_116_37x16[2]=Create_MEMDEV_Icon("0:/picture/exam2/light_on_360_116_37x16.bmp",360,116);
	hMem_Sub_light_on_116_37x16[3]=Create_MEMDEV_Icon("0:/picture/exam2/light_on_417_116_37x16.bmp",417,116);
	
	hMem_Sub_light_off_116_37x16[0]=Create_MEMDEV_Icon("0:/picture/exam2/light_off_247_116_37x16.bmp",347,116);
	hMem_Sub_light_off_116_37x16[1]=Create_MEMDEV_Icon("0:/picture/exam2/light_off_303_116_37x16.bmp",303,116);
	hMem_Sub_light_off_116_37x16[2]=Create_MEMDEV_Icon("0:/picture/exam2/light_off_360_116_37x16.bmp",360,116);
	hMem_Sub_light_off_116_37x16[3]=Create_MEMDEV_Icon("0:/picture/exam2/light_off_417_116_37x16.bmp",417,116);	


	while(1){	
		for(Temp_Counter=0;Temp_Counter<4;Temp_Counter++){
			if((1==OUTPUTDEVICE.LED[Temp_Counter])&&(1!=Light_On_Flag[Temp_Counter])){
				if(0==Temp_Counter)GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_on_116_37x16[Temp_Counter], 247, 116);
				else GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_on_116_37x16[Temp_Counter], 248+57*Temp_Counter, 116);
				Light_On_Flag[Temp_Counter]=1;
			}
			else if((0==OUTPUTDEVICE.LED[Temp_Counter])&&(0!=Light_On_Flag[Temp_Counter])){
				if(0==Temp_Counter)GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_off_116_37x16[Temp_Counter], 247, 116);
				else GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_off_116_37x16[Temp_Counter], 248+57*Temp_Counter, 116);
				Light_On_Flag[Temp_Counter]=0;
			}
		}
		
		if(1==INPUTDEVICE.sound_exceed_threshold){
			 if(1!=sound_exceed_threshold_Flag){			 
				 GUI_MEMDEV_CopyToLCDAt(hMem_Sub_word_background_2_150_215_70x40 ,150,215);
				 GUI_SetFont(&GUI_Fontyouyuan20);
				 GUI_DispStringAt(_apStrings_youren[0], 150, 215);
				 GUI_SetFont(&GUI_Font32_ASCII);
				 sound_exceed_threshold_Flag=1;			 
			 }	
		}				 
		else{
			if(0!=sound_exceed_threshold_Flag){
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_word_background_2_150_215_70x40 ,150,215);
			  GUI_SetFont(&GUI_Fontyouyuan20);				
				GUI_DispStringAt(_apStrings_wuren[0], 150, 215);
				GUI_SetFont(&GUI_Font32_ASCII);
				sound_exceed_threshold_Flag=0;				
			}				
		}
		
		if(1==OUTPUTDEVICE.LED[7]){
			if(1!=Power_On_Flag){			 
			 GUI_MEMDEV_CopyToLCDAt(hMem_Sub_power_on_274_274_74x37 ,274,274);
			 Power_On_Flag=1;			 
			}	
		}				 
		else{
			if(0==OUTPUTDEVICE.LED[7]){
				if(0!=Power_On_Flag){	
					GUI_MEMDEV_CopyToLCDAt(hMem_Sub_power_off_274_274_74x37 ,274,274);
					Power_On_Flag=0;				
				}				
			}
		}
		if(Light_Intensity_Record!=INPUTDEVICE.LightIntensity){		
			GUI_MEMDEV_CopyToLCDAt(hMem_Sub_word_background_1_125_120_82x40 ,125,120);		
			sprintf(Light_Intensity,"%d",INPUTDEVICE.LightIntensity);
			GUI_DispStringHCenterAt(Light_Intensity,166,120);
			Light_Intensity_Record=INPUTDEVICE.LightIntensity;
		}	
		if(2!=OUTPUTDEVICE.Cureent_Exam_Num){
			Delete_MEMDEV_Icon(hMem_Sub_power_on_274_274_74x37);
			Delete_MEMDEV_Icon(hMem_Sub_power_off_274_274_74x37);
			
			Delete_MEMDEV_Icon(hMem_Sub_word_background_1_125_120_82x40);
			Delete_MEMDEV_Icon(hMem_Sub_word_background_2_150_215_70x40);
				
			for(Delete_Counter=0;Delete_Counter<=3;Delete_Counter++){
				Delete_MEMDEV_Icon(hMem_Sub_light_on_116_37x16[Delete_Counter]);
			}
			
			for(Delete_Counter=0;Delete_Counter<=3;Delete_Counter++){
				Delete_MEMDEV_Icon(hMem_Sub_light_off_116_37x16[Delete_Counter]);
			}
			break;
		}
		GUI_Delay(10);
	}
}



void bmpdisplay_exam3(void)
{
	int Temp_Counter=0;
	int Temp_flash_Counter=0;
	int Humidity_Counter=0;
	int Delete_Counter=0;
	
	int Temperature_Record=0;
	int Humidity_Record=0;
	
	char Temperature_str[5];
	char Humidity_str[5];
	
	int jiachushi_Flag=4;	
	int zhilengre_Flag=4;	
	
	GUI_MEMDEV_Handle hMem_Main;

	GUI_MEMDEV_Handle hMem_Sub_fan_324_205_73x72[5];	
	GUI_MEMDEV_Handle hMem_Sub_heat_324_205_73x72[3];
	GUI_MEMDEV_Handle hMem_Sub_temper_84_199_12x43[3];
	
	GUI_MEMDEV_Handle hMem_Sub_fog_365_50_115x110[9];			
	
	GUI_MEMDEV_Handle hMem_Sub_background_degree_165_225_52x29;		
	GUI_MEMDEV_Handle hMem_Sub_background_percent_163_112_57x34;
	GUI_MEMDEV_Handle hMem_Sub_background_jiachushi_340_167_46x19;	
	GUI_MEMDEV_Handle hMem_Sub_background_zhilengre_335_285_46x19;

	
//
// Create the memory device
//
	hMem_Main = GUI_MEMDEV_Create(0, 0, 480, 320);

	
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(0x00d1fef0);
	GUI_SetFont(&GUI_Font32_ASCII);
//	GUI_SetFont(&GUI_Fontyouyuan20);

	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_UC_SetEncodeUTF8();
	GUI_Clear();

	GUI_MEMDEV_Select(hMem_Main);//ѡ�д洢�豸		
	dispbmpex("0:/picture/face.bmp",0,0,	0);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_CopyToLCDAt(hMem_Main, 0, 0);
//	GUI_Delay(5000);	
	
	GUI_MEMDEV_Select(hMem_Main);//ѡ�д洢�豸		
	dispbmpex("0:/picture/exam3/exam3_background.bmp",0,0,	0);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_CopyToLCDAt(hMem_Main, 0, 0);	
	GUI_MEMDEV_Delete(hMem_Main);		
	
//�����洢�豸	
	hMem_Sub_fan_324_205_73x72[0]=Create_MEMDEV_Icon("0:/picture/exam3/fan1_324_205_73x72.bmp",324,205);
	hMem_Sub_fan_324_205_73x72[1]=Create_MEMDEV_Icon("0:/picture/exam3/fan2_324_205_73x72.bmp",324,205);	
	hMem_Sub_fan_324_205_73x72[2]=Create_MEMDEV_Icon("0:/picture/exam3/fan3_324_205_73x72.bmp",324,205);
	hMem_Sub_fan_324_205_73x72[3]=Create_MEMDEV_Icon("0:/picture/exam3/fan4_324_205_73x72.bmp",324,205);	
	hMem_Sub_fan_324_205_73x72[4]=Create_MEMDEV_Icon("0:/picture/exam3/fan5_324_205_73x72.bmp",324,205);

	hMem_Sub_heat_324_205_73x72[0]=Create_MEMDEV_Icon("0:/picture/exam3/heat1_324_205_73x72.bmp",324,205);
	hMem_Sub_heat_324_205_73x72[1]=Create_MEMDEV_Icon("0:/picture/exam3/heat2_324_205_73x72.bmp",324,205);	
	hMem_Sub_heat_324_205_73x72[2]=Create_MEMDEV_Icon("0:/picture/exam3/heat3_324_205_73x72.bmp",324,205);

	hMem_Sub_temper_84_199_12x43[0]=Create_MEMDEV_Icon("0:/picture/exam3/temper1_84_199_12x43.bmp",84,199);
	hMem_Sub_temper_84_199_12x43[1]=Create_MEMDEV_Icon("0:/picture/exam3/temper2_84_199_12x43.bmp",84,199);
	hMem_Sub_temper_84_199_12x43[2]=Create_MEMDEV_Icon("0:/picture/exam3/temper3_84_199_12x43.bmp",84,199);
	
	hMem_Sub_fog_365_50_115x110[0]=Create_MEMDEV_Icon("0:/picture/exam3/fog1_365_50_115x110.bmp",365,50);	
	hMem_Sub_fog_365_50_115x110[1]=Create_MEMDEV_Icon("0:/picture/exam3/fog2_365_50_115x110.bmp",365,50);	
	hMem_Sub_fog_365_50_115x110[2]=Create_MEMDEV_Icon("0:/picture/exam3/fog3_365_50_115x110.bmp",365,50);	
	hMem_Sub_fog_365_50_115x110[3]=Create_MEMDEV_Icon("0:/picture/exam3/fog4_365_50_115x110.bmp",365,50);	
	hMem_Sub_fog_365_50_115x110[4]=Create_MEMDEV_Icon("0:/picture/exam3/fog5_365_50_115x110.bmp",365,50);	
	hMem_Sub_fog_365_50_115x110[5]=Create_MEMDEV_Icon("0:/picture/exam3/fog6_365_50_115x110.bmp",365,50);	
	hMem_Sub_fog_365_50_115x110[6]=Create_MEMDEV_Icon("0:/picture/exam3/fog7_365_50_115x110.bmp",365,50);	
	hMem_Sub_fog_365_50_115x110[7]=Create_MEMDEV_Icon("0:/picture/exam3/fog8_365_50_115x110.bmp",365,50);
	hMem_Sub_fog_365_50_115x110[8]=Create_MEMDEV_Icon("0:/picture/exam3/fog9_365_50_115x110.bmp",365,50);	
	
	hMem_Sub_background_degree_165_225_52x29=Create_MEMDEV_Icon("0:/picture/exam3/background_degree_165_225_52x29.bmp",165,225);	
	hMem_Sub_background_percent_163_112_57x34=Create_MEMDEV_Icon("0:/picture/exam3/background_percent_163_112_57x34.bmp",163,112);
	hMem_Sub_background_jiachushi_340_167_46x19=Create_MEMDEV_Icon("0:/picture/exam3/background_jiachushi_340_167_46x19.bmp",340,167);
	hMem_Sub_background_zhilengre_335_285_46x19=Create_MEMDEV_Icon("0:/picture/exam3/background_zhilengre_335_285_46x19.bmp",335,285);
	while(1){
	//����	�Լ���ʾ����״̬������/����/���ʣ�	
		if(INPUTDEVICE.temperature >= 24 ){
			
			if(1!=zhilengre_Flag){
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_background_zhilengre_335_285_46x19,335,285);
				GUI_SetFont(&GUI_Fontyouyuan16);
				GUI_DispStringHCenterAt(_apStrings_zhileng[0],358,285);
				GUI_SetFont(&GUI_Font32_ASCII);
				zhilengre_Flag=1;
			}
			
			GUI_MEMDEV_CopyToLCDAt(hMem_Sub_fan_324_205_73x72[Temp_Counter],324,205);
			Temp_Counter++;
			if(5<=Temp_Counter)	Temp_Counter=0;				
		}
		else if(INPUTDEVICE.temperature <= 20){
			if(2!=zhilengre_Flag){
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_background_zhilengre_335_285_46x19,335,285);
				GUI_SetFont(&GUI_Fontyouyuan16);
				GUI_DispStringHCenterAt(_apStrings_zhire[0],358,285);
				GUI_SetFont(&GUI_Font32_ASCII);
				zhilengre_Flag=2;
			}
			
			if(3<=Temp_Counter)Temp_Counter=0;
			GUI_MEMDEV_CopyToLCDAt(hMem_Sub_heat_324_205_73x72[Temp_Counter],324,205);
			Temp_Counter++;			
		}
		else{
			if(3!=zhilengre_Flag){
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_fan_324_205_73x72[0],324,205);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_background_zhilengre_335_285_46x19,335,285);
				GUI_SetFont(&GUI_Fontyouyuan16);
				GUI_DispStringHCenterAt(_apStrings_shushi[0],358,285);
				GUI_SetFont(&GUI_Font32_ASCII);
				zhilengre_Flag=3;					
			}			
		}
	//��ʾ�¶�ֵ
		if(Temperature_Record!=INPUTDEVICE.temperature){
			GUI_MEMDEV_CopyToLCDAt(hMem_Sub_background_degree_165_225_52x29,165,225);
			sprintf(Temperature_str,"%d",INPUTDEVICE.temperature);
			GUI_DispStringHCenterAt(Temperature_str,191,225);
			Temperature_Record=INPUTDEVICE.temperature;
		}
	//��ʾ�¶ȶ���
		GUI_MEMDEV_CopyToLCDAt(hMem_Sub_temper_84_199_12x43[Temp_flash_Counter],84,199);
		Temp_flash_Counter++;
		if(Temp_flash_Counter>=3)Temp_flash_Counter=0;
	
		
	//��ʪ��	�Լ���ʾ��ʪ״̬����ʪ/ȥʪ/���ʣ�	zhilengre_Flag
		if(INPUTDEVICE.humidity >= 60){
			if(1!=jiachushi_Flag){
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_background_jiachushi_340_167_46x19,340,167);
				GUI_SetFont(&GUI_Fontyouyuan16);
				GUI_DispStringHCenterAt(_apStrings_chushi[0],363,167);
				GUI_SetFont(&GUI_Font32_ASCII);
				jiachushi_Flag=1;
			}
			
			GUI_MEMDEV_CopyToLCDAt(hMem_Sub_fog_365_50_115x110[7-Humidity_Counter],365,50);
			Humidity_Counter++;
			if(8<=Humidity_Counter)	Humidity_Counter=0;	
		}
		else if(INPUTDEVICE.humidity <= 50){
			if(2!=jiachushi_Flag){
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_background_jiachushi_340_167_46x19,340,167);
				GUI_SetFont(&GUI_Fontyouyuan16);
				GUI_DispStringHCenterAt(_apStrings_jiashi[0],363,167);
				GUI_SetFont(&GUI_Font32_ASCII);
				jiachushi_Flag=2;
			}			
			GUI_MEMDEV_CopyToLCDAt(hMem_Sub_fog_365_50_115x110[Humidity_Counter],365,50);
			Humidity_Counter++;
			if(8<=Humidity_Counter)	Humidity_Counter=0;	
		
		}
		else{
			GUI_MEMDEV_CopyToLCDAt(hMem_Sub_fog_365_50_115x110[8],365,50);
			if(3!=jiachushi_Flag){
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_background_jiachushi_340_167_46x19,340,167);
				GUI_SetFont(&GUI_Fontyouyuan16);
				GUI_DispStringHCenterAt(_apStrings_shushi[0],363,167);
				GUI_SetFont(&GUI_Font32_ASCII);
				jiachushi_Flag=3;
			}		
		}
	//��ʾʪ��ֵ
		if(Humidity_Record!=INPUTDEVICE.humidity){
			GUI_MEMDEV_CopyToLCDAt(hMem_Sub_background_percent_163_112_57x34,163,112);
			sprintf(Humidity_str,"%d",INPUTDEVICE.humidity);
			GUI_DispStringHCenterAt(Humidity_str,191,114);
			Humidity_Record=INPUTDEVICE.humidity;
		}
//
		if(3!=OUTPUTDEVICE.Cureent_Exam_Num){
				
			for(Delete_Counter=0;Delete_Counter<=4;Delete_Counter++){
				Delete_MEMDEV_Icon(hMem_Sub_fan_324_205_73x72[Delete_Counter]);
			}
			
			for(Delete_Counter=0;Delete_Counter<=2;Delete_Counter++){
				Delete_MEMDEV_Icon(hMem_Sub_heat_324_205_73x72[Delete_Counter]);
			}
			
			for(Delete_Counter=0;Delete_Counter<=2;Delete_Counter++){
				Delete_MEMDEV_Icon(hMem_Sub_temper_84_199_12x43[Delete_Counter]);
			}
			
			for(Delete_Counter=0;Delete_Counter<=8;Delete_Counter++){
				Delete_MEMDEV_Icon(hMem_Sub_fog_365_50_115x110[Delete_Counter]);
			}
			
			Delete_MEMDEV_Icon(hMem_Sub_background_degree_165_225_52x29);
			Delete_MEMDEV_Icon(hMem_Sub_background_percent_163_112_57x34);
			Delete_MEMDEV_Icon(hMem_Sub_background_jiachushi_340_167_46x19);
			Delete_MEMDEV_Icon(hMem_Sub_background_zhilengre_335_285_46x19);		
			break;
		}		
	GUI_Delay(10);
//		OSTimeDlyHMSM(0, 0, 0, 10);//1000ms		
	}
}


void bmpdisplay_exam4(void)
{
	int Distance_Counter=7;
	int Water_flash_Counter=0;
	int Delete_Counter=0;
	
	int Water_Level_State=4;

	float Distance_Record=9.0;
	
	char Distance_str[5];	
	
	GUI_MEMDEV_Handle hMem_Main;

	GUI_MEMDEV_Handle hMem_Sub_bridge_272_175_171x54[8];	
	GUI_MEMDEV_Handle hMem_Sub_water_53_xx_151x29[5];
	GUI_MEMDEV_Handle hMem_Sub_water_level_state_280_90_160x30[3];
	GUI_MEMDEV_Handle hMem_Sub_water_level_background_53_173_151x69[3];	

	GUI_MEMDEV_Handle hMem_Sub_distance_background_140_88_54x32;
	

//
// Create the memory device
//
	hMem_Main = GUI_MEMDEV_Create(0, 0, 480, 320);

	
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(0x00d1fef0);
	GUI_SetFont(&GUI_Font24_ASCII);
//	GUI_SetFont(&GUI_Fontyouyuan20);

	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_UC_SetEncodeUTF8();
	GUI_Clear();

	GUI_MEMDEV_Select(hMem_Main);//ѡ�д洢�豸		
	dispbmpex("0:/picture/face.bmp",0,0,	0);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_CopyToLCDAt(hMem_Main, 0, 0);
//	GUI_Delay(5000);	
	
	GUI_MEMDEV_Select(hMem_Main);//ѡ�д洢�豸		
	dispbmpex("0:/picture/exam4/exam4_background.bmp",0,0,0);
	GUI_MEMDEV_Select(0);	
	GUI_MEMDEV_CopyToLCDAt(hMem_Main, 0, 0);	
	GUI_MEMDEV_Delete(hMem_Main);

	hMem_Sub_bridge_272_175_171x54[0]=Create_MEMDEV_Icon("0:/picture/exam4/bridge1_272_175_171x54.bmp",272,175);
	hMem_Sub_bridge_272_175_171x54[1]=Create_MEMDEV_Icon("0:/picture/exam4/bridge2_272_175_171x54.bmp",272,175);
	hMem_Sub_bridge_272_175_171x54[2]=Create_MEMDEV_Icon("0:/picture/exam4/bridge3_272_175_171x54.bmp",272,175);
	hMem_Sub_bridge_272_175_171x54[3]=Create_MEMDEV_Icon("0:/picture/exam4/bridge4_272_175_171x54.bmp",272,175);
	hMem_Sub_bridge_272_175_171x54[4]=Create_MEMDEV_Icon("0:/picture/exam4/bridge5_272_175_171x54.bmp",272,175);
	hMem_Sub_bridge_272_175_171x54[5]=Create_MEMDEV_Icon("0:/picture/exam4/bridge6_272_175_171x54.bmp",272,175);	
	hMem_Sub_bridge_272_175_171x54[6]=Create_MEMDEV_Icon("0:/picture/exam4/bridge7_272_175_171x54.bmp",272,175);
	hMem_Sub_bridge_272_175_171x54[7]=Create_MEMDEV_Icon("0:/picture/exam4/bridge8_272_175_171x54.bmp",272,175);	
	
	hMem_Sub_water_53_xx_151x29[0]=Create_MEMDEV_Icon("0:/picture/exam4/water1_53_xx_151x29.bmp",51,199);	
	hMem_Sub_water_53_xx_151x29[1]=Create_MEMDEV_Icon("0:/picture/exam4/water2_53_xx_151x29.bmp",51,199);
	hMem_Sub_water_53_xx_151x29[2]=Create_MEMDEV_Icon("0:/picture/exam4/water3_53_xx_151x29.bmp",51,199);
	hMem_Sub_water_53_xx_151x29[3]=Create_MEMDEV_Icon("0:/picture/exam4/water4_53_xx_151x29.bmp",51,199);
	hMem_Sub_water_53_xx_151x29[4]=Create_MEMDEV_Icon("0:/picture/exam4/water5_53_xx_151x29.bmp",51,199);
	
	hMem_Sub_water_level_state_280_90_160x30[0]=Create_MEMDEV_Icon("0:/picture/exam4/water_level_low_280_90_160x30.bmp",280,90);
	hMem_Sub_water_level_state_280_90_160x30[1]=Create_MEMDEV_Icon("0:/picture/exam4/water_level_normal_280_90_160x30.bmp",280,90);
	hMem_Sub_water_level_state_280_90_160x30[2]=Create_MEMDEV_Icon("0:/picture/exam4/water_level_high_280_90_160x30.bmp",280,90);
	
	hMem_Sub_water_level_background_53_173_151x69[0]=Create_MEMDEV_Icon("0:/picture/exam4/water_level_low_background_53_173_151x69.bmp",53,173);	
	hMem_Sub_water_level_background_53_173_151x69[1]=Create_MEMDEV_Icon("0:/picture/exam4/water_level_normal_background_53_173_151x69.bmp",53,173);	
	hMem_Sub_water_level_background_53_173_151x69[2]=Create_MEMDEV_Icon("0:/picture/exam4/water_level_high_background_53_173_151x69.bmp",53,173);	

	hMem_Sub_distance_background_140_88_54x32 = Create_MEMDEV_Icon("0:/picture/exam4/distance_background_140_88_54x32.bmp",140,88);

	while(1){
		
		//��ʾ����բ����
		if(INPUTDEVICE.Distance<=3){//��ˮλ����ִ��һ��
			if(Water_Level_State!=1){
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_water_level_state_280_90_160x30[0],280,90);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_water_level_background_53_173_151x69[0],53,173);				
				Water_Level_State=1;
			}
			if(Distance_Counter<7){
				Distance_Counter++;
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_bridge_272_175_171x54[Distance_Counter],272,175);
			}		
		}
		else if(INPUTDEVICE.Distance>=6){//��ˮλ����ִ��һ��
			if(Water_Level_State!=3){
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_water_level_state_280_90_160x30[2],280,90);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_water_level_background_53_173_151x69[2],53,173);	
				Water_Level_State=3;
			}
			if(Distance_Counter>=1){
				Distance_Counter--;
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_bridge_272_175_171x54[Distance_Counter],272,175);
			}
		}
		else{//����ˮλ
			if(Water_Level_State!=2){
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_water_level_state_280_90_160x30[1],280,90);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_water_level_background_53_173_151x69[1],53,173);	
				Water_Level_State=2;
			}
			
			if(Distance_Counter!=5){
				if(Distance_Counter<5)Distance_Counter++;
				else if(Distance_Counter>5)Distance_Counter--;
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_bridge_272_175_171x54[Distance_Counter],272,175);
			}
		}
		//��ʾ����
		if(INPUTDEVICE.Distance!=Distance_Record){
			Distance_Record=INPUTDEVICE.Distance;
			GUI_MEMDEV_CopyToLCDAt(hMem_Sub_distance_background_140_88_54x32,140,88);
			sprintf(Distance_str,"%.2f",INPUTDEVICE.Distance);
			GUI_DispStringHCenterAt(Distance_str,167,93);
		}
		//ˮ����	
		if(Water_Level_State==1)GUI_MEMDEV_CopyToLCDAt(hMem_Sub_water_53_xx_151x29[Water_flash_Counter],53,212);
		else if(Water_Level_State==2)GUI_MEMDEV_CopyToLCDAt(hMem_Sub_water_53_xx_151x29[Water_flash_Counter],53,196);
		else if(Water_Level_State==3)GUI_MEMDEV_CopyToLCDAt(hMem_Sub_water_53_xx_151x29[Water_flash_Counter],53,172);
		
		Water_flash_Counter++;		
		if(Water_flash_Counter>=5)Water_flash_Counter=0;
		
		if(4!=OUTPUTDEVICE.Cureent_Exam_Num){
				
			for(Delete_Counter=0;Delete_Counter<=7;Delete_Counter++){
				Delete_MEMDEV_Icon(hMem_Sub_bridge_272_175_171x54[Delete_Counter]);
			}
			
			for(Delete_Counter=0;Delete_Counter<=4;Delete_Counter++){
				Delete_MEMDEV_Icon(hMem_Sub_water_53_xx_151x29[Delete_Counter]);
			}
			
			for(Delete_Counter=0;Delete_Counter<=2;Delete_Counter++){
				Delete_MEMDEV_Icon(hMem_Sub_water_level_state_280_90_160x30[Delete_Counter]);
			}
			
			for(Delete_Counter=0;Delete_Counter<=2;Delete_Counter++){
				Delete_MEMDEV_Icon(hMem_Sub_water_level_background_53_173_151x69[Delete_Counter]);
			}
			
			Delete_MEMDEV_Icon(hMem_Sub_distance_background_140_88_54x32);	
			break;
		}	
		GUI_Delay(10);		
	}
}


int IR_LearnState=3;
void bmpdisplay_exam5(void){
	int Delete_Counter=0;
	int counter_2=0;
	
	int Recomend_Record=4;
	
	GUI_MEMDEV_Handle hMem_Main;

	GUI_MEMDEV_Handle hMem_Sub_light_top_135_59_80x83[3];
	GUI_MEMDEV_Handle hMem_Sub_light_middle_95_140_80x83[3];	
	GUI_MEMDEV_Handle hMem_Sub_light_bottom_42_214_80x83[3];
	
	GUI_MEMDEV_Handle hMem_Sub_Recomend_Learncancel_195_193_256x31;	
	GUI_MEMDEV_Handle hMem_Sub_Recomend_Learnsuccess_195_193_256x31;	
	GUI_MEMDEV_Handle hMem_Sub_Recomend_Pressbuten_195_193_256x31;	
	GUI_MEMDEV_Handle hMem_Sub_Recomend_Sendsuccess_195_193_256x31;	

//
// Create the memory device
//
	hMem_Main = GUI_MEMDEV_Create(0, 0, 480, 320);

	
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(0x00d1fef0);
	GUI_SetFont(&GUI_Font24_ASCII);
//	GUI_SetFont(&GUI_Fontyouyuan20);

	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_UC_SetEncodeUTF8();
	GUI_Clear();

	GUI_MEMDEV_Select(hMem_Main);//ѡ�д洢�豸		
	dispbmpex("0:/picture/face.bmp",0,0,	0);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_CopyToLCDAt(hMem_Main, 0, 0);
//	GUI_Delay(5000);	
	
	GUI_MEMDEV_Select(hMem_Main);//ѡ�д洢�豸		
	dispbmpex("0:/picture/exam5/exam5_background.bmp",0,0,0);
	GUI_MEMDEV_Select(0);	
	GUI_MEMDEV_CopyToLCDAt(hMem_Main, 0, 0);	
	GUI_MEMDEV_Delete(hMem_Main);

	hMem_Sub_light_top_135_59_80x83[0]=Create_MEMDEV_Icon("0:/picture/exam5/light_top1_135_59_80x83.bmp",135,59);	
	hMem_Sub_light_top_135_59_80x83[1]=Create_MEMDEV_Icon("0:/picture/exam5/light_top2_135_59_80x83.bmp",135,59);
	hMem_Sub_light_top_135_59_80x83[2]=Create_MEMDEV_Icon("0:/picture/exam5/light_top3_135_59_80x83.bmp",135,59);
	
	hMem_Sub_light_middle_95_140_80x83[0]=Create_MEMDEV_Icon("0:/picture/exam5/light_middle1_95_140_80x83.bmp",95,140);	
	hMem_Sub_light_middle_95_140_80x83[1]=Create_MEMDEV_Icon("0:/picture/exam5/light_middle2_95_140_80x83.bmp",95,140);
	hMem_Sub_light_middle_95_140_80x83[2]=Create_MEMDEV_Icon("0:/picture/exam5/light_middle3_95_140_80x83.bmp",95,140);
	
	hMem_Sub_light_bottom_42_214_80x83[0]=Create_MEMDEV_Icon("0:/picture/exam5/light_bottom1_42_214_80x83.bmp",42,214);	
	hMem_Sub_light_bottom_42_214_80x83[1]=Create_MEMDEV_Icon("0:/picture/exam5/light_bottom2_42_214_80x83.bmp",42,214);
	hMem_Sub_light_bottom_42_214_80x83[2]=Create_MEMDEV_Icon("0:/picture/exam5/light_bottom3_42_214_80x83.bmp",42,214);
	
	hMem_Sub_Recomend_Learncancel_195_193_256x31=Create_MEMDEV_Icon("0:/picture/exam5/Recomend_Learncancel_195_193_256x31.bmp",195,193);	
	hMem_Sub_Recomend_Learnsuccess_195_193_256x31=Create_MEMDEV_Icon("0:/picture/exam5/Recomend_Learnsuccess_195_193_256x31.bmp",195,193);	
	hMem_Sub_Recomend_Pressbuten_195_193_256x31=Create_MEMDEV_Icon("0:/picture/exam5/Recomend_Pressbuten_195_193_256x31.bmp",195,193);	
	hMem_Sub_Recomend_Sendsuccess_195_193_256x31=Create_MEMDEV_Icon("0:/picture/exam5/Recomend_Sendsuccess_195_193_256x31.bmp",195,193);

	while(1){
		if(Recomend_Record!=IR_LearnState){
			Recomend_Record=IR_LearnState;
			switch(IR_LearnState){
				case 0:GUI_MEMDEV_CopyToLCDAt(hMem_Sub_Recomend_Pressbuten_195_193_256x31,195,193);				
					counter_2=0;
					break;
				case 1:GUI_MEMDEV_CopyToLCDAt(hMem_Sub_Recomend_Learnsuccess_195_193_256x31,195,193);
					counter_2=5;				
					break;
				case 2:GUI_MEMDEV_CopyToLCDAt(hMem_Sub_Recomend_Learncancel_195_193_256x31,195,193);
					counter_2=4;				
					break;
				case 3:GUI_MEMDEV_CopyToLCDAt(hMem_Sub_Recomend_Sendsuccess_195_193_256x31,195,193);
					counter_2=5;				
					break;	
			}
		}
			
		switch(counter_2++){
			case 0:
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_top_135_59_80x83[0],135,59);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_middle_95_140_80x83[1],95,140);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_bottom_42_214_80x83[2],42,214);
				break;
			case 1:
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_top_135_59_80x83[1],135,59);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_middle_95_140_80x83[2],95,140);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_bottom_42_214_80x83[0],42,214);
				break;
			case 2:
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_top_135_59_80x83[2],135,59);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_middle_95_140_80x83[0],95,140);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_bottom_42_214_80x83[1],42,214);
				break;
			case 3:
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_top_135_59_80x83[1],135,59);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_middle_95_140_80x83[2],95,140);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_bottom_42_214_80x83[0],42,214);
				counter_2=0;
				break;
			case 4:
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_top_135_59_80x83[0],135,59);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_middle_95_140_80x83[1],95,140);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_bottom_42_214_80x83[2],42,214);
				counter_2=4;			
				break;			
			case 5:
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_top_135_59_80x83[0],135,59);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_middle_95_140_80x83[0],95,140);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_bottom_42_214_80x83[0],42,214);
				break;
			case 6:
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_top_135_59_80x83[1],135,59);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_middle_95_140_80x83[1],95,140);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_bottom_42_214_80x83[1],42,214);
				break;
			case 7:
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_top_135_59_80x83[2],135,59);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_middle_95_140_80x83[2],95,140);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_bottom_42_214_80x83[2],42,214);	
				break;
			case 8:
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_top_135_59_80x83[1],135,59);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_middle_95_140_80x83[1],95,140);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_light_bottom_42_214_80x83[1],42,214);	
				counter_2=5;
				break;			
		}
		if(5!=OUTPUTDEVICE.Cureent_Exam_Num){
				
			for(Delete_Counter=0;Delete_Counter<=2;Delete_Counter++){
				Delete_MEMDEV_Icon(hMem_Sub_light_top_135_59_80x83[Delete_Counter]);
			}
			
			for(Delete_Counter=0;Delete_Counter<=2;Delete_Counter++){
				Delete_MEMDEV_Icon(hMem_Sub_light_middle_95_140_80x83[Delete_Counter]);
			}
			
			for(Delete_Counter=0;Delete_Counter<=2;Delete_Counter++){
				Delete_MEMDEV_Icon(hMem_Sub_light_bottom_42_214_80x83[Delete_Counter]);
			}
			
			Delete_MEMDEV_Icon(hMem_Sub_Recomend_Learncancel_195_193_256x31);	
			Delete_MEMDEV_Icon(hMem_Sub_Recomend_Learnsuccess_195_193_256x31);	
			Delete_MEMDEV_Icon(hMem_Sub_Recomend_Pressbuten_195_193_256x31);	
			Delete_MEMDEV_Icon(hMem_Sub_Recomend_Sendsuccess_195_193_256x31);	
			break;
		}			
		GUI_Delay(20);	
	}
}


void bmpdisplay_exam6_bus(void){
	int Putcard_Flag=0;		
  int RFID_CARDID_Record=0;
	int RFID_CARDDATA_Record=0;
	char RFID_CARDID_str[20];
	char remaining_sum_str[10];	
	
	GUI_MEMDEV_Handle hMem_Main;

	GUI_MEMDEV_Handle hMem_Sub_Recomend_Putcard_75_105_160x80;
	GUI_MEMDEV_Handle hMem_Sub_Recomend_Readcardinfo_75_105_160x80;	
	GUI_MEMDEV_Handle hMem_Sub_Recomend_Recharge_75_105_160x80;
	GUI_MEMDEV_Handle hMem_Sub_Recomend_Rechargesuccess_75_105_160x80;
	GUI_MEMDEV_Handle	hMem_Sub_Recomend_Rechargefault_75_105_160x80;
	GUI_MEMDEV_Handle hMem_Sub_Recomend_remaining_sum_clear_75_105_160x80;
	GUI_MEMDEV_Handle hMem_Sub_Recomend_Slotcard_75_105_160x80;
	
	GUI_MEMDEV_Handle hMem_Sub_ID_background_130_135_77x17;
	GUI_MEMDEV_Handle hMem_Sub_not_enough_145_157_63x23;	
	GUI_MEMDEV_Handle hMem_Sub_remaining_sum_background_145_160_42x18;	

//
// Create the memory device
//
	hMem_Main = GUI_MEMDEV_Create(0, 0, 480, 320);

	
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(0x00d1fef0);
	GUI_SetFont(&GUI_Font16_ASCII);
//	GUI_SetFont(&GUI_Fontyouyuan20);

	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_UC_SetEncodeUTF8();
	GUI_Clear();

	GUI_MEMDEV_Select(hMem_Main);//ѡ�д洢�豸		
	dispbmpex("0:/picture/face.bmp",0,0,0);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_CopyToLCDAt(hMem_Main,0,0);
	
	GUI_MEMDEV_Select(hMem_Main);//ѡ�д洢�豸		
	dispbmpex("0:/picture/exam6/exam6_buscardmanage_background.bmp",0,0,0);
	GUI_MEMDEV_Select(0);	
	GUI_MEMDEV_CopyToLCDAt(hMem_Main, 0, 0);	
	GUI_MEMDEV_Delete(hMem_Main);	
	
	hMem_Sub_Recomend_Putcard_75_105_160x80=Create_MEMDEV_Icon("0:/picture/exam6/Recomend_Putcard_75_105_160x80.bmp",160,80);	
	hMem_Sub_Recomend_Readcardinfo_75_105_160x80=Create_MEMDEV_Icon("0:/picture/exam6/Recomend_Readcardinfo_75_105_160x80.bmp",160,80);	
	hMem_Sub_Recomend_Recharge_75_105_160x80=Create_MEMDEV_Icon("0:/picture/exam6/Recomend_Recharge_75_105_160x80.bmp",160,80);	
	hMem_Sub_Recomend_Rechargesuccess_75_105_160x80=Create_MEMDEV_Icon("0:/picture/exam6/Recomend_Rechargesuccess_75_105_160x80.bmp",160,80);	
	hMem_Sub_Recomend_Rechargefault_75_105_160x80=Create_MEMDEV_Icon("0:/picture/exam6/Recomend_Rechargefault_75_105_160x80.bmp",160,80);	
	hMem_Sub_Recomend_remaining_sum_clear_75_105_160x80=Create_MEMDEV_Icon("0:/picture/exam6/Recomend_remaining_sum_clear_75_105_160x80.bmp",160,80);	
	hMem_Sub_Recomend_Slotcard_75_105_160x80=Create_MEMDEV_Icon("0:/picture/exam6/Recomend_Slotcard_75_105_160x80.bmp",160,80);	

	hMem_Sub_ID_background_130_135_77x17=Create_MEMDEV_Icon("0:/picture/exam6/ID_background_130_135_77x17.bmp",130,135);	
	hMem_Sub_not_enough_145_157_63x23=Create_MEMDEV_Icon("0:/picture/exam6/not_enough_145_157_63x23.bmp",145,157);	
	hMem_Sub_remaining_sum_background_145_160_42x18=Create_MEMDEV_Icon("0:/picture/exam6/remaining_sum_background_145_160_42x18.bmp",145,160);	


	OUTPUTDEVICE.RFID_CARD.rfid_card_Info.Data=10;
	INPUTDEVICE.RFID_CARD.rfid_card_Info.Data=0;
	
		switch(2){
				case 1:
					GUI_MEMDEV_CopyToLCDAt(hMem_Sub_Recomend_Putcard_75_105_160x80,75,105);
					break;
				case 2:
					GUI_MEMDEV_CopyToLCDAt(hMem_Sub_Recomend_Slotcard_75_105_160x80,75,105);
					break;
		}
	while(1){
		switch(2){
			case 1:
				if(0==Read_Block(5,INPUTDEVICE.RFID_CARD.CARD_Info_Str)){
					if(RFID_CARDID_Record!=INPUTDEVICE.RFID_CARD.rfid_card_Info.RFID_CARDID){
						RFID_CARDID_Record=INPUTDEVICE.RFID_CARD.rfid_card_Info.RFID_CARDID;
						GUI_MEMDEV_CopyToLCDAt(hMem_Sub_Recomend_Readcardinfo_75_105_160x80,75,105);
						
						sprintf(RFID_CARDID_str,"%04X",RFID_CARDID_Record);
						GUI_DispStringHCenterAt(RFID_CARDID_str,169,135);			
					}
					if(RFID_CARDDATA_Record!=INPUTDEVICE.RFID_CARD.rfid_card_Info.Data){
						RFID_CARDDATA_Record=INPUTDEVICE.RFID_CARD.rfid_card_Info.Data;
						if(RFID_CARDDATA_Record>0){
							GUI_MEMDEV_CopyToLCDAt(hMem_Sub_remaining_sum_background_145_160_42x18,145,160);
							sprintf(remaining_sum_str,"%d",RFID_CARDDATA_Record);
							GUI_DispStringHCenterAt(remaining_sum_str,166,159);
						}
						else {
							GUI_MEMDEV_CopyToLCDAt(hMem_Sub_not_enough_145_157_63x23,145,157);
						}	
					}
					//��ֵ
					if(OUTPUTDEVICE.RFID_CARD.rfid_card_Info.Card_State==1){//�ж��������Ϣ�Ŀ�״̬�������Ƿ�д���µ����
						GUI_MEMDEV_CopyToLCDAt(hMem_Sub_Recomend_Recharge_75_105_160x80,75,105);
						if(!Write_Block(5,OUTPUTDEVICE.RFID_CARD.CARD_Info_Str)){	
							GUI_MEMDEV_CopyToLCDAt(hMem_Sub_Recomend_Rechargesuccess_75_105_160x80,75,105);
							GUI_Delay(50);
						}
						else GUI_MEMDEV_CopyToLCDAt(hMem_Sub_Recomend_Rechargefault_75_105_160x80,75,105);	
						
						while(0==Read_Block(5,INPUTDEVICE.RFID_CARD.CARD_Info_Str)){
							GUI_Delay(50);
						}						
						OUTPUTDEVICE.RFID_CARD.rfid_card_Info.Card_State=0;
					}
					else if(OUTPUTDEVICE.RFID_CARD.rfid_card_Info.Card_State==2){//�ж�״̬���������
						OUTPUTDEVICE.RFID_CARD.rfid_card_Info.Data=0;
						if(!Write_Block(5,OUTPUTDEVICE.RFID_CARD.CARD_Info_Str)){	
							GUI_MEMDEV_CopyToLCDAt(hMem_Sub_Recomend_remaining_sum_clear_75_105_160x80,75,105);
							GUI_Delay(50);
						}
						while(0==Read_Block(5,INPUTDEVICE.RFID_CARD.CARD_Info_Str)){
							GUI_Delay(50);
						}	
					}
					Putcard_Flag=1;	
				}
				else {//���ƿ����Ĵ���
					if(Putcard_Flag!=0){
						GUI_MEMDEV_CopyToLCDAt(hMem_Sub_Recomend_Putcard_75_105_160x80,75,105);
						Putcard_Flag=0;
						RFID_CARDID_Record=0;
						RFID_CARDDATA_Record=51300;
					}
				}			
				GUI_Delay(50);
				break;
			case 2:
				if(0==Read_Block(5,INPUTDEVICE.RFID_CARD.CARD_Info_Str)){
					if(RFID_CARDID_Record!=INPUTDEVICE.RFID_CARD.rfid_card_Info.RFID_CARDID){
						RFID_CARDID_Record=INPUTDEVICE.RFID_CARD.rfid_card_Info.RFID_CARDID;
						GUI_MEMDEV_CopyToLCDAt(hMem_Sub_Recomend_Readcardinfo_75_105_160x80,75,105);
						sprintf(RFID_CARDID_str,"%04X",RFID_CARDID_Record);
						GUI_DispStringHCenterAt(RFID_CARDID_str,169,135);			
					}
					if(RFID_CARDDATA_Record!=INPUTDEVICE.RFID_CARD.rfid_card_Info.Data){
						RFID_CARDDATA_Record=INPUTDEVICE.RFID_CARD.rfid_card_Info.Data;
						if(RFID_CARDDATA_Record>0){
							GUI_MEMDEV_CopyToLCDAt(hMem_Sub_remaining_sum_background_145_160_42x18,145,160);
							sprintf(remaining_sum_str,"%d",RFID_CARDDATA_Record);
							GUI_DispStringHCenterAt(remaining_sum_str,166,159);
						}
						else {
							GUI_MEMDEV_CopyToLCDAt(hMem_Sub_not_enough_145_157_63x23,145,157);
						}	
					}
					Putcard_Flag=1;
					//����			
					if(RFID_CARDDATA_Record>0){
						OUTPUTDEVICE.RFID_CARD.rfid_card_Info.Data=--RFID_CARDDATA_Record;
						Write_Block(5,OUTPUTDEVICE.RFID_CARD.CARD_Info_Str);
						GUI_MEMDEV_CopyToLCDAt(hMem_Sub_remaining_sum_background_145_160_42x18,145,160);
						sprintf(remaining_sum_str,"%d",RFID_CARDDATA_Record);
						GUI_DispStringHCenterAt(remaining_sum_str,166,159);
					}
					else {
						GUI_MEMDEV_CopyToLCDAt(hMem_Sub_not_enough_145_157_63x23,145,157);
					}
					
					while(0==Read_Block(5,INPUTDEVICE.RFID_CARD.CARD_Info_Str)){
						GUI_Delay(50);
					}
				}
				else {//���ƿ����Ĵ���
					if(Putcard_Flag!=0){
						GUI_MEMDEV_CopyToLCDAt(hMem_Sub_Recomend_Slotcard_75_105_160x80,75,105);
						Putcard_Flag=0;
						RFID_CARDID_Record=0;
						RFID_CARDDATA_Record=51300;
					}
				}
				GUI_Delay(50);
				break;								
		}
		if(61!=OUTPUTDEVICE.Cureent_Exam_Num){			
			Delete_MEMDEV_Icon(hMem_Sub_Recomend_Putcard_75_105_160x80);	
			Delete_MEMDEV_Icon(hMem_Sub_Recomend_Readcardinfo_75_105_160x80);	
			Delete_MEMDEV_Icon(hMem_Sub_Recomend_Recharge_75_105_160x80);	
			Delete_MEMDEV_Icon(hMem_Sub_Recomend_Rechargesuccess_75_105_160x80);	
			Delete_MEMDEV_Icon(hMem_Sub_Recomend_Rechargefault_75_105_160x80);
			Delete_MEMDEV_Icon(hMem_Sub_Recomend_remaining_sum_clear_75_105_160x80);
			Delete_MEMDEV_Icon(hMem_Sub_Recomend_Slotcard_75_105_160x80);
			
			Delete_MEMDEV_Icon(hMem_Sub_ID_background_130_135_77x17);	
			Delete_MEMDEV_Icon(hMem_Sub_not_enough_145_157_63x23);	
			Delete_MEMDEV_Icon(hMem_Sub_remaining_sum_background_145_160_42x18);				
			break;
		}		
	}
}

void bmpdisplay_exam6_entrance_guard(void){
	int Delete_Counter=0;
	int open_door_counter=0;
	
	GUI_MEMDEV_Handle hMem_Main;
	
	GUI_MEMDEV_Handle hMem_Sub_door_160_114_278x151[5];
	
	GUI_MEMDEV_Handle hMem_Sub_door_light_blue_247_91_100x22;
	GUI_MEMDEV_Handle hMem_Sub_door_light_red_247_91_100x22;
	GUI_MEMDEV_Handle hMem_Sub_door_light_grey_247_91_100x22;	
	
	GUI_MEMDEV_Handle hMem_Sub_entrance_guard_fault_50_132_56x23;	
	GUI_MEMDEV_Handle hMem_Sub_entrance_guard_pass_50_132_56x23;
	GUI_MEMDEV_Handle hMem_Sub_entrance_guard_recognising_50_132_56x23;	
	GUI_MEMDEV_Handle hMem_Sub_entrance_guard_void_50_132_56x23;

//
// Create the memory device
//
	hMem_Main = GUI_MEMDEV_Create(0, 0, 480, 320);

	
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(0x00d1fef0);
	GUI_SetFont(&GUI_Font16_ASCII);
//	GUI_SetFont(&GUI_Fontyouyuan20);

	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_UC_SetEncodeUTF8();
	GUI_Clear();

	GUI_MEMDEV_Select(hMem_Main);//ѡ�д洢�豸		
	dispbmpex("0:/picture/face.bmp",0,0,0);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_CopyToLCDAt(hMem_Main,0,0);
//	GUI_Delay(5000);	
	
	GUI_MEMDEV_Select(hMem_Main);//ѡ�д洢�豸		
	dispbmpex("0:/picture/exam6/exam6_entrance_guard_background.bmp",0,0,0);
	GUI_MEMDEV_Select(0);	
	GUI_MEMDEV_CopyToLCDAt(hMem_Main, 0, 0);	
	GUI_MEMDEV_Delete(hMem_Main);

	hMem_Sub_door_160_114_278x151[0]=Create_MEMDEV_Icon("0:/picture/exam6/door1_160_114_278x151.bmp",160,114);	
	hMem_Sub_door_160_114_278x151[1]=Create_MEMDEV_Icon("0:/picture/exam6/door2_160_114_278x151.bmp",160,114);	
	hMem_Sub_door_160_114_278x151[2]=Create_MEMDEV_Icon("0:/picture/exam6/door3_160_114_278x151.bmp",160,114);	
	hMem_Sub_door_160_114_278x151[3]=Create_MEMDEV_Icon("0:/picture/exam6/door4_160_114_278x151.bmp",160,114);
	hMem_Sub_door_160_114_278x151[4]=Create_MEMDEV_Icon("0:/picture/exam6/door5_160_114_278x151.bmp",160,114);

	hMem_Sub_door_light_blue_247_91_100x22=Create_MEMDEV_Icon("0:/picture/exam6/door_light_blue_247_91_100x22.bmp",247,91);
	hMem_Sub_door_light_red_247_91_100x22=Create_MEMDEV_Icon("0:/picture/exam6/door_light_red_247_91_100x22.bmp",247,91);	
	hMem_Sub_door_light_grey_247_91_100x22=Create_MEMDEV_Icon("0:/picture/exam6/door_light_grey_247_91_100x22.bmp",247,91);

	hMem_Sub_entrance_guard_fault_50_132_56x23=Create_MEMDEV_Icon("0:/picture/exam6/entrance_guard_fault_50_132_56x23.bmp",50,132);	
	hMem_Sub_entrance_guard_pass_50_132_56x23=Create_MEMDEV_Icon("0:/picture/exam6/entrance_guard_pass_50_132_56x23.bmp",50,132);	
	hMem_Sub_entrance_guard_recognising_50_132_56x23=Create_MEMDEV_Icon("0:/picture/exam6/entrance_guard_recognising_50_132_56x23.bmp",50,132);	
	hMem_Sub_entrance_guard_void_50_132_56x23=Create_MEMDEV_Icon("0:/picture/exam6/entrance_guard_void_50_132_56x23.bmp",50,132);	

	OUTPUTDEVICE.RFID_CARD.rfid_card_Info.entrance_guard_pass=1;
	Write_Block(5,OUTPUTDEVICE.RFID_CARD.CARD_Info_Str);
	while(1){
		if(0==Read_Block(5,INPUTDEVICE.RFID_CARD.CARD_Info_Str)){
			GUI_MEMDEV_CopyToLCDAt(hMem_Sub_entrance_guard_recognising_50_132_56x23,50,132);
			GUI_Delay(50);
			if(1==INPUTDEVICE.RFID_CARD.rfid_card_Info.entrance_guard_pass){
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_entrance_guard_pass_50_132_56x23,50,132);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_door_light_blue_247_91_100x22,247,91);
				GUI_Delay(50);
				for(open_door_counter=0;open_door_counter<5;open_door_counter++){
					GUI_MEMDEV_CopyToLCDAt(hMem_Sub_door_160_114_278x151[open_door_counter],160,114);
					GUI_Delay(10);
				}
				GUI_Delay(300);
				for(open_door_counter=0;open_door_counter<5;open_door_counter++){
					GUI_MEMDEV_CopyToLCDAt(hMem_Sub_door_160_114_278x151[4-open_door_counter],160,114);
					GUI_Delay(10);
				}
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_entrance_guard_void_50_132_56x23,50,132);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_door_light_grey_247_91_100x22,247,91);
			}
			else{
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_entrance_guard_fault_50_132_56x23,50,132);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_door_light_red_247_91_100x22,247,91);
				GUI_Delay(100);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_entrance_guard_void_50_132_56x23,50,132);
				GUI_MEMDEV_CopyToLCDAt(hMem_Sub_door_light_grey_247_91_100x22,247,91);			
			}
			while(0==Read_Block(5,INPUTDEVICE.RFID_CARD.CARD_Info_Str));		
		}				
		GUI_Delay(50);
		if(62!=OUTPUTDEVICE.Cureent_Exam_Num){			
			Delete_MEMDEV_Icon(hMem_Sub_entrance_guard_fault_50_132_56x23);	
			Delete_MEMDEV_Icon(hMem_Sub_entrance_guard_pass_50_132_56x23);	
			Delete_MEMDEV_Icon(hMem_Sub_entrance_guard_recognising_50_132_56x23);	
			Delete_MEMDEV_Icon(hMem_Sub_entrance_guard_void_50_132_56x23);

			Delete_MEMDEV_Icon(hMem_Sub_door_light_grey_247_91_100x22);
			Delete_MEMDEV_Icon(hMem_Sub_door_light_red_247_91_100x22);
			Delete_MEMDEV_Icon(hMem_Sub_door_light_blue_247_91_100x22);			

			for(Delete_Counter=0;Delete_Counter<=4;Delete_Counter++){
				Delete_MEMDEV_Icon(hMem_Sub_door_160_114_278x151[Delete_Counter]);
			}				
			break;
		}	
	}
}






























