#ifndef _HUMANBODYSENSOR_H
#define _HUMANBODYSENSOR_H

#include "main.h"

#define HUMANBODYSENSOR_IN_PORT 		GPIOC
#define HUMANBODYSENSOR_IN_PIN 			GPIO_Pin_13
#define HUMANBODYSENSOR_PORT_CLOCK 	RCC_AHB1Periph_GPIOC

void humanbodysensor_init(void);
void humanbodysensor_measure(void);

#endif













