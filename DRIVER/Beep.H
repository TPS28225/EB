

#ifndef _BEEP_H_
#define _BEEP_H_

#define BEEP_RCC   RCC_AHB1Periph_GPIOE
#define BEEP_GPIO  GPIOE
#define BEEP_PIN   GPIO_Pin_5

#define BEEP_ON    GPIO_SetBits(BEEP_GPIO,BEEP_PIN)
#define BEEP_OFF   GPIO_ResetBits(BEEP_GPIO,BEEP_PIN)

//void BEEP_Run(void);
//void BEEP_Configuration(void);
void Beep_Config(void);
void musicPlay(void);
#endif
