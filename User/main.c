/*==============================include============================*/
#include "stm32f10x.h"
#include "LED_Ctrl.h"
#include "UART_Send.h"
#include "string.h"
#include "stdio.h"
#include "stdio_user.h"
#include "translater.h"
#include "break_service_UART.h"
// #include "break_service_Timer.h"
#include "timer.h"
#include "nixie.h"
#include "mysys.h"
#include "dev_button.h"
#include "dev_led.h"
#include "dev_beep.h"
/*================================================================*/
extern Cmd_State cmd_list;


// static DataFlow_Ptr DFP_main = NULL;

void USART_CallBack_userdef(DataFlow_Ptr);

void start_gpio_test(void);                     // 测试状态机函数
void RCC_Init_Function(void);


void RCC_Init_Function(void) {
    /*初始化系统时钟*/ 
     /*使用外部RC晶振*/
    RCC_DeInit();               // 初始化位缺省值
    RCC_HSEConfig(RCC_HSE_ON);  // 外部高速时钟
    while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);// 等待外部高速时钟就绪
    
    // FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    // FLASH_SetLatency(FLASH_Latency_2);
    
    // 系统时钟设置
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK2Config(RCC_HCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    RCC_PLLCmd(ENABLE);
    
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while (RCC_GetSYSCLKSource() != 0x08);
}


int main(void) {
    // 系统任务初始化-----------------------------------------------------------------------
    RCC_Init_Function();        // 系统时钟使能
    USART1_Init_Function();     // 串口初始化                        GPIOA 9 10 
    Stdio_Buffer_Init();        // 输入输出栈初始化
    Trans_Init();               // 翻译器初始化
    USART1_Read_Init();         // 初始化从pc读取数据
    Button_Init();              // 按键状态机初始化                     GPIOE occupied
  
    // 用户自定义device init----------------------------------------------------------------
    leds_init();                // 初始化小灯（不要用，函数写的不好）
    delay_init();               // 延时初始化
    ADCx_Init();                // ADC转换                         GPIOA occupied
    NIXIE_GPIO_Config();        // 数码管                          GPIOF cooupied
    beep_init();                // 蜂鸣器                          GPIOG pin 7 

    // 全局变量获取--------------------------------------------------------------------------
    DataFlow_Ptr DFPtr = get_StdioBuffer();
    printf("start \n");

  
    while (1) {
        // 命令解释调用
        USART1_Receive_Service(USART_CallBack_userdef);
    }
}

/* ========================== UART检测函数输入输出 =======================
// 如果开启该函数，从pc输入的数据将会从单片机返回
void USART_CallBack_userdef(DataFlow_Ptr DFP) {
    char *testString;
    printf("CallBack:active receive \n");
    // 输出数据
    testString = get_String_Data(DFP);
    printf("print data receive: %s \n", testString);
    for (int i = 0; i < 10; i++) {
        printf("test: %c", DFP->data[i]);
    }
}
=========================================================================*/

/* ============================= 中断函数命令解释 =======================*/
void USART_CallBack_userdef(DataFlow_Ptr DFP) {
    static unsigned int test_code_mem = 0;
    static unsigned int test_code_now = 0;
    
    // 解释命令
    printf("press button 1 to execute \n");
    while (1) {
        // test_code_now = button_action_Executer(&button1, 1);
        test_code_now = button_edge_Executer(&button1, 1);
        // 检测到变化 and 检测到当前状态是1
        if (test_code_now == 1) {
            printf("up mem: %d, now: %d \n", test_code_mem, test_code_now);
            break;
        }
        test_code_mem = test_code_now;
    }
    Cmd_Executer(Cmd_Sum_Analize(DFP, &cmd_list));
    
}
/*===================================================================*/


