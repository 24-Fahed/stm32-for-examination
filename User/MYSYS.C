#include "mysys.h"
#include "stm32f10x.h"

static u8 fac_us=0;
static u16 fac_ms=0;
uint32_t sys_count;
/***********************************************************************8
分为两组，选择其中一组用即可，即在主函数里调用delay_init()；就利用delay_us(u32 nus)；和delay_ms(u16 nms)。
在主函数里调用SysTick_Init()；和SysTick_Handler()；就利用delay_tus(uint32_t nus)；和delay_tms(uint16_t nms)；

***************************************************************************************/

void delay_init(void)
{
 SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
 fac_us=SystemCoreClock/8000000;
 fac_ms=fac_us*1000;
}

void delay_us(u32 nus)
{
 u32 temp;
 SysTick->LOAD=nus*fac_us;
 SysTick->VAL=0x00;
 SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
 do
 {
   temp=SysTick->CTRL;
 }while((temp&0x01)&&!(temp&(1<<16)));
 SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
 SysTick->VAL=0x00;
}

void delay_ms(u16 nms)
{
 u32 temp;
 SysTick->LOAD=(u32)nms*fac_ms;
 SysTick->VAL=0x00;
 SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
 do
 {
   temp=SysTick->CTRL;
 }while((temp&0x01)&&!(temp&(1<<16)));
 SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
 SysTick->VAL=0x00;
}

void SysTick_Init(void)
{
   SysTick_Config(SystemCoreClock/1000000);
}

void SysTick_Handler(void)
{
if(sys_count)
sys_count--;

}
  
void delay_tus(uint32_t nus)
{
  sys_count=nus;
	while(sys_count);
}

void delay_tms(uint16_t nms)
{
  sys_count=nms*1000;
	while(sys_count);
}
















