#include "LED_Ctrl.h"

void LED_Init(void) {

    GPIO_InitTypeDef  GPIO_InitStructure;
    //打开PA端口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	 
    //配置的IO是PG6
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;		
	//IO口速度为50MHz
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //配置为通用推挽输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	//调用库函数GPIO_Init()配置IO
    GPIO_Init(GPIOG, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    //设置D1初始化状态为熄灭	
    GPIO_SetBits(GPIOG, GPIO_Pin_6);
    GPIO_SetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_9);
    GPIO_SetBits(GPIOA, GPIO_Pin_8);
}

void LED_Ctrl(LG_Struct_ptr LG) {
    if ((*LG).LED2 == 1)            GPIO_ResetBits(GPIOB, GPIO_Pin_8);
    else                            GPIO_SetBits(GPIOB, GPIO_Pin_8);
    
    if ((*LG).LED1 == 1)            GPIO_ResetBits(GPIOB, GPIO_Pin_9);
    else                            GPIO_SetBits(GPIOB, GPIO_Pin_9);
    
    if ((*LG).LED3 == 1)            GPIO_ResetBits(GPIOA, GPIO_Pin_8);
    else                            GPIO_SetBits(GPIOA, GPIO_Pin_8);
    
    if ((*LG).LED4 == 1)            GPIO_ResetBits(GPIOG, GPIO_Pin_6);
    else                            GPIO_SetBits(GPIOG, GPIO_Pin_6);
}
