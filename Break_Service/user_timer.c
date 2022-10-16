#include "stm32f10x.h"
#include "user_timer.h"
#include "led.h"

/**************************************************************************************
 * ��  �� : ��ʼ��TIM3������TIM3�ж����ȼ�
 * ��  �� : ��
 * ����ֵ : ��
 **************************************************************************************/
void TIM3_Init(void)
{
	TIM_TimeBaseInitTypeDef			TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3 , ENABLE);          //������TIM3ʱ�� 
	
	TIM_DeInit(TIM3);                                               //������TIM3�Ĵ�������Ϊȱʡֵ  
	
	//TIM3��ͨ�ö�ʱ����������TIM_ClockDivision��TIM_CounterMode��TIM_Period��TIM_Prescaler����������TIM_RepetitionCounter
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1 ;       //������ʱ�ӷָ�(Tck_tim) 
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up ;   //ѡ���˼�����ģʽ(TIM���ϼ���ģʽ)  
	TIM_TimeBaseInitStruct.TIM_Period = 9999 ;         //�趨�������Զ���װֵ,ȡֵ��Χ0x0000~0xFFFF   
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7199 ;      //����������ΪTIM3ʱ��Ƶ�ʳ�����Ԥ��ƵֵΪ(7199+1),ȡֵ��Χ0x0000~0xFFFF 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct ) ;       

	TIM_ClearFlag(TIM3, TIM_FLAG_Update);              //���TIM3�Ĵ�������־λ    
	TIM_ITConfig(TIM3, TIM_IT_Update,ENABLE);          //ʹ��TIM3�ж�  
	TIM_Cmd(TIM3, ENABLE);                             //ʹ��TIM3����  
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    //NVIC_Group:��ռ���ȼ�2λ�������ȼ�2λ  
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;    //����ΪTIM3�ж�  
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;        //��ռ���ȼ�Ϊ1  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;               //�����ȼ�Ϊ2  
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                  //ʹ���ж�ͨ��  
  NVIC_Init(&NVIC_InitStructure); 
}

/**************************************************************************************
 * ��  �� : TIM3�жϷ�����
 * ��  �� : ��
 * ����ֵ : ��
 **************************************************************************************/
void TIM3_IRQHandler(void)
{
	led_toggle(LED_1);                             //1sִ��һ�η�תָʾ��D1�Ĳ���
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);          //����жϱ�־λ 
}