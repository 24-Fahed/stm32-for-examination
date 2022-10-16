/****************************************Copyright (c)****************************************************
**                                        
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:		 main.c
** Last modified Date:          
** Last Version:		   
** Descriptions:		   
**				
**--------------------------------------------------------------------------------------------------------
** Created by:			FiYu
** Created date:		2018-1-20
** Version:			    1.0
** Descriptions:		KEY���
**--------------------------------------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "dev_key.h"
#include "delay.h"


/*******************************************************************************
 * ��  �� : ��ʼ����Ƭ����ⰴ��S1������PE2������S2������PE3������S3������PE4������S4������PE5
 * ��  �� : ��
 * ����ֵ : ��
 ******************************************************************************/
void keys_init(void)
{
   //����IO��ʼ�����ýṹ��
   GPIO_InitTypeDef  GPIO_InitStructure;
   //��PE�˿�ʱ��
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 
	 
	 //���õ�IO��PE2��PE3��PE4��PE5
   GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;		
	 //����Ϊ��������
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	 //���ÿ⺯��GPIO_Init()����IO
   GPIO_Init(GPIOE, &GPIO_InitStructure);						
}

/***************************************************************************
 * ��  �� : ��⿪�����ϵ�4������(S1 S2 S3 S4)
 * ��  �� : ��
 * ����ֵ : �������
 ***************************************************************************/
uint8_t keys_scan(void)
{
   //���ÿ⺯GPIO_ReadInputDataBit()��ⰴ��S1������S2������S3������S4��Ӧ����PE2��PE3��PE4��PE5�ĵ�ƽ�Ƿ�Ϊ�͵�ƽ
   if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) == KEY_ON )  || (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) == KEY_ON )  || (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) == KEY_ON )  ||  (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5) == KEY_ON ) )
	 {
       //�����ʱ10ms�������ʱ�󰴼�S1�ĵ�ƽ��Ȼû�б仯��˵������ȷʵ����Ч��������ư�������
			 sw_delay_ms(10);
       if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) == KEY_ON )  
	     {	
         return KEY1_ON;
       }
       else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) == KEY_ON )
       {
         return KEY2_ON;
       }
       else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) == KEY_ON )
       {
         return KEY3_ON;
       }
       else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5) == KEY_ON )
       {
         return KEY4_ON;
       }

   }
   
   else if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) == KEY_OFF )&&(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) == KEY_OFF ) &&(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) == KEY_OFF )&&(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5) == KEY_OFF )  )
   {
     ;
   }
  
   return KEYS_OFF;
}


/********************************************END FILE********************/
