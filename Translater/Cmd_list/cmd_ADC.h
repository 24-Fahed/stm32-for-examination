#ifndef __CMD_ADC_H__
#define __CMD_ADC_H__

#include "stdio.h"
#include "dev_ADC.h"

// Ԥ��λ�ã����������Ƿ���Ч
static inline void cmd_adc_test(char *test) {
    printf("it is a adc cmd test \n");
    printf("��ѹ��... V \n");
}

void cmd_adc_transform(char *parameter);

#endif // __CMD_ADC_H__
