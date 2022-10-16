#include "race_counter.h"

#include "break_service_UART.h"
#include "mysys.h"
#include "dev_button.h"
#include "timer.h"

extern rc_struct COUNTER;
static int exit_flag = 0;

void counter_main(unsigned int mode) {
    unsigned int test_code_mem = 0;
    unsigned int test_code_now = 0;
    
    Clear_DataFlow(get_StdioBuffer());
    
    // 启动八段数码管
    NIXIE_GPIO_Config();
    
    printf("Welcome using race counter program \n");
    printf("race counter start! \n");
    printf("select mode %d \n", mode);
    if (mode == 1) {
        while(1) {
            if (exit_flag == 1) {
                exit_flag = 0;
                printf("Thinks for use \n");
                break;
            }
            
            test_code_now = button_action_Executer(&button1, 1);
            
            if ((test_code_mem != test_code_now) && (test_code_now == 1)) {
                USART1_Receive_Service(USART_CallBack_race);
            }
            test_code_mem = test_code_now;
            
            display_nixie((COUNTER.a_pos) / 10, 3);
            delay_ms(3);
            display_nixie((COUNTER.a_pos) % 10, 2);
            delay_ms(3);
            display_nixie((COUNTER.b_pos) / 10, 1);
            delay_ms(3);
            display_nixie((COUNTER.b_pos) % 10, 0);
            delay_ms(3);
        }
    }
}

void USART_CallBack_race(DataFlow_Ptr DFP) {
    if (ustrcmp("group A", get_String_Data(DFP)) >= 0) {
        COUNTER.a_pos++;
    }
    else if (ustrcmp("group B", get_String_Data(DFP))  >= 0) {
        COUNTER.b_pos++;
    }
    else if (ustrcmp("A counter", get_String_Data(DFP)) >= 0) {
        // int count_list[] = {24};
        printf("进攻计时... \n");
        if (API_timer_number_counter(24)) {
            printf("score! \n");
            COUNTER.a_pos++;
        } else {
            printf("no score \n");
        }
    }
    else if (ustrcmp("exit", get_String_Data(DFP)) >= 0) {
        exit_flag = 1;
    }
    else {
        printf("please input right group \n");
    }
    printf("Current point: %d : %d \n", COUNTER.a_pos, COUNTER.b_pos);
}
