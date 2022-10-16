#include "dev_ADC.h"
#include "stm32f10x.h"
#include "mysys.h"
// #include "MYSYS.H"

/*====================================ADC模块使用说明===============================
完整调用程序参考cmd_adc.c中的编写
向单片机中发送adc -trans# 可以直接输出电压
====================================================================================*/


void ADCx_Init(void)
{
   //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef  ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
 
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;//TX			   //串口输出PA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;	    //复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* 初始化串口输入IO */
	
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;
	
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;// ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv None; 你原来的代码
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel=1;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	
}
	
u16 Get_ADC_Value(u8  ch,u8 times)
{
  u32 temp_val=0;
	u8 t;
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5);
	
	for(t=0;t<times;t++)
	{
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	temp_val+=ADC_GetConversionValue(ADC1);
    delay_ms(5);
	}
	return temp_val/times;
}
