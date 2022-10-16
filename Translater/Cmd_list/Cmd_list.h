#ifndef __CMD_LIST_H__
#define __CMD_LIST_H__

#include <stdio.h>

#include "cmd_Send.h"
#include "cmd_ADC.h"
#include "cmd_Race.h"
#include "cmd_timer.h"

/*
cmd list 组成说明
Value enum {
    cmd...
}

struct order_struct cmd_table {
    String Name, Value...
}

add a cmd please add cmdName in two parameter above

init table
order_cmd -> option1 -> option2......
*/

// order state struct
typedef enum    {
                    _send = 0,
                    _ADC,
                    _Race,
                    _timer,
                    _None_Cmd,
                } 
_CMD_ORDER;

                // 缺陷：如果命令中有相同的选项，则会出现问题
typedef enum    {
                    // temp cmd option
                    _pc = 0,
                    _rf,
    
                    _test,
                    _trans,
    
                    _cmdMode,
    
                    _sec,
                    _counter,
    
                    _None_Option
                }
_CMD_OPTION;

// 命令结构存储类型：
/*
struct order_struct {
    const char            *name;
    const union {
           _CMD_ORDER     cmd_value;
           _CMD_OPTION  option_value;
    } val;
    struct order_struct   *Next;
    // struct order_struct   *Batch;
};*/

// 尝试使用unsigned char存储变量值
struct order_struct {
    const char          *name;
    const unsigned char val;
    struct order_struct *Next;
};

// 命令翻译表
static struct order_struct cmd_table[] = {
    {"send", _send, NULL},
    {"ADC", _ADC, NULL},
    {"Race", _Race, NULL},
    {"timer", _timer, NULL},
    {"\0", _None_Cmd, NULL}
};

static struct order_struct option_table[] = {
    {"-pc",         _pc,            NULL},
    {"-rf",         _rf,            NULL},
    {"-test",       _test,          NULL},
    {"-trans",      _trans,         NULL},
    
    {"-cmd",        _cmdMode,       NULL},
    
    {"-sec",        _sec,           NULL},
    {"-counter",    _counter,       NULL},
    {"",            _None_Option,   NULL}
};
/* ================= table search linker relation ============
cmd_table     option_table
send      ->  -pc -> NULL
  |
\0        ->  ""  -> NULL

*/

static inline void Cmd_List_Init(void) {
    // struct order_struct *end_cmd = &(cmd_table[(sizeof(cmd_table) / sizeof(struct order_struct)) - 1]);
    struct order_struct *end_option = &(option_table[(sizeof(option_table) / sizeof(struct order_struct)) - 1]);
    // send  
    cmd_table[0].Next = &(option_table[0]);       
          // send option
    option_table[0].Next = &(option_table[1]);
    option_table[1].Next = end_option;
    
    // adc
    cmd_table[1].Next = &(option_table[2]);
    option_table[2].Next = &(option_table[3]);
    option_table[3].Next = end_option;
    
    // raec
    cmd_table[2].Next = &(option_table[4]);
    option_table[4].Next = end_option;
    
    // timer
    cmd_table[3].Next = &(option_table[5]);
    option_table[5].Next = &(option_table[6]);
    option_table[6].Next = end_option;
    
    
    // NONE cmd
    // cmd_table[1].Next = end_option;
    // end_cmd->Next = end_option;
};

#endif // __CMD_LIST_H__
