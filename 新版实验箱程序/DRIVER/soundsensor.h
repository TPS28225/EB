#ifndef _SOUNDSENSOR_H
#define _SOUNDSENSOR_H
#include "main.h"

#define SOUNDSENSOR_IN_PORT 		GPIOF
#define SOUNDSENSOR_IN_PIN 			GPIO_Pin_7
#define SOUNDSENSOR_PORT_CLOCK 	RCC_AHB1Periph_GPIOF

void soundsensor_init(void);
void soundsensor_measure(void);

#endif

















