#ifndef __DELAY_H
#define __DELAY_H 
#include "main.h"

#define DELAY_TIMER				TIM2
#define DELAY_TIMER_CLK 	RCC_APB1Periph_TIM2
#define DELAY_TIMER_IRQ 	TIM2_IRQn

void delay_init(void);
void delay_us(u32 nus);
void delay_ms(u32 nms);

#endif





























