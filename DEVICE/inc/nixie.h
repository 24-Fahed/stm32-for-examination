#ifndef __NIXIE_H__
#define __NIXIE_H__

#include "stm32f10x.h"

void   NIXIE_GPIO_Config(void);
void display_nixie(uint16_t ch, int pos);
void display_4_nixie(int number);

#endif
