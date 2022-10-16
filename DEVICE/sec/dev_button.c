/* ============================== statue machine instructer: ===========================================
* A button contain four state: new_state, event and Next_state. Now state will switch to Next_state
* under the effection of event. A programs has designed for get button event. 
* Following is state machine change for a button switch from press to release
* holding (no change):
* _True_Press_state   -- press --> _True_Press_state   >> nothing

* change state (button pressed):
* _True_Press_state   --release--> _Hode_Press_state   >> nothing           // 容错
* _Hode_Press_state   --release--> _Hode_Press_state   >> check_release_act // 检测
* _Hode_Press_state   --ensure_release--> _True_Release_state >> release_act // 释放
* 
* hode release state (after change)
* _True_Release_state --release--> _True_Release_state >> nothing
=======================================================================================================*/

/* =============================== How to maintain state table =====================================
* Call Button_Init() to init button state struct and state table
* Then call analizeData(currstate, classfy_button1_event(check_press_counter, check_release_counter))
* this function will return your current state but can not update button state struct (it is a bug).
* analizeData will tell what next state it is. According to those imformation, you can make related 
* action. 
* It is just a demo for the process of what i think.
================================================================================================== */

/*

*/


/*
Auther: who want design a system for blindness people, please tell me by qq.<^_^>
*/ 

/*
button status: batton1, batton2
*/

#include "dev_button.h"

static button_fsm_table_t Button_States[] = {
    // now_state          event                  Next_state
                                                                                    // 按键1对应状态表
    {_True_Press_state,   Button1_Press_event,   _True_Press_state,   nothing           },
    {_True_Press_state,   Button1_Release_event, _Hold_Press_state,   nothing           },
    {_Hold_Release_state, Insure1_Press_event,   _True_Press_state,   press_act         },
    {_Hold_Press_state,   Insure1_Release_event, _True_Release_state, release_act       },
    {_Hold_Release_state, Button1_Press_event,   _Hold_Release_state, check_press_act   },
    {_Hold_Press_state,   Button1_Release_event, _Hold_Press_state,   check_release_act },
    {_True_Release_state, Button1_Press_event,   _Hold_Release_state, nothing           },
    {_True_Release_state, Button1_Release_event, _True_Release_state, nothing           },
    {_Other_state,        Other_event,           _Other_state,        fail_act          }
};

// extern button_fsm_table_t Button_States;

void Button_Init(void) {
    // 开启GPIOE和2 3 4 5
    // 初始化时钟
    RCC->APB2ENR |= 1<<6;
    
    // 设置端口输入接受
    // 接受浮空0x04
    GPIOE->CRL &= ~0x00FFFF00;
    GPIOE->CRL |= 0x00444400;
    
    // 初始化按键状态机
    // 修改：将原来的数据直接修改掉，不使用指针指向state_table
    // bug：初始化初始为Button_States的第一个数据
    
    
    button1.state_table = Button_States[7];     // 初始化为松开
    button1.check_release_counter = 0;
    button1.check_press_counter = 0;
    
    button2.state_table = Button_States[7];
    button2.check_press_counter = 0;
    button2.check_release_counter = 0;
}

button_event classfy_button1_event(int counter_press, int counter_release) {
    button_event event = Other_event;
    int state_int = GPIOE->IDR;
    
    if (counter_press >= 30) {                           // 防抖动
        return event = Insure1_Press_event;
    }
    if (counter_release <= -30) {                        // 防抖动
        return event = Insure1_Release_event;
    }
    if ((state_int & 1<<2) != 1<<2) {                   // 按下
        return (event = Button1_Press_event);
    }
    else {                                              // 释放
        return (event = Button1_Release_event);
    }
    // return event;
}

button_event classfy_button2_event(int counter_press, int counter_release) {
    button_event event = Other_event;
    int state_int = GPIOE->IDR;
    
    if (counter_press >= 30) {                           // 防抖动
        return event = Insure1_Press_event;
    }
    if (counter_release <= -30) {                        // 防抖动
        return event = Insure1_Release_event;
    }
    if ((state_int & 1<<3) != 1<<3) {                   // 按下
        return (event = Button1_Press_event);
    }
    else{                                              // 释放
        return (event = Button1_Release_event);
    }
    // return event;
}


/*
该函数将判断结果用结构体的方式返回
*/
button_fsm_table_t analizeData(button_states currstate, button_event registerEvent) {
    int ind;
    // 寻找状态
    for (ind = 0; ind < sizeof(Button_States) / sizeof(Button_States[0]); ++ind) {
        if (currstate     == Button_States[ind].state && 
            registerEvent == Button_States[ind].event) {
                return Button_States[ind];
            }
    }
    return Button_States[8];        // 没有寻找到
}

/*
该函数将更改结构体状态并执行对应的动作
分析 -> 行动 -> 更改状态
使用返回值为结构体，并非指针，以维护对照表
这种方法返回按键的数据非常缓慢
*/
unsigned int button_action_Executer(button_sum_ptr button, int button_num) {
    button_fsm_table_t table;
    unsigned int return_code = 0;
    // 分析
    if (button_num == 1)
         table =  analizeData(button->state_table.state, classfy_button1_event(button->check_press_counter, button->check_release_counter));
    else if (button_num == 2)
         table =  analizeData(button->state_table.state, classfy_button2_event(button->check_press_counter, button->check_release_counter));
    // 更改状态
    switch (table.action) {
        case press_act:
            // 清空计数器
            button->check_press_counter = 0;
            button->check_release_counter = 0;
            // 更细状态
            return_code = 1;
            break;
        case release_act:
            button->check_press_counter = 0;
            button->check_release_counter = 0;
            // 更改状态
            break;
        case check_press_act:
            button->check_press_counter += 1;
            // return_code = 0;
            break;
        case check_release_act:
            button->state_table = table;
            button->check_release_counter -= 1;
            break;
        case fail_act:
            return_code = 3;
            button->state_table = Button_States[7];// 重新初始化按键
            return return_code;
        default:
            // button->state_table.state = table.nextstate;
            if (button->state_table.state == _True_Press_state)
                return_code = 1;
            else if (button->state_table.state == _True_Release_state)
                return_code = 0;
            break;
    }
    button->state_table.state = table.nextstate;
    return return_code;
}

// 边沿触发，当按键按下或者抬起的时候不变，只有在按键按压并抬起的一瞬间会返回1；
unsigned int button_edge_Executer(button_sum_ptr button, int button_num) {
    button_fsm_table_t table;
    unsigned int return_code = 0;
    // 分析
    if (button_num == 1)
         table =  analizeData(button->state_table.state, classfy_button1_event(button->check_press_counter, button->check_release_counter));
    else if (button_num == 2)
         table =  analizeData(button->state_table.state, classfy_button2_event(button->check_press_counter, button->check_release_counter));
    // 更改状态
    switch (table.action) {
        case press_act:
            // 清空计数器
            button->check_press_counter = 0;
            button->check_release_counter = 0;
            // 更细状态
            return_code = 1;
            break;
        case release_act:
            button->check_press_counter = 0;
            button->check_release_counter = 0;
            // 更改状态
            break;
        case check_press_act:
            button->check_press_counter += 1;
            // return_code = 0;
            break;
        case check_release_act:
            button->state_table = table;
            button->check_release_counter -= 1;
            break;
        case fail_act:
            return_code = 3;
            button->state_table = Button_States[7];// 重新初始化按键
            return return_code;
        default:
            break;
    }
    button->state_table.state = table.nextstate;
    return return_code;
}
