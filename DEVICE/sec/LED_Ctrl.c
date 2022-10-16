#include "LED_Ctrl.h"

void LED_Init(void) {

    GPIO_InitTypeDef  GPIO_InitStructure;
    //��PA�˿�ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	 
    //���õ�IO��PG6
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;		
	//IO���ٶ�Ϊ50MHz
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //����Ϊͨ���������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	//���ÿ⺯��GPIO_Init()����IO
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
    
    //����D1��ʼ��״̬ΪϨ��	
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
