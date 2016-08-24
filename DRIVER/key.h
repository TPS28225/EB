#ifndef _KEY_H
#define _KEY_H

#include "main.h"

#define KEY1_PIN               	GPIO_Pin_3              
#define KEY1_PORT         			GPIOD                    
#define KEY1_CLK          			RCC_AHB1Periph_GPIOD

#define KEY2_PIN               	GPIO_Pin_6               
#define KEY2_PORT         			GPIOD                   
#define KEY2_CLK          			RCC_AHB1Periph_GPIOD

//#define KEY3_PIN               	GPIO_Pin_7             
//#define KEY3_PORT         			GPIOD                     
//#define KEY3_CLK          			RCC_AHB1Periph_GPIOD
#define KEY3_PIN               	GPIO_Pin_4             
#define KEY3_PORT         			GPIOA                     
#define KEY3_CLK          			RCC_AHB1Periph_GPIOA

#define KEY4_PIN               GPIO_Pin_9               
#define KEY4_PORT         			GPIOG                     
#define KEY4_CLK          			RCC_AHB1Periph_GPIOG



#define DOOR_PIN               	GPIO_Pin_9               
#define DOOR_PORT         			GPIOC                     
#define DOOR_CLK          			RCC_AHB1Periph_GPIOC

#define HUMAN_PIN               GPIO_Pin_13               
#define HUMAN_PORT         			GPIOC                     
#define HUMAN_CLK          			RCC_AHB1Periph_GPIOC

#define SOUND_PIN               GPIO_Pin_7               
#define SOUND_PORT         			GPIOF                     
#define SOUND_CLK          			RCC_AHB1Periph_GPIOF
#define SOUND_EXIT_CLK 					RCC_APB2Periph_SYSCFG

#define VOICE_ADD_PIN           GPIO_Pin_8               
#define VOICE_ADD_PORT         	GPIOG                     
#define VOICE_ADD_CLK          	RCC_AHB1Periph_GPIOG

#define VOICE_RED_PIN           GPIO_Pin_8               
#define VOICE_RED_PORT         	GPIOC                     
#define VOICE_RED_CLK          	RCC_AHB1Periph_GPIOC

#define SONG_NEXT_PIN         	GPIO_Pin_11               
#define SONG_NEXT_PORT        	GPIOG                     
#define SONG_NEXT_CLK         	RCC_AHB1Periph_GPIOG

#define SONG_FORMER_PIN         GPIO_Pin_12               
#define SONG_FORMER_PORT        GPIOG                     
#define SONG_FORMER_CLK         RCC_AHB1Periph_GPIOG




#define DOOR 	GPIO_ReadInputDataBit(DOOR_PORT, DOOR_PIN)
#define KEY1 	GPIO_ReadInputDataBit(KEY1_PORT, KEY1_PIN)
#define KEY2 	GPIO_ReadInputDataBit(KEY2_PORT, KEY2_PIN)
#define KEY3 	GPIO_ReadInputDataBit(KEY3_PORT, KEY3_PIN)
#define KEY4 	GPIO_ReadInputDataBit(KEY4_PORT, KEY4_PIN)
#define HUMAN GPIO_ReadInputDataBit(HUMAN_PORT,HUMAN_PIN)
#define SOUND GPIO_ReadInputDataBit(SOUND_PORT,SOUND_PIN)

#define VOICE_ADD 	GPIO_ReadInputDataBit(VOICE_ADD_PORT, VOICE_ADD_PIN)
#define VOICE_RED 	GPIO_ReadInputDataBit(VOICE_RED_PORT, VOICE_RED_PIN)
#define SONG_NEXT 	GPIO_ReadInputDataBit(SONG_NEXT_PORT,	SONG_NEXT_PIN)
#define SONG_FORMER GPIO_ReadInputDataBit(SONG_FORMER_PORT,SONG_FORMER_PIN)

void KEY_init(void);
void KEY_RUN(void);

#endif











