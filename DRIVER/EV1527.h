#ifndef __EV1527_H
#define __EV1527_H

#include "main.h"

#define RF_CONT 150  //????50????,??3?????150????

#define RF_TX_PORT 				GPIOC
#define RF_TX_PIN					GPIO_Pin_13
#define RF_TX_PORT_CLK 		RCC_AHB1Periph_GPIOC

#define RF_RX_PORT 				GPIOA
#define RF_RX_PIN					GPIO_Pin_10
#define RF_RX_PORT_CLK 		RCC_AHB1Periph_GPIOA
#define RF_RX_EXIT_LINE 	EXTI_Line10

#define RF_TX_TIMER				TIM13
#define RF_TX_TIMER_CLK 	RCC_APB1Periph_TIM13

#define RF_RX_TIMER				TIM14
#define RF_RX_TIMER_CLK 	RCC_APB1Periph_TIM14

typedef struct{
	u8 Count;
	u16 TimeVal;
	u8 State;
	u8 HeadFlag;
	u8 ZaboFlag;
	u8 SendEnable;
	u8 SendCount;
	u8 SendTime;
	u8 SendFlag;
	u8 Movecnt;
	u32 SendData;
}RF_STRUCT;
extern RF_STRUCT Rf;

void RF_H3V4_H34B_Init(void);
u8 RF_H3V4F_Rev(u8 *decOut);
void RF_H34B_Send(u32 data);
void EXTI10_Int(u8 en);
void EV1527_Run(void);

void TIM13_Init(u16 arr,u16 psc);
void TIM13_Set(u8 sta);
void RF_EXTI_Init(void);
void TIM14_Set(u8 sta);
void TIM14_Init(u16 arr,u16 psc);
void Upload(void);
void Download(void);
					    
#endif


