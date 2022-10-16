#include "break_service_UART.h"
#include "nixie.h"


static DataFlow_Ptr DFP = NULL;
//  static int test = 0;
// 中断处理函数
void USART1_IRQHandler(void) {
    USART_ClearFlag(USART1, USART_FLAG_TC);
    rx = USART_ReceiveData(USART1);
    
    // 获取数据
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);       // 等待重置
    // printf("receive finish \n");
}

void USART1_Read_Init(void) {
    // 获取输入栈地址
    printf("Initlize input buffer \n");
    DFP = get_StdioBuffer();
    if (DFP == NULL) {
        // 初始化失败
        printf("Initlize ERROR: input & communicate buffer %p \n", DFP);
        while (1);                                                          // 停止初始化进行
    }
}

// 设想这样一个问题：在中断取得第一个字符载入到结构中的时候，返回后正好语句运行到下面函数
// 该函数将数据判定只有一个，并在读取一个字符后结束，导致后面的输入和这个字符脱节
// 给指定buffer上锁，将数据锁住，只有在完成所有的写入才可与操作读取服务
void USART1_Receive_Service(void (*user_CallBack)(DataFlow_Ptr)) {
    int check = 0;
    while (check != 35) {
        if (rx != 0) {
            if ((check = Load_Data(rx, DFP)) < 0) {
                printf("ERROR:buffer over flow");
                Clear_DataFlow(DFP);
            }
            if (check != 35)
                rx = 0;
            else
                unget_Char(DFP);
        }
        
        if (check == 35) {
            rx = '\0';
            user_CallBack(DFP);
        }
    }
    
    Clear_DataFlow(DFP);
    rx = '\0';
}
