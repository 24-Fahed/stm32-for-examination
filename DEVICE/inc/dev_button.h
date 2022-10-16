#ifndef __BUTTON_CTRL_H__
#define __BUTTON_CTRL_H__

#include "stm32f10x.h" 


// 编写按键对应的所有状态
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

// 这里对应的是操作小灯的行为，应该在led中提供，这里先写一下
typedef enum            {press_act = 0, release_act, check_press_act, check_release_act, nothing,
                         Other_act,
                         fail_act}
                         button_act;

                         
// 编写button对应状态机表
typedef struct {
    // 当前状态
    button_states      state;
    button_event       event;
    // 下一状态
    button_states      nextstate;
    button_act         action;
} button_fsm_table_t;

typedef button_fsm_table_t *button_fsm_table_p;      // 指针

// 存储按键状态机
typedef struct {
    // 按键状态存放
    button_fsm_table_t state_table;
    int check_release_counter;
    int check_press_counter;
} button_sum;

typedef button_sum *button_sum_ptr;

// 创建按键数据表
static button_sum button1;
static button_sum button2;


// 按键状态机初始化
void Button_Init(void);
// button状态机调用
// 事件分类器
button_event classfy_button1_event(int check_press_counter, int check_release_counter);
button_event classfy_button2_event(int check_press_counter, int check_release_counter);

// 事件分析器
button_fsm_table_t analizeData(button_states currstate, button_event registerEvent);
// 测试函数(提供仿真测试的函数，GPIOE_Pin_3按键，对应高位反应)
void init_button_test(void);
void test_dev_button(void);

// 使用数字的形式返回
unsigned int button_action_Executer(button_sum_ptr button, int button_num);
unsigned int button_edge_Executer(button_sum_ptr button, int button_num);

#endif // __BUTTON_CTRL_H__
