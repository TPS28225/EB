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

void UltrasonicWave_Configuration(void);               //对超声波模块初始化
void UltrasonicWave_StartMeasure(void);                //开始测距，发送一个>10us的脉冲，然后测量返回的高电平时间
void UltrasonicWave_MeasureDistance(void);
#endif /* __UltrasonicWave_H */

