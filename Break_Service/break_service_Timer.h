#ifndef __BREAK_SERVICE_TIMER_H__
#define __BREAK_SERVICE_TIMER_H__

#include "stm32f10x.h"

#define TIM3_1s 9999

// TIM3_1s «1√Îº∆ ±
void TIM3_Init(int length);
void TIMER3_Haddpen_Service(void (*TIM3_Call_Back)());
void TIM3_disable(void);
void TIM3_enable(void);

#endif // __BREAK_SERVICE_TIMER_H__
