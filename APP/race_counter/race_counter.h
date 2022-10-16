#ifndef __RACW_COUNTER_H__
#define __RACW_COUNTER_H__

#include "stdio_user.h"
#include "stdio.h"
#include "nixie.h"
// #include "Cmd_list.h"

struct counter_race {
    int a_pos;
    int b_pos;
};

typedef struct counter_race rc_struct;

static rc_struct COUNTER = {0, 0};

void counter_main(unsigned int mode);
void USART_CallBack_race(DataFlow_Ptr DFP);

#endif // __RACW_COUNTER_H__

