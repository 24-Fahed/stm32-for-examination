#ifndef __DEF_BEEP_H__
#define __DEF_BEEP_H__

#include "stm32f10x.h"

/*========================== breaf instruct ============================
������������
��device init�������beep_init��ʼ����������ռ��GPIOG 7��
����beep_start ��ʼ����
����beep_stop ֹͣ����
======================================================================= */

static inline void beep_init  (void)
{
   //����IO��ʼ�����ýṹ��
   GPIO_InitTypeDef  GPIO_InitStructure;
   //��PG�˿�ʱ��
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);	 
	 
	 //���õ�IO��PG7
   GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;		
	 //����Ϊͨ���������
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 //IO���ٶ�Ϊ50MHz
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 //���ÿ⺯��GPIO_Init()����IO
   GPIO_Init(GPIOG, &GPIO_InitStructure);	
   //���÷������ĳ�ʼ״̬����Ϊ������t
   GPIO_ResetBits(GPIOG,GPIO_Pin_7);						
}

static inline void beep_start(void) {
  GPIO_SetBits(GPIOG,GPIO_Pin_7); 
}

static inline void beep_stop(void) {
  GPIO_ResetBits(GPIOG,GPIO_Pin_7);	 
}

#endif // __DEF_BEEP_H__
