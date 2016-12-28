#ifndef __UltrasonicWave_H
#define	__UltrasonicWave_H
#include "main.h"

    
#define TRIG_PORT    	 						GPIOB				// 
#define	TRIG_PIN       						GPIO_Pin_2  //TRIG
#define TRIG_PORT_CLK 						RCC_AHB1Periph_GPIOB

#define ECHO_PORT    	 						GPIOF				// 
#define	ECHO_PIN       						GPIO_Pin_11	//ECHO  
#define ECHO_PORT_CLK 						RCC_AHB1Periph_GPIOF

#define UltrasonicWave_TIMER			TIM10
#define UltrasonicWave_TIMER_CLK 	RCC_APB2Periph_TIM10

#define UltrasonicWave_EXIT_CLK 	RCC_APB2Periph_SYSCFG

void UltrasonicWave_Configuration(void);               //�Գ�����ģ���ʼ��
void UltrasonicWave_StartMeasure(void);                //��ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
void UltrasonicWave_MeasureDistance(void);
#endif /* __UltrasonicWave_H */

