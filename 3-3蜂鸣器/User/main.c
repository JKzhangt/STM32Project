#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出 高低电平都有效，开漏模式低电平有效高电平无效
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//50MHZ速度
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	

	while(1)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		Delay_ms(100);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		Delay_ms(100);
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		Delay_ms(100);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		Delay_ms(700);
		
	}
	
}
