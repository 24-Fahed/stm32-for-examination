#ifndef KEY_H
#define KEY_H
#include "stm32f10x.h"

#define KEY_ON	0
#define KEY_OFF	1


#define KEYS_OFF 	0	          //û�а�������
#define KEY1_ON 	1	          //����S1����
#define KEY2_ON 	2	          //����S2����
#define KEY3_ON 	3	          //����S3����
#define KEY4_ON 	4	          //����S4����

void keys_init(void);
uint8_t keys_scan(void);

#endif
