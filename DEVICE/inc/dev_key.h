#ifndef KEY_H
#define KEY_H
#include "stm32f10x.h"

#define KEY_ON	0
#define KEY_OFF	1


#define KEYS_OFF 	0	          //没有按键按下
#define KEY1_ON 	1	          //按键S1按下
#define KEY2_ON 	2	          //按键S2按下
#define KEY3_ON 	3	          //按键S3按下
#define KEY4_ON 	4	          //按键S4按下

void keys_init(void);
uint8_t keys_scan(void);

#endif
