#ifndef _BMPDISPLAY_H
#define _BMPDISPLAY_H
#include "main.h"
#include "GUI.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK STM32F103ս��������
//STemwin BMPͼƬ��ʾ 
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/4/10
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//ʹ��GUI_BMP_Draw()��������BMPͼƬ�Ļ�
//ͼƬ�Ǽ��ص�RAM�еģ���˲��ܴ���BMPMEMORYSIZE
//ע�⣺��ʾBMPͼƬʱ�ڴ�����ʹ�õ�EMWIN���ڴ����뺯�������
//BMPMEMORYSIZE���ܴ������Ǹ�EMWIN������ڴ�ش�С
#define BMPMEMORYSIZE	500*1024	//ͼƬ��С������500kb

//����������ص�RAM�е�BMPͼƬʱ��ͼƬÿ�е��ֽ���
#define BMPPERLINESIZE	2*1024		

int dispbmp(u8 *BMPFileName,u8 mode,u32 x,u32 y);
int dispbmpex(u8 *BMPFileName,u8 mode,u32 x,u32 y);
GUI_MEMDEV_Handle Create_MEMDEV_Icon(u8 *BMPFileName,u32 x,u32 y);
void Delete_MEMDEV_Icon(GUI_MEMDEV_Handle hMem_Sub);
void bmpdisplay_demo(void);
#endif