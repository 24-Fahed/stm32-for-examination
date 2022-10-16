#include "stm32f10x.h"
#include "nixie.h"
#include "MYSYS.h"

/*
初始化NIXIE_GPIO_Confi43g后，
将需要显示的数据（4位）输入到函数display_4_nixie中，即可显示
*/

uint16_t digit_table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

void   NIXIE_GPIO_Config(void){
	GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7| \
        GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
}
	
void display_nixie(uint16_t ch, int pos) {
    // GPIO_Write(GPIOF,table[ch]);
    // GPIOF->ODR |= 1<<8;            // 设置8号为高电平
    GPIO_Write(GPIOF, digit_table[ch] + (0x0100 << pos));
}

void display_4_nixie(int number) {
    display_nixie(number % 10, 0);
    delay_ms(2);
    display_nixie(number / 10 % 10, 1);
    delay_ms(2);
    display_nixie(number / 100 % 10, 2);
    delay_ms(2);
    display_nixie(number / 1000 % 10, 3);
    delay_ms(2);
}
	
