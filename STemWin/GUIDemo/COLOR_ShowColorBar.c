/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2014  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.26 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : COLOR_ShowColorBar.c
Purpose     : Example draws a color bar
Requirements: WindowManager - ( )
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "LCDConf.h"
#include "main.h"
/*******************************************************************
*
*       Defines
*
********************************************************************
*/
#define X_START 60
#define Y_START 40

//����������ص�RAM�е�BMPͼƬʱ��ͼƬÿ�е��ֽ���
#define BMPPERLINESIZE	2*1024	
/*******************************************************************
*
*       Types
*
********************************************************************
*/
typedef struct {
  int NumBars;

  GUI_COLOR Color;
  const char * s;
} BAR_DATA;

/*******************************************************************
*
*       Static data
*
********************************************************************
*/
static FIL BMPFile;
static char bmpBuffer[BMPPERLINESIZE];

static const BAR_DATA _aBarData[] = {
  { 2, GUI_RED    , "Red" },
  { 2, GUI_GREEN  , "Green" },
  { 2, GUI_BLUE   , "Blue" },
  { 1, GUI_WHITE  , "Grey" },
  { 2, GUI_YELLOW , "Yellow" },
  { 2, GUI_CYAN   , "Cyan" },
  { 2, GUI_MAGENTA, "Magenta" },
};

static const GUI_COLOR _aColorStart[] = { GUI_BLACK, GUI_WHITE };

/*******************************************************************
*
*       Static code
*
********************************************************************
*/
/*******************************************************************
*
*       _DemoShowColorBar
*/
static void _DemoShowColorBar(void) {
  GUI_RECT Rect;
  int      yStep;
  int      i;
  int      j;
  int      xSize;
  int      ySize;
  int      NumBars;
  int      NumColors;

  //
  // Get display size
  //
  xSize = LCD_GetXSize();
  ySize = LCD_GetYSize();
  //
  // Get number of bars
  //
  NumColors = GUI_COUNTOF(_aBarData);
  for (i = NumBars = 0, NumBars = 0; i < NumColors; i++) {
    NumBars += _aBarData[i].NumBars;
  }
  yStep = (ySize - Y_START) / NumBars;
  //
  // Draw text
  //
  Rect.x0 = 0;
  Rect.x1 = X_START - 1;
  Rect.y0 = Y_START;
	GUI_SetFont(&GUI_Font8x16);
  for (i = 0; i < NumColors; i++) {
    Rect.y1 = Rect.y0 + yStep * _aBarData[i].NumBars - 1;
    GUI_DispStringInRect(_aBarData[i].s, &Rect, GUI_TA_LEFT | GUI_TA_VCENTER);
    Rect.y0 = Rect.y1 + 1;
  }
  //
  // Draw colors
  //
  Rect.x0 = X_START;
  Rect.x1 = xSize - 1;
  Rect.y0 = Y_START;
  for (i = 0; i < NumColors; i++) {
    for (j = 0; j < _aBarData[i].NumBars; j++) {
      Rect.y1 = Rect.y0 + yStep - 1;
      GUI_DrawGradientH(Rect.x0, Rect.y0, Rect.x1, Rect.y1, _aColorStart[j], _aBarData[i].Color);
      Rect.y0 = Rect.y1 + 1;
    }
  }
}
/*********************************************************************
*
*       BmpGetData
*
* Function description
*   This routine is called by GUI_BMP_DrawEx(). The routine is responsible
*   for setting the data pointer to a valid data location with at least
*   one valid byte.
*
* Parameters:
*   p           - Pointer to application defined data.
*   NumBytesReq - Number of bytes requested.
*   ppData      - Pointer to data pointer. This pointer should be set to
*                 a valid location.
*   StartOfFile - If this flag is 1, the data pointer should be set to the
*                 beginning of the data stream.
*
* Return value:
*   Number of data bytes available.
*/
static int BmpGetData(void * p, const U8 ** ppData, unsigned NumBytesReq, U32 Off) 
{
	static int readaddress=0;
	FIL * phFile;
	UINT NumBytesRead;
	#if SYSTEM_SUPPORT_UCOS
		OS_CPU_SR cpu_sr;
	#endif
	
	phFile = (FIL *)p;
	
	if (NumBytesReq > sizeof(bmpBuffer)) 
	{
		NumBytesReq = sizeof(bmpBuffer);
	}

	//�ƶ�ָ�뵽Ӧ�ö�ȡ��λ��
	if(Off == 1) readaddress = 0;
	else readaddress=Off;
	#if SYSTEM_SUPPORT_UCOS
		OS_ENTER_CRITICAL();	//�ٽ���
	#endif
	f_lseek(phFile,readaddress); 
	
	//��ȡ���ݵ���������
	f_read(phFile,bmpBuffer,NumBytesReq,&NumBytesRead);
	#if SYSTEM_SUPPORT_UCOS
		OS_EXIT_CRITICAL();	//�˳��ٽ��� 
	#endif
	*ppData = (U8 *)bmpBuffer;
	return NumBytesRead;//���ض�ȡ�����ֽ���
}

//��ָ��λ����ʾ������ص�RAM�е�BMPͼƬ(���ļ�ϵͳ֧�֣�����СRAM���Ƽ�ʹ�ô˷�����)
//BMPFileName:ͼƬ��SD�����������洢�豸�е�·��
//mode:��ʾģʽ
//		0 ��ָ��λ����ʾ���в���x,yȷ����ʾλ��
//		1 ��LCD�м���ʾͼƬ����ѡ���ģʽ��ʱ�����x,y��Ч��
//x:ͼƬ���Ͻ���LCD�е�x��λ��(������modeΪ1ʱ���˲�����Ч)
//y:ͼƬ���Ͻ���LCD�е�y��λ��(������modeΪ1ʱ���˲�����Ч)
//member:  ���ű����ķ�����
//denom:���ű����ķ�ĸ��
//����ֵ:0 ��ʾ����,���� ʧ��
int dispbmpex(char *BMPFileName,u8 mode,u32 x,u32 y,int member,int denom)
{
	char result;
	int XSize,YSize;
	float Xflag,Yflag;
	GUI_COLOR forecolor,bkcolor;
	forecolor=GUI_GetColor();			//��ȡ��ǰǰ��ɫ
	bkcolor=GUI_GetBkColor();			//��ȡ��ǰ����ɫ
	
	result = f_open(&BMPFile,(const TCHAR*)BMPFileName,FA_READ);	//���ļ�
	//�ļ��򿪴���
	if(result != FR_OK) 	return 1;
		
	switch(mode)
	{
		case 0:	//��ָ��λ����ʾͼƬ
			if((member == 1) && (denom == 1)) //�������ţ�ֱ�ӻ���
			{
				GUI_BMP_DrawEx(BmpGetData,&BMPFile,x,y);//��ָ��λ����ʾBMPͼƬ
			}else //����ͼƬ��Ҫ����
			{
				GUI_BMP_DrawScaledEx(BmpGetData,&BMPFile,x,y,member,denom);
			}
			break;
		case 1:	//��LCD�м���ʾͼƬ
			XSize = GUI_BMP_GetXSizeEx(BmpGetData,&BMPFile);	//��ȡͼƬ��X���С
			YSize = GUI_BMP_GetYSizeEx(BmpGetData,&BMPFile);	//��ȡͼƬ��Y���С
			if((member == 1) && (denom == 1)) //�������ţ�ֱ�ӻ���
			{
				//��LCD�м���ʾͼƬ
				GUI_BMP_DrawEx(BmpGetData,&BMPFile,(lcddev.width-XSize)/2-1,(lcddev.height-YSize)/2-1);
			}else //����ͼƬ��Ҫ����
			{
				Xflag = (float)XSize*((float)member/(float)denom);
				Yflag = (float)YSize*((float)member/(float)denom);
				XSize = (lcddev.width-(int)Xflag)/2-1;
				YSize = (lcddev.height-(int)Yflag)/2-1;
				GUI_BMP_DrawScaledEx(BmpGetData,&BMPFile,XSize,YSize,member,denom);
			}
			break;
	}
	f_close(&BMPFile);		//�ر�BMPFile�ļ�
	GUI_SetColor(forecolor);		//�ָ�ǰ��ɫ
	GUI_SetBkColor(bkcolor);		//�ָ�����ɫ
	return 0;
}

//int dispstreambmpex(char *BMPFileName,u8 mode,u32 x,u32 y,int member,int denom)
//{
//	char result;
//	int XSize,YSize;
//	float Xflag,Yflag;
//	GUI_COLOR forecolor,bkcolor;
//	forecolor=GUI_GetColor();			//��ȡ��ǰǰ��ɫ
//	bkcolor=GUI_GetBkColor();			//��ȡ��ǰ����ɫ
//	
//	result = f_open(&BMPFile,(const TCHAR*)BMPFileName,FA_READ);	//���ļ�
//	//�ļ��򿪴���
//	if(result != FR_OK) 	return 1;

////	GUI_BMP_DrawEx(BmpGetData,&BMPFile,x,y);//��ָ��λ����ʾBMPͼƬ
//	GUI_DrawStreamedBitmapM565Ex(BmpGetData, &BMPFile,x,y);
//	
//	f_close(&BMPFile);		//�ر�BMPFile�ļ�
//	GUI_SetColor(forecolor);		//�ָ�ǰ��ɫ
//	GUI_SetBkColor(bkcolor);		//�ָ�����ɫ
//	return 0;
//}
/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  GUI_SetBkColor(GUI_BLACK);//GUI_BLACK
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);//GUI_WHITE
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_DispStringHCenterAt("COLOR_ShowColorBar - Sample", 160, 5);
  _DemoShowColorBar();
  while(1)
	{		
		dispbmpex("0:/picture/dog.bmp",0,0,	0,	1,1);
		GUI_Delay(3000);
		GUI_Clear();

		dispbmpex("0:/picture/face.bmp",0,0,	0,	1,1);
		GUI_Delay(3000);
		GUI_Clear();
	}
}

/*************************** End of file ****************************/
