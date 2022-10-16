#ifndef __CMD_ADC_H__
#define __CMD_ADC_H__

#include "stdio.h"
#include "dev_ADC.h"

// 预留位置，测试命令是否生效
static inline void cmd_adc_test(char *test) {
    printf("it is a adc cmd test \n");
    printf("电压：... V \n");
}

void cmd_adc_transform(char *parameter);

#endif // __CMD_ADC_H__
