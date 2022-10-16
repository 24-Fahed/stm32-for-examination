#ifndef __LED_CTRL_H__
#define __LED_CTRL_H__

#include "stm32f10x.h"

typedef struct LED_Group LG_Struct;
typedef struct LED_Group* LG_Struct_ptr;
struct LED_Group {
    int LED1;
    int LED2;
    int LED3;
    int LED4;
};

void LED_Init(void);
void LED_Ctrl(LG_Struct_ptr LG);

#endif
