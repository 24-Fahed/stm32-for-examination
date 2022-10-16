#include "break_service_UART.h"
#include "nixie.h"


static DataFlow_Ptr DFP = NULL;
//  static int test = 0;
// �жϴ�����
void USART1_IRQHandler(void) {
    USART_ClearFlag(USART1, USART_FLAG_TC);
    rx = USART_ReceiveData(USART1);
    
    // ��ȡ����
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);       // �ȴ�����
    // printf("receive finish \n");
}

void USART1_Read_Init(void) {
    // ��ȡ����ջ��ַ
    printf("Initlize input buffer \n");
    DFP = get_StdioBuffer();
    if (DFP == NULL) {
        // ��ʼ��ʧ��
        printf("Initlize ERROR: input & communicate buffer %p \n", DFP);
        while (1);                                                          // ֹͣ��ʼ������
    }
}

// ��������һ�����⣺���ж�ȡ�õ�һ���ַ����뵽�ṹ�е�ʱ�򣬷��غ�����������е����溯��
// �ú����������ж�ֻ��һ�������ڶ�ȡһ���ַ�����������º�������������ַ��ѽ�
// ��ָ��buffer��������������ס��ֻ����������е�д��ſ��������ȡ����
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
