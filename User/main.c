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

void start_gpio_test(void);                     // ����״̬������
void RCC_Init_Function(void);


void RCC_Init_Function(void) {
    /*��ʼ��ϵͳʱ��*/ 
     /*ʹ���ⲿRC����*/
    RCC_DeInit();               // ��ʼ��λȱʡֵ
    RCC_HSEConfig(RCC_HSE_ON);  // �ⲿ����ʱ��
    while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);// �ȴ��ⲿ����ʱ�Ӿ���
    
    // FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    // FLASH_SetLatency(FLASH_Latency_2);
    
    // ϵͳʱ������
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
    // ϵͳ�����ʼ��-----------------------------------------------------------------------
    RCC_Init_Function();        // ϵͳʱ��ʹ��
    USART1_Init_Function();     // ���ڳ�ʼ��                        GPIOA 9 10 
    Stdio_Buffer_Init();        // �������ջ��ʼ��
    Trans_Init();               // ��������ʼ��
    USART1_Read_Init();         // ��ʼ����pc��ȡ����
    Button_Init();              // ����״̬����ʼ��                     GPIOE occupied
  
    // �û��Զ���device init----------------------------------------------------------------
    leds_init();                // ��ʼ��С�ƣ���Ҫ�ã�����д�Ĳ��ã�
    delay_init();               // ��ʱ��ʼ��
    ADCx_Init();                // ADCת��                         GPIOA occupied
    NIXIE_GPIO_Config();        // �����                          GPIOF cooupied
    beep_init();                // ������                          GPIOG pin 7 

    // ȫ�ֱ�����ȡ--------------------------------------------------------------------------
    DataFlow_Ptr DFPtr = get_StdioBuffer();
    printf("start \n");

  
    while (1) {
        // ������͵���
        USART1_Receive_Service(USART_CallBack_userdef);
    }
}

/* ========================== UART��⺯��������� =======================
// ��������ú�������pc��������ݽ���ӵ�Ƭ������
void USART_CallBack_userdef(DataFlow_Ptr DFP) {
    char *testString;
    printf("CallBack:active receive \n");
    // �������
    testString = get_String_Data(DFP);
    printf("print data receive: %s \n", testString);
    for (int i = 0; i < 10; i++) {
        printf("test: %c", DFP->data[i]);
    }
}
=========================================================================*/

/* ============================= �жϺ���������� =======================*/
void USART_CallBack_userdef(DataFlow_Ptr DFP) {
    static unsigned int test_code_mem = 0;
    static unsigned int test_code_now = 0;
    
    // ��������
    printf("press button 1 to execute \n");
    while (1) {
        // test_code_now = button_action_Executer(&button1, 1);
        test_code_now = button_edge_Executer(&button1, 1);
        // ��⵽�仯 and ��⵽��ǰ״̬��1
        if (test_code_now == 1) {
            printf("up mem: %d, now: %d \n", test_code_mem, test_code_now);
            break;
        }
        test_code_mem = test_code_now;
    }
    Cmd_Executer(Cmd_Sum_Analize(DFP, &cmd_list));
    
}
/*===================================================================*/


