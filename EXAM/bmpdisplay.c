#include "bmpdisplay.h"
#include "GUI.h"
#include "malloc.h"
#include "ff.h"
#include "ili93xx.h"
#include "exammanager.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F103战舰开发板
//STemwin BMP图片显示 
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/4/10
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos 使用	  
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

	//移动指针到应该读取的位置
	if(Off == 1) readaddress = 0;
	else readaddress=Off;
	#if SYSTEM_SUPPORT_UCOS
		OS_ENTER_CRITICAL();	//临界区
	#endif
	f_lseek(phFile,readaddress); 
	
	//读取数据到缓冲区中
	f_read(phFile,bmpBuffer,NumBytesReq,&NumBytesRead);
	#if SYSTEM_SUPPORT_UCOS
		OS_EXIT_CRITICAL();	//退出临界区 
	#endif
	*ppData = (U8 *)bmpBuffer;
	return NumBytesRead;//返回读取到的字节数
}

//在指定位置显示加载到RAM中的BMP图片
//BMPFileName:图片在SD卡或者其他存储设备中的路径(需文件系统支持！)
//mode:显示模式
//		0 在指定位置显示，有参数x,y确定显示位置
//		1 在LCD中间显示图片，当选择此模式的时候参数x,y无效。
//x:图片左上角在LCD中的x轴位置(当参数mode为1时，此参数无效)
//y:图片左上角在LCD中的y轴位置(当参数mode为1时，此参数无效)
//member:  缩放比例的分子项
//denom:缩放比例的分母项
//返回值:0 显示正常,其他 失败
int dispbmp(u8 *BMPFileName,u8 mode,u32 x,u32 y)
{
	u16 bread;
	char *bmpbuffer;
	char result;
	GUI_COLOR forecolor,bkcolor;
	
	#if SYSTEM_SUPPORT_UCOS
		OS_CPU_SR cpu_sr;
	#endif

	forecolor=GUI_GetColor();			//获取当前前景色
	bkcolor=GUI_GetBkColor();			//获取当前背景色
	result = f_open(&BMPFile,(const TCHAR*)BMPFileName,FA_READ);	//打开文件
	//文件打开错误或者文件大于BMPMEMORYSIZE
	if((result != FR_OK) || (BMPFile.fsize>BMPMEMORYSIZE)) 	return 1;

	bmpbuffer = mymalloc(SRAMEX,BMPFile.fsize);//申请内存
	if(bmpbuffer == NULL) return 2;
	
	#if SYSTEM_SUPPORT_UCOS
		OS_ENTER_CRITICAL();	//临界区
	#endif
		
	result = f_read(&BMPFile,bmpbuffer,BMPFile.fsize,(UINT *)&bread); //读取数据
	if(result != FR_OK) return 3;
	
	#if SYSTEM_SUPPORT_UCOS
		OS_EXIT_CRITICAL();	//退出临界区
	#endif
	
	GUI_BMP_Draw(bmpbuffer,x,y);
	
	f_close(&BMPFile);		//关闭BMPFile文件
	myfree(SRAMEX,bmpbuffer);	//释放内存
	GUI_SetColor(forecolor);		//恢复前景色
	GUI_SetBkColor(bkcolor);		//恢复背景色
	return 0;
}

//在指定位置显示无需加载到RAM中的BMP图片(需文件系统支持！对于小RAM，推荐使用此方法！)
//BMPFileName:图片在SD卡或者其他存储设备中的路径
//mode:显示模式
//		0 在指定位置显示，有参数x,y确定显示位置
//		1 在LCD中间显示图片，当选择此模式的时候参数x,y无效。
//x:图片左上角在LCD中的x轴位置(当参数mode为1时，此参数无效)
//y:图片左上角在LCD中的y轴位置(当参数mode为1时，此参数无效)
//member:  缩放比例的分子项
//denom:缩放比例的分母项
//返回值:0 显示正常,其他 失败
int dispbmpex(u8 *BMPFileName,u8 mode,u32 x,u32 y)
{
	char result;
	GUI_COLOR forecolor,bkcolor;
	forecolor=GUI_GetColor();			//获取当前前景色
	bkcolor=GUI_GetBkColor();			//获取当前背景色
	
	result = f_open(&BMPFile,(const TCHAR*)BMPFileName,FA_READ);	//打开文件
	//文件打开错误
	if(result != FR_OK) 	return 1;

		
	GUI_BMP_DrawEx(BmpGetData,&BMPFile,x,y);//在指定位置显示BMP图片

	f_close(&BMPFile);		//关闭BMPFile文件
	GUI_SetColor(forecolor);		//恢复前景色
	GUI_SetBkColor(bkcolor);		//恢复背景色
	return 0;
}

int dispaly_icon(u8 *BMPFileName,u32 x,u32 y)
{
	char result;
	int XSize,YSize;
	GUI_MEMDEV_Handle hMem_Sub;
	
	result = f_open(&BMPFile,(const TCHAR*)BMPFileName,FA_READ);	//打开文件
	//文件打开错误
	if(result != FR_OK) 	return 0;
	
	XSize = GUI_BMP_GetXSizeEx(BmpGetData,&BMPFile);	//获取图片的X轴大小
	YSize = GUI_BMP_GetYSizeEx(BmpGetData,&BMPFile);	//获取图片的Y轴大小
	
	hMem_Sub = GUI_MEMDEV_Create(x, y, XSize, YSize);
	GUI_MEMDEV_Select(hMem_Sub);	
	
	GUI_BMP_DrawEx(BmpGetData,&BMPFile,x,y);//在指定位置显示BMP图片	
	
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
	
	result = f_open(&BMPFile,(const TCHAR*)BMPFileName,FA_READ);	//打开文件
	//文件打开错误
	if(result != FR_OK) 	return 0xffff;
	
	XSize = GUI_BMP_GetXSizeEx(BmpGetData,&BMPFile);	//获取图片的X轴大小
	YSize = GUI_BMP_GetYSizeEx(BmpGetData,&BMPFile);	//获取图片的Y轴大小
	hMem_Sub = GUI_MEMDEV_Create(x, y, XSize, YSize);
	GUI_MEMDEV_Select(hMem_Sub);	
	GUI_BMP_DrawEx(BmpGetData,&BMPFile,x,y);//在指定位置显示BMP图片	
	f_close(&BMPFile);		//关闭BMPFile文件	
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
