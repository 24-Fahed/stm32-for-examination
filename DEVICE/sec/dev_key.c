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
** Descriptions:		KEY检测
**--------------------------------------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "dev_key.h"
#include "delay.h"


/*******************************************************************************
 * 描  述 : 初始化单片机检测按键S1的引脚PE2、按键S2的引脚PE3、按键S3的引脚PE4、按键S4的引脚PE5
 * 参  数 : 无
 * 返回值 : 无
 ******************************************************************************/
void keys_init(void)
{
   //定义IO初始化配置结构体
   GPIO_InitTypeDef  GPIO_InitStructure;
   //打开PE端口时钟
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 
	 
	 //配置的IO是PE2、PE3、PE4、PE5
   GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;		
	 //配置为上拉输入
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	 //调用库函数GPIO_Init()配置IO
   GPIO_Init(GPIOE, &GPIO_InitStructure);						
}

/***************************************************************************
 * 描  述 : 检测开发板上的4个按键(S1 S2 S3 S4)
 * 参  数 : 无
 * 返回值 : 按键编号
 ***************************************************************************/
uint8_t keys_scan(void)
{
   //调用库函GPIO_ReadInputDataBit()检测按键S1、按键S2、按键S3、按键S4对应引脚PE2、PE3、PE4、PE5的电平是否为低电平
   if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) == KEY_ON )  || (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) == KEY_ON )  || (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) == KEY_ON )  ||  (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5) == KEY_ON ) )
	 {
       //软件延时10ms，如果延时后按键S1的电平依然没有变化，说明按键确实被有效操作，简称按键消抖
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
