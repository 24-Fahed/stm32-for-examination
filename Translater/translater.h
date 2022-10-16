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
ע�⣺�ش�bug��������������Ƿ�ѡ������������ѭ��
*/

/*
    �������ģʽ����������Ѱ��ͬʱֱ�ӷ���cmd�ṹ�У�����������
*/

/*
struct CMD_STATE {                                      // ���������������
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
typedef Cmd_State *Cmd_State_Ptr;                        // ָ��ṹ���ָ��

static Cmd_State cmd_list = {                           // ��������������
    _None_Cmd,
    _None_Option,
    '\0'
};



struct CMD_STATE_T {                                     // ������洢����״̬������
    _CMD_ORDER                  order;
    _CMD_OPTION                 option;
    FUN_ACT                     Function_Action;
};


// const
// if you want add your cmd, add here
const static struct CMD_STATE_T cmd_state_table[] = {         // �������飨���ұ�
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
void                         Trans_Init(void);                                              // ��ʼ���빦������
Cmd_State_Ptr                Cmd_Sum_Analize(DataFlow_Ptr DFP, Cmd_State_Ptr CSP);          // ���÷����ܺ���
struct order_struct *        Cmd_Order_Analize(char *order);                                // ���������
struct order_struct *        Cmd_Option_Analize(char *option, struct order_struct *cmd_s);  // ����ѡ���  
int                          Cmd_parameter_Analize(char *parameter);                        // ������������



int                          Cmd_Executer(Cmd_State_Ptr CSP);                               // ִ�ж�Ӧ�����ʹ����ʼ��

static inline                Cmd_State_Ptr get_cmd_address(void) {
                                 return &(cmd_list);
                             }

void                         Cmd_Struct_to_String(Cmd_State_Ptr CSP);
                             
#endif // __TRANSLTER_H__
