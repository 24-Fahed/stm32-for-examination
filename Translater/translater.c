#include "translater.h"

extern Cmd_State cmd_list;

static int table_size = 0;

void            
Trans_Init(void) {
    printf("Init Translater: \n");
    // cmd_list.order = _None_Cmd;
    // cmd_list.option = _None_Option;
    if (&cmd_list == NULL) {
      printf("[ERROR] ");
      printf("Translater no found. \n");
      printf("Init process stoped \n");
      while (1);
    }
    Cmd_List_Init();
    table_size = sizeof(cmd_table) / sizeof(struct order_struct);
    if (table_size == 0) {
      printf("[WARNING] ");
      printf("cmd table no found. \n");
    }
    printf("[OK] \n");
}


Cmd_State_Ptr   
Cmd_Sum_Analize(DataFlow_Ptr DFP, Cmd_State_Ptr CSP) {
    char tmpCall[10];
    get_Word(DFP, &(tmpCall[0]));
    struct order_struct *tmpCall_st = Cmd_Order_Analize(&(tmpCall[0]));     // 获取到order下的option指针
    if (tmpCall_st != NULL) {
        CSP->order = tmpCall_st->val;
    
    
        get_Word(DFP, &(tmpCall[0]));
        CSP->option = Cmd_Option_Analize(&(tmpCall[0]), tmpCall_st->Next)->val;
        // Cmd_parameter_Analize(get_DataFlow(DFP));
        ustrcpy(&(DFP->data[DFP->header]), CSP->parameter);        // ??????????
    }
    // 这里如果直接返回，在执行命令函数里面会死循环
    
    return CSP;
}

struct order_struct *
Cmd_Order_Analize(char *order) {
    struct order_struct *tmpCall = &(cmd_table[0]);
    while (tmpCall->Next != NULL) {
      if (ustrcmp(tmpCall->name, order) >= 0) {
        // match order
        return tmpCall;
      }
      tmpCall++;
    }
    printf("Error: No match cmd \n");
    return NULL;        // ?????????????
};                     // ??????????

struct order_struct *     
Cmd_Option_Analize(char *option, struct order_struct* cmd_s) {
    struct order_struct *tmpCall = cmd_s;
    // 检测是否为NULL
    if (cmd_s == NULL) {
        printf("cmd have op options, system return. \n");
        return NULL;
    }
    while (tmpCall->Next != NULL) {
      if (ustrcmp(tmpCall->name, option) >= 0) {
        return tmpCall;
      }
      printf("seatching... \n");
      tmpCall++;
    }
    printf("no option \n");
    return NULL;
}                   // ?????????  


/*
int             
Cmd_parameter_Analize(char *parameter) {
    
};             // ????????????
*/

int Cmd_Executer(Cmd_State_Ptr CSP) {
  int i = 0;
  while (i < sizeof(cmd_state_table) / sizeof(struct CMD_STATE_T)) {
    if (CSP->order == cmd_state_table[i].order && CSP->option == cmd_state_table[i].option) {
        cmd_state_table[i].Function_Action(&(CSP->parameter[0]));
    }
    i++;
  }
  return 0;
}

void Cmd_Struct_to_String(Cmd_State_Ptr CSP) {
    printf("Struct Cmd_State: cmd_list \n");
    printf("Address: %p \n", CSP);
    printf("Data: order_num: %d \n option_num: %d \n parameter: %s \n", \
        CSP->order, CSP->option, CSP->parameter);
    printf("end  \n");
}

