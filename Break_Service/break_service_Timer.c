#include "break_service_Timer.h"

static unsigned Tim3_Break_flag = 0;

// 中断函数
void TIM3_IRQHandler(void)
{
	// led_toggle(LED_1);                             //1s执行一次翻转指示灯D1的操作
    Tim3_Break_flag = 1;
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);          //清除中断标志位 
}

void TIM3_Init(int length) {
	TIM_TimeBaseInitTypeDef			TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3 , ENABLE);          //打开外设TIM3时钟 
	
	TIM_DeInit(TIM3);                                               //将外设TIM3寄存器重设为缺省值  
	
	//TIM3是通用定时器，需配置TIM_ClockDivision、TIM_CounterMode、TIM_Period和TIM_Prescaler，无需配置TIM_RepetitionCounter
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1 ;       //设置了时钟分割(Tck_tim) 
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up ;   //选择了计数器模式(TIM向上计数模式)  
	TIM_TimeBaseInitStruct.TIM_Period = length ;         //设定计数器自动重装值,取值范围0x0000~0xFFFF   
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7199 ;      //设置用来作为TIM3时钟频率除数的预分频值为(7199+1),取值范围0x0000~0xFFFF 
    // 72 0000 / 7200 = 100us  100us * 10000 = 1s;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct ) ;       
    
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);              //清除TIM3的待处理标志位    
	// TIM_ITConfig(TIM3, TIM_IT_Update,ENABLE);          //使能TIM3中断  
	TIM_Cmd(TIM3, ENABLE);                             //使能TIM3外设  
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    //NVIC_Group:先占优先级2位，从优先级2位  
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;    //配置为TIM3中断  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;        //先占优先级为1  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;               //从优先级为2  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                  //使能中断通道  
    NVIC_Init(&NVIC_InitStructure); 
}

void TIMER3_Haddpen_Service(void (*TIM3_Call_Back)()) {
    if (Tim3_Break_flag == 1) {
        TIM3_Call_Back();
        Tim3_Break_flag = 0;
    }
}

void TIM3_disable(void) {
    TIM_ITConfig(TIM3, TIM_IT_Update,DISABLE);          //使能TIM3中断  
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);              //清除TIM3的待处理标志位    
}

void TIM3_enable(void) {
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);              //清除TIM3的待处理标志位    
    TIM_ITConfig(TIM3, TIM_IT_Update,ENABLE);          //使能TIM3中断  
}
