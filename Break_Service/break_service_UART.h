#ifndef __BREAK_SERVICE_H__
#define __BREAK_SERVICE_H__

#include <stm32f10x.h>
#include <stdio.h>
#include "stdio_user.h"

// data receiver
static char rx = '\0';

// global parameter
static void *cmd_buffer = NULL;

void USART1_Read_Init(void);
// 检测是否有数据进入
void USART1_Receive_Service(void (*user_CallBack)(DataFlow_Ptr));

#endif // __BREAK_SERVICE_H__
