#include "UART_Send.h"

/*============================================
* 该模块针对中断进行进一步封装，提供初始化外设的函数，提供操控硬件的函数
* 初始化数据发送
* 
========================================================================*/

void USART1_Init_Function(void) {
    /*RCC*/
    /*外设时钟使能*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    
    /*GPIO*/
    // 设置PA9 PA10为指定外设接收发送
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /*NVIC 针对数据接收中断提供*/
    NVIC_InitTypeDef NVIC_InitStructure;
    
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   // 先占优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          // 从优先级
    NVIC_Init(&NVIC_InitStructure);
    
    /*USART1初始化设置*/
    // 初始化USART
    USART_InitTypeDef USART_InitStructure;
    
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = 
        USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure);
    
    USART_Cmd(USART1, ENABLE);
    USART_ClearFlag(USART1, USART_FLAG_TC);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  
    
    /*同步时钟设置（暂时不需用）
    USART_ClockInitTypeDef USART_ClockInitStructure;
    
    USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
    USART_ClockInitStructure.USART_CPOL = USART_CPOL_High;
    USART_ClockInitStructure.USART_CPHA = USART_CPHA_1Edge;
    USART_ClockInitStructure.USART_LastBit = USART_LastBit_Enable;
    // USART_Init(USART1, &USART_ClockInitStructure);
    USART_ClockInit(USART1, &USART_ClockInitStructure);
    */
}
