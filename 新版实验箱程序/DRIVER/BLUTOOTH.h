#ifndef _BLUTOOTH_H
#define _BLUTOOTH_H
#include "main.h"

#define BLUTOOTH_USART					UART4
#define BLUTOOTH_USART_CLK 			RCC_APB1Periph_UART4
#define BLUTOOTH_USART_IRQ 			UART4_IRQn

#define BLUTOOTH_PORT_CLK				RCC_AHB1Periph_GPIOC

#define BLUTOOTH_TX_PORT 				GPIOC
#define BLUTOOTH_TX_PIN					GPIO_Pin_10
#define BLUTOOTH_TX_PORT_CLK 		RCC_AHB1Periph_GPIOC

#define BLUTOOTH_RX_PORT 				GPIOC
#define BLUTOOTH_RX_PIN					GPIO_Pin_11
#define BLUTOOTH_RX_PORT_CLK 		RCC_AHB1Periph_GPIOC

void BLUTOOTH_Configuration(void);
void BLUTOOTH_Run(void);
void Usart4_Init(u32 bound, u16 wordLength, u16 stopBit, u16 parity);
void Usart4_Send_Data(char *buf,u16 len);

#endif































