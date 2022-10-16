#ifndef __DEF_BEEP_H__
#define __DEF_BEEP_H__

#include "stm32f10x.h"

/*========================== breaf instruct ============================
蜂鸣器驱动。
在device init区域调用beep_init初始化蜂鸣器（占用GPIOG 7）
调用beep_start 开始蜂鸣
调用beep_stop 停止蜂鸣
======================================================================= */

static inline void beep_init  (void)
{
   //定义IO初始化配置结构体
   GPIO_InitTypeDef  GPIO_InitStructure;
   //打开PG端口时钟
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);	 
	 
	 //配置的IO是PG7
   GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;		
	 //配置为通用推挽输出
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 //IO口速度为50MHz
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 //调用库函数GPIO_Init()配置IO
   GPIO_Init(GPIOG, &GPIO_InitStructure);	
   //设置蜂鸣器的初始状态设置为不鸣叫t
   GPIO_ResetBits(GPIOG,GPIO_Pin_7);						
}

static inline void beep_start(void) {
  GPIO_SetBits(GPIOG,GPIO_Pin_7); 
}

static inline void beep_stop(void) {
  GPIO_ResetBits(GPIOG,GPIO_Pin_7);	 
}

#endif // __DEF_BEEP_H__
