#include "cmd_ADC.h"
#include "mysys.h"
#include "stdio_user.h"

// �����ѹ�������̶���
void cmd_adc_transform(char *parameter) {
    printf("test cmd_and_transform \n");
    int i = 0;
    float vo1;
    unsigned int value = 0;
    
    while (i < 200) {
        i++;
        // printf("ccatch \n");
        if (i % 20 == 0) {
            PGout(9) =! PGout(9);
        }
        if (i % 50 == 0) {
            value = Get_ADC_Value(ADC_Channel_1, 20);
            printf("���ADֵΪ��%d \n",value);
            vo1=(float)value*(3.3/4096);
            printf("����ѹֵΪ: %.2fV\r\n",vo1);
        }
        delay_ms(10);
    }
    printf("ADC stop \n");
}
