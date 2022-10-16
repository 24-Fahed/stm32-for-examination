#ifndef __BUTTON_CTRL_H__
#define __BUTTON_CTRL_H__

#include "stm32f10x.h" 


// ��д������Ӧ������״̬
typedef enum            {Button1_Press_event = 0, Button1_Release_event,
                         Button2_Press_event, Button2_Release_event,
                         Insure1_Press_event, Insure1_Release_event,
                         Insure2_Press_event, Insure2_Release_event,
                         Other_event}
                         button_event;
                         
typedef enum            {_True_Press_state = 0, _True_Release_state, 
                         _Hold_Press_state, _Hold_Release_state,
                         _Other_state}
                         button_states;

// �����Ӧ���ǲ���С�Ƶ���Ϊ��Ӧ����led���ṩ��������дһ��
typedef enum            {press_act = 0, release_act, check_press_act, check_release_act, nothing,
                         Other_act,
                         fail_act}
                         button_act;

                         
// ��дbutton��Ӧ״̬����
typedef struct {
    // ��ǰ״̬
    button_states      state;
    button_event       event;
    // ��һ״̬
    button_states      nextstate;
    button_act         action;
} button_fsm_table_t;

typedef button_fsm_table_t *button_fsm_table_p;      // ָ��

// �洢����״̬��
typedef struct {
    // ����״̬���
    button_fsm_table_t state_table;
    int check_release_counter;
    int check_press_counter;
} button_sum;

typedef button_sum *button_sum_ptr;

// �����������ݱ�
static button_sum button1;
static button_sum button2;


// ����״̬����ʼ��
void Button_Init(void);
// button״̬������
// �¼�������
button_event classfy_button1_event(int check_press_counter, int check_release_counter);
button_event classfy_button2_event(int check_press_counter, int check_release_counter);

// �¼�������
button_fsm_table_t analizeData(button_states currstate, button_event registerEvent);
// ���Ժ���(�ṩ������Եĺ�����GPIOE_Pin_3��������Ӧ��λ��Ӧ)
void init_button_test(void);
void test_dev_button(void);

// ʹ�����ֵ���ʽ����
unsigned int button_action_Executer(button_sum_ptr button, int button_num);
unsigned int button_edge_Executer(button_sum_ptr button, int button_num);

#endif // __BUTTON_CTRL_H__
