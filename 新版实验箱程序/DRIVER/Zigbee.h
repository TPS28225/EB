#ifndef _ZIGBEE_H
#define _ZIGBEE_H
#include "main.h"

#define ZIGBEE_TIMER 					TIM5
#define ZIGBEE_TIMER_CLK 			RCC_APB1Periph_TIM5
#define ZIGBEE_TIMER_IRQ 			TIM5_IRQn

#define ZIGBEE_USART					UART5
#define ZIGBEE_USART_CLK 			RCC_APB1Periph_UART5
#define ZIGBEE_USART_IRQ 			UART5_IRQn

#define ZIGBEE_TX_PORT 				GPIOC
#define ZIGBEE_TX_PIN		GPIO_Pin_12
#define ZIGBEE_TX_PORT_CLK 		RCC_AHB1Periph_GPIOC

#define ZIGBEE_RX_PORT 				GPIOD
#define ZIGBEE_RX_PIN					GPIO_Pin_2
#define ZIGBEE_RX_PORT_CLK 		RCC_AHB1Periph_GPIOD

void Zigbee_RUN(void);
void Zigbee_Configuration(void);	
void Zigbee_Tx(char *buf,u16 len);

#endif































