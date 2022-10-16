#ifndef __TRANSLTER_H__
#define __TRANSLTER_H__

#include "stdio_user.h"
#include "stdio.h"
#include "string.h"

#include "Cmd_list.h"


/* ========================parameter instructer===========================
    [adj]           [type]                      [name]              [value]     [effection]
    ststic          int                         table_size          0           store cmd_table length
    const struct    struct CMD_STATE_T list     cmd_state_table     init        store cmd translated
    static          Cmd_State                   cmd_list            init        store cmd_table
============================================================================*/

/*========================struct instructor===============================
    [declear]           [typedef]                       [effection]
    struct CMD_STATE    CMD_STATE | *Cmd_State_Ptr      translated cmd struct
    struct CMD_STATE_T  NULL                            translater status table struct
==========================================================================*/

/* =======================status machine instructer=========================
Add new cmd: insert cmd all possible status in this struct list:
cmd_state_table
{
order, option, parameter,      // cmd current received
}(adding rules)

Then, add a file Named Cmd_{cmd_name}.c & Cmd_{cmd_name}.h.Those file include:
    - Cmd actions function to execute cmd
    - DEV driver including in this file 

Finally, goto Cmd_list.h add cmd name in enum _CMD_ORDER and ccmd options in
_CMD_OPTION. Reorginized search table cmd_table and cmd_option table in 
cmd_table. You will find instructer in file Cmd_list.h to help you add cmd to
table.
==========================================================================*/


/*
注意：重大bug：如果程序遇到非法选项或者命令，会死循环
*/

/*
    更改设计模式：将函数在寻找同时直接放在cmd结构中，减少运算量
*/

/*
struct CMD_STATE {                                      // 作用宇命令的载体
    _CMD_ORDER                  order;
    _CMD_OPTION                 option;
    char                        parameter[10];
};*/

typedef void (*FUN_ACT)(char *);

struct CMD_STATE {
    unsigned char               order;                  // _CMD_ORDER
    unsigned char               option;                 // _CMD_OPTION
    char                        parameter[10];
    // FUN_ACT                     Function_Action;        // execute task
};

typedef struct CMD_STATE Cmd_State;
typedef Cmd_State *Cmd_State_Ptr;                        // 指向结构体的指针

static Cmd_State cmd_list = {                           // 被翻译过后的命令
    _None_Cmd,
    _None_Option,
    '\0'
};



struct CMD_STATE_T {                                     // 作用宇存储命令状态的载体
    _CMD_ORDER                  order;
    _CMD_OPTION                 option;
    FUN_ACT                     Function_Action;
};


// const
// if you want add your cmd, add here
const static struct CMD_STATE_T cmd_state_table[] = {         // 命令数组（查找表）
  {_send,     _pc,          cmd_send_pc },
  {_send,     _rf,          NULL},
  {_ADC,      _test,        cmd_adc_test},
  {_ADC,      _trans,       cmd_adc_transform},
  {_Race,     _cmdMode,     cmd_race_cmdMode},
  {_timer,    _sec,         cmd_timer_sec},
  {_timer,    _counter,     cmd_timer_counter},
  {_None_Cmd, _None_Option, NULL        }
};

/*==========================logic function defination ==========================*/
void                         Trans_Init(void);                                              // 初始翻译功能命令
Cmd_State_Ptr                Cmd_Sum_Analize(DataFlow_Ptr DFP, Cmd_State_Ptr CSP);          // 调用分析总函数
struct order_struct *        Cmd_Order_Analize(char *order);                                // 分析命令函数
struct order_struct *        Cmd_Option_Analize(char *option, struct order_struct *cmd_s);  // 分析选项函数  
int                          Cmd_parameter_Analize(char *parameter);                        // 分析参数函数



int                          Cmd_Executer(Cmd_State_Ptr CSP);                               // 执行对应的语句和处理初始化

static inline                Cmd_State_Ptr get_cmd_address(void) {
                                 return &(cmd_list);
                             }

void                         Cmd_Struct_to_String(Cmd_State_Ptr CSP);
                             
#endif // __TRANSLTER_H__
