#include "bmpdisplay.h"
#include "GUI.h"
#include "malloc.h"
#include "ff.h"
#include "ili93xx.h"
#include "exammanager.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F103ս��������
//STemwin BMPͼƬ��ʾ 
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/4/10
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos ʹ��	  
#endif
static FIL BMPFile;
static char bmpBuffer[BMPPERLINESIZE];
/*******************************************************************
*
*       Static functions
*
********************************************************************
*/
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

//��ָ��λ����ʾ���ص�RAM�е�BMPͼƬ
//BMPFileName:ͼƬ��SD�����������洢�豸�е�·��(���ļ�ϵͳ֧�֣�)
//mode:��ʾģʽ
//		0 ��ָ��λ����ʾ���в���x,yȷ����ʾλ��
//		1 ��LCD�м���ʾͼƬ����ѡ���ģʽ��ʱ�����x,y��Ч��
//x:ͼƬ���Ͻ���LCD�е�x��λ��(������modeΪ1ʱ���˲�����Ч)
//y:ͼƬ���Ͻ���LCD�е�y��λ��(������modeΪ1ʱ���˲�����Ч)
//member:  ���ű����ķ�����
//denom:���ű����ķ�ĸ��
//����ֵ:0 ��ʾ����,���� ʧ��
int dispbmp(u8 *BMPFileName,u8 mode,u32 x,u32 y)
{
	u16 bread;
	char *bmpbuffer;
	char result;
	GUI_COLOR forecolor,bkcolor;
	
	#if SYSTEM_SUPPORT_UCOS
		OS_CPU_SR cpu_sr;
	#endif

	forecolor=GUI_GetColor();			//��ȡ��ǰǰ��ɫ
	bkcolor=GUI_GetBkColor();			//��ȡ��ǰ����ɫ
	result = f_open(&BMPFile,(const TCHAR*)BMPFileName,FA_READ);	//���ļ�
	//�ļ��򿪴�������ļ�����BMPMEMORYSIZE
	if((result != FR_OK) || (BMPFile.fsize>BMPMEMORYSIZE)) 	return 1;

	bmpbuffer = mymalloc(SRAMEX,BMPFile.fsize);//�����ڴ�
	if(bmpbuffer == NULL) return 2;
	
	#if SYSTEM_SUPPORT_UCOS
		OS_ENTER_CRITICAL();	//�ٽ���
	#endif
		
	result = f_read(&BMPFile,bmpbuffer,BMPFile.fsize,(UINT *)&bread); //��ȡ����
	if(result != FR_OK) return 3;
	
	#if SYSTEM_SUPPORT_UCOS
		OS_EXIT_CRITICAL();	//�˳��ٽ���
	#endif
	
	GUI_BMP_Draw(bmpbuffer,x,y);
	
	f_close(&BMPFile);		//�ر�BMPFile�ļ�
	myfree(SRAMEX,bmpbuffer);	//�ͷ��ڴ�
	GUI_SetColor(forecolor);		//�ָ�ǰ��ɫ
	GUI_SetBkColor(bkcolor);		//�ָ�����ɫ
	return 0;
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
int dispbmpex(u8 *BMPFileName,u8 mode,u32 x,u32 y)
{
	char result;
	GUI_COLOR forecolor,bkcolor;
	forecolor=GUI_GetColor();			//��ȡ��ǰǰ��ɫ
	bkcolor=GUI_GetBkColor();			//��ȡ��ǰ����ɫ
	
	result = f_open(&BMPFile,(const TCHAR*)BMPFileName,FA_READ);	//���ļ�
	//�ļ��򿪴���
	if(result != FR_OK) 	return 1;

		
	GUI_BMP_DrawEx(BmpGetData,&BMPFile,x,y);//��ָ��λ����ʾBMPͼƬ

	f_close(&BMPFile);		//�ر�BMPFile�ļ�
	GUI_SetColor(forecolor);		//�ָ�ǰ��ɫ
	GUI_SetBkColor(bkcolor);		//�ָ�����ɫ
	return 0;
}

int dispaly_icon(u8 *BMPFileName,u32 x,u32 y)
{
	char result;
	int XSize,YSize;
	GUI_MEMDEV_Handle hMem_Sub;
	
	result = f_open(&BMPFile,(const TCHAR*)BMPFileName,FA_READ);	//���ļ�
	//�ļ��򿪴���
	if(result != FR_OK) 	return 0;
	
	XSize = GUI_BMP_GetXSizeEx(BmpGetData,&BMPFile);	//��ȡͼƬ��X���С
	YSize = GUI_BMP_GetYSizeEx(BmpGetData,&BMPFile);	//��ȡͼƬ��Y���С
	
	hMem_Sub = GUI_MEMDEV_Create(x, y, XSize, YSize);
	GUI_MEMDEV_Select(hMem_Sub);	
	
	GUI_BMP_DrawEx(BmpGetData,&BMPFile,x,y);//��ָ��λ����ʾBMPͼƬ	
	
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_CopyToLCDAt(hMem_Sub, x, y);	
	GUI_MEMDEV_Delete(hMem_Sub);		
	
	return 0;
}

GUI_MEMDEV_Handle Create_MEMDEV_Icon(u8 *BMPFileName,u32 x,u32 y)
{
	char result;
	int XSize,YSize;
	GUI_MEMDEV_Handle hMem_Sub;
	
	result = f_open(&BMPFile,(const TCHAR*)BMPFileName,FA_READ);	//���ļ�
	//�ļ��򿪴���
	if(result != FR_OK) 	return 0xffff;
	
	XSize = GUI_BMP_GetXSizeEx(BmpGetData,&BMPFile);	//��ȡͼƬ��X���С
	YSize = GUI_BMP_GetYSizeEx(BmpGetData,&BMPFile);	//��ȡͼƬ��Y���С
	hMem_Sub = GUI_MEMDEV_Create(x, y, XSize, YSize);
	GUI_MEMDEV_Select(hMem_Sub);	
	GUI_BMP_DrawEx(BmpGetData,&BMPFile,x,y);//��ָ��λ����ʾBMPͼƬ	
	f_close(&BMPFile);		//�ر�BMPFile�ļ�	
	GUI_MEMDEV_Select(0);	
		
	return hMem_Sub;
}

void Delete_MEMDEV_Icon(GUI_MEMDEV_Handle hMem_Sub)
{
			GUI_MEMDEV_Delete(hMem_Sub);		
}

//void bmpdisplay_demo(void)
//{

//}
