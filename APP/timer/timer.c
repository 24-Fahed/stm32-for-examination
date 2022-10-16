#include "timer.h"
#include "dev_button.h"
#include "stdio_user.h"
#include "nixie.h"
#include "mysys.h"
#include "break_service_UART.h"

void TIM3_Break_CallBack(void);
void timer_mune_USART_CallBack(DataFlow_Ptr DFP);

static int time = 0;
static int time_list[] = {0, 0, 0, 0, 0, 0, 0, 0};
static unsigned int counter_state = _wait;

static int api_time_max = 0;
static int api_init = 0;
static int api_stop = 0;

static int button1_mem = 0;
static int button1_now = 0;

void timer_init(void) {
    // ��ʼ����ʱ��
    TIM3_Init(TIM3_1s);
}


// static int init = 0;
// ��Ӧ�ð�����������
// ��ʼ�� -> ������ -> ������ӿ� -> ���ָ��ϵͳ


void timer_start(void) {
    int pos = 0;
    TIM3_Init(TIM3_1s);            // ��ʼ��
    NIXIE_GPIO_Config();
    Clear_DataFlow(get_StdioBuffer());
    // rx = 0;                         // ���³�ʼ��usart
    
    while(1) {
        // ����ʱ
        button1_now = button_action_Executer(&button1, 1);
        if (counter_state == _start) {
            TIMER3_Haddpen_Service(TIM3_Break_CallBack);// �ȴ��ж�
            if (counter_state == _start && BUTTON1_DOWN_STARE) {
                if (pos < 8) {
                    time_list[pos] = time;
                    printf("AT: %d \n", time);
                }
                else {
                    counter_state = _wait;
                    pos = 0;
                    // printf("timer recoder %d, %d, %d \n", time_list[0], time_list[1], time_list[2]);
                    TIM3_disable();
                }
                pos++;
            }
        }
        
        // apiִ��
        if (counter_state == _api) {
            if (api_init == 0) {
                TIM3_enable();
                api_init = 1;
            }
            TIMER3_Haddpen_Service(TIM3_Break_CallBack);// �ȴ��ж�
            if (time > api_time_max) {
                counter_state = _api_wait;
                TIM3_disable();
            }
            if (BUTTON1_DOWN_STARE) {
                counter_state  = _api_wait;
                TIM3_disable();
                api_stop = 1;
            }
        }
        
        if (counter_state  == _api_wait) {
            // ������ܿ���ʱ�䷵��api���ƺ���
            api_init = 0;
            break;
        }
        
        // ����˵�
        if (counter_state == _wait) {
            printf("Timer meun: \n (input display to show records \n input exit back to cmd line) \n input start to start timer \n");
            USART1_Receive_Service(timer_mune_USART_CallBack);
            pos = 0;
        }
        
        // �˳����
        if (counter_state == _exit) {
            printf("thinks for use \n");
            time = 0;
            break;
        }
        
        // ��ʾʱ��
        display_nixie(time / 1000, 3);
        delay_ms(2);
        display_nixie(time / 100, 2);
        delay_ms(2);
        display_nixie(time / 10, 1);
        delay_ms(2);
        display_nixie(time % 10, 0);
        delay_ms(2);
        
        button1_mem = button1_now;
    }
    TIM3_disable();
    counter_state = _wait;
}

void timer_mune_USART_CallBack(DataFlow_Ptr DFP) {
    char *order = get_String_Data(DFP);
    if (ustrcmp("display", order) >= 0) {
        printf("timer recoder %d, %d, %d, %d, %d, %d, %d, %d \n", time_list[0], time_list[1], time_list[2] \
                        , time_list[3], time_list[4], time_list[5], time_list[6], time_list[7]);
    }
    else if (ustrcmp("start", order) >= 0) {
        time = 0;
        for (int i = 0; i < 8; i++)             // ��ʼ������
            time_list[i] = 0;
        TIM3_enable();
        counter_state = _start;
    }
    else if (ustrcmp("exit", order) >= 0) {
        counter_state = _exit;
    } else {
        printf("unexpected cmd \n");
    }
}


void API_timer_TimerCounter(int *timer_list) {
    for (int n = 0; n < 5; n++) {
        api_time_max = *(timer_list + n);
        counter_state = _api;
        timer_start();
        printf("one finished at %d sec \n", *(timer_list + n));
        
    }
    // �������
    time = 0;
    api_time_max = 0;
    counter_state = _wait;
    return;
}

int API_timer_number_counter(int timef) {
    // ��ʼ��
    api_stop = 0;
    api_time_max = timef;
    counter_state = _api;
    // ��ʼ
    TIM3_enable();
    // ��ʱ
    timer_start();
    // ���
    time = 0;
    api_time_max = 0;
    counter_state = _wait;
    // �ж�
    if (api_stop == 1) return 1;
    else               return 0;
}

void TIM3_Break_CallBack(void) {
    // printf("up time \n");
    time++;
}
