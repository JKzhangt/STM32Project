#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出 高低电平都有效，开漏模式低电平有效高电平无效
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//50MHZ速度
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	

	while(1)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		Delay_ms(500);
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		Delay_ms(500);
		
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
		Delay_ms(500);
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
		Delay_ms(500);
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)0);//把0转换为枚举类型
		Delay_ms(500);
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)1);
		Delay_ms(500);
	}
	
}
