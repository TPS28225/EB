

#ifndef _BEEP_H_
#define _BEEP_H_

typedef struct
{
  short mName; // 音名：取值L1～L7、M1～M7、H1～H7分别表示低音、中音、高音的1234567，取值0表示休止符
  short mTime; // 时值：取值T、T/2、T/4、T/8、T/16、T/32分别表示全音符、二分音符、四分音符、八分音符.，取值0表示演奏结束
}tNote;

#define BEEP_RCC   RCC_AHB1Periph_GPIOE
#define BEEP_GPIO  GPIOE
#define BEEP_PIN   GPIO_Pin_5

#define BEEP_ON    GPIO_SetBits(BEEP_GPIO,BEEP_PIN)
#define BEEP_OFF   GPIO_ResetBits(BEEP_GPIO,BEEP_PIN)

void buzzerQuiet(void);	// 蜂鸣器停止发声
void buzzerSound(unsigned short usFreq);
void BEEP_Run(void);
void BEEP_Configuration(void);
void Beep_Config(void);
void musicPlay(const tNote *MyScore);
#endif
